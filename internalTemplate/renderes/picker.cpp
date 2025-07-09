#include "picker.h"

void RenderQueue::Submit(const std::function<void()>& fn)
{
    std::lock_guard<std::mutex> lock(queueMutex);
    queue.push_back(fn);
}

void RenderQueue::ExecuteAll()
{
    std::lock_guard<std::mutex> lock(queueMutex);
    for (const auto& fn : queue)
        fn();
    queue.clear();
}

bool CreateRenderer(RendererOptions renderer)
{
    switch (renderer)
    {
    case RendererOptions::NONE:
        return false;
    case RendererOptions::DX9:
        Renderer = RendererOptions::DX9;
        //return (crd3d9::Create());

    case RendererOptions::DX10:
        Renderer = RendererOptions::DX10;

    case RendererOptions::DX11:
        Renderer = RendererOptions::DX11;

    case RendererOptions::DX12:
        Renderer = RendererOptions::DX12;

    case RendererOptions::OPENGL:
        Renderer = RendererOptions::OPENGL;
        return (glHook::CreateGl());

    case RendererOptions::VULKAN:
        Renderer = RendererOptions::VULKAN;
    }
}

void DrawLine(float x1, float y1, float x2, float y2, float lineWidth, const unsigned char color[3])
{
    switch (Renderer)
    {
    case RendererOptions::NONE:
        return;

    case RendererOptions::DX9:
        return;

    case RendererOptions::DX10:
        return;

    case RendererOptions::DX11:
        return;

    case RendererOptions::DX12:
        return;

    case RendererOptions::OPENGL:
        return RenderQueue::Submit([x1, y1, x2, y2, lineWidth, color] {GL::DrawLine(x1, y1, x2, y2, lineWidth, color); });

    case RendererOptions::VULKAN:
        return;
    }
}

void DrawFilledRect(float x, float y, float width, float height, const unsigned char color[3])
{
    switch (Renderer)
    {
    case RendererOptions::NONE:
        return;

    case RendererOptions::DX9:
        return;

    case RendererOptions::DX10:
        return;

    case RendererOptions::DX11:
        return;

    case RendererOptions::DX12:
        return;

    case RendererOptions::OPENGL:
        return RenderQueue::Submit([x, y, width, height, color] {GL::DrawFilledRect(x, y, width, height, color); });

    case RendererOptions::VULKAN:
        return;
    }
}

void DrawOutline(float x, float y, float width, float height, float lineWidth, const unsigned char color[3])
{
    switch (Renderer)
    {
    case RendererOptions::NONE:
        return;

    case RendererOptions::DX9:
        return;

    case RendererOptions::DX10:
        return;

    case RendererOptions::DX11:
        return;

    case RendererOptions::DX12:
        return;

    case RendererOptions::OPENGL:
        return RenderQueue::Submit([x, y, width, height, lineWidth, color] {GL::DrawOutline(x, y, width, height, lineWidth, color); });

    case RendererOptions::VULKAN:
        return;
    }
}

void DrawCircle(float cx, float cy, float r, int num_segments, GLfloat lineWidth, const unsigned char color[3])
{
    switch (Renderer)
    {
    case RendererOptions::NONE:
        return;

    case RendererOptions::DX9:
        return;

    case RendererOptions::DX10:
        return;

    case RendererOptions::DX11:
        return;

    case RendererOptions::DX12:
        return;

    case RendererOptions::OPENGL:
        return RenderQueue::Submit([cx, cy, r, num_segments, lineWidth, color] {GL::DrawCircle(cx, cy, r, num_segments, lineWidth, color); });

    case RendererOptions::VULKAN:
        return;
    }
}

void Print(float x, float y, const unsigned char color[3], const char* format, ...)
{
    char Buffer[100];

    va_list args;
    va_start(args, format);
    vsnprintf(Buffer, 100, format, args);
    va_end(args);

    switch (Renderer)
    {
    case RendererOptions::NONE:
        return;

    case RendererOptions::DX9:
        return;

    case RendererOptions::DX10:
        return;

    case RendererOptions::DX11:
        return;

    case RendererOptions::DX12:
        return;

    case RendererOptions::OPENGL:
    {
        return RenderQueue::Submit([=]() {
            GL::Print(x, y, color, format, Buffer);
            });
    }

    case RendererOptions::VULKAN:
        return;
    }
}
