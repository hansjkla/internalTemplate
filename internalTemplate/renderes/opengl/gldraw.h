#pragma once
#pragma comment(lib, "OpenGL32.lib")
#include <Windows.h>
#include <stdio.h>
#include <gl/GL.h>
#include "gltext.h"

namespace GL
{
	void SetupOrtho();
	void RestoreGl();

	void DrawLine(float x1, float y1, float x2, float y2, float lineWidth, const GLubyte color[3]);
	void DrawFilledRect(float x, float y, float width, float height, const GLubyte color[3]);
	void DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3]);
	void DrawCircle(float cx, float cy, float r, int num_segments, GLfloat lineWidth, const GLubyte color[3]);
}
