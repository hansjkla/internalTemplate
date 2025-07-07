#pragma once
#include <mutex>
#include <vector>
#include <functional>
#include <cstdarg>
#include <cstdio>
#include <string>
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

void DrawLine(float x1, float y1, float x2, float y2, float lineWidth, const unsigned char color[3]);
void DrawFilledRect(float x, float y, float width, float height, const unsigned char color[3]);
void DrawOutline(float x, float y, float width, float height, float lineWidth, const unsigned char color[3]);
void DrawCircle(float cx, float cy, float r, int num_segments, GLfloat lineWidth, const unsigned char color[3]);
void Print(float x, float y, const unsigned char color[3], const char* format, ...);
