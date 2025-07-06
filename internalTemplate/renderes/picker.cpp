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
    if (renderer == RendererOptions::NONE) return false;

    switch (renderer)
    {
    case RendererOptions::NONE:
        return false;
    case RendererOptions::DX9:
        Renderer = RendererOptions::DX9;
        return (crd3d9::Create());

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


void Render(const std::function<void()>& fn)
{
    RenderQueue::Submit(fn);
}
