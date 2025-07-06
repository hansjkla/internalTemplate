#pragma once
#include <mutex>
#include <vector>
#include <functional>
#include "d3d9/crd3d9.h"
#include "opengl/glhook.h"
#include "RendererOptions.h"

namespace RenderQueue
{
	inline std::vector<std::function<void()>> queue;
	inline std::mutex queueMutex;

	void Submit(const std::function<void()>& fn);
	void ExecuteAll();
}

bool CreateRenderer(RendererOptions renderer);

void Render(const std::function<void()>& fn);
