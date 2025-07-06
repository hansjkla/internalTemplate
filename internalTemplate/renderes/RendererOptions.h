#pragma once

enum class RendererOptions
{
    NONE,
    DX9,
    DX10,
    DX11,
    DX12,
    OPENGL,
    VULKAN
};

extern RendererOptions Renderer;
