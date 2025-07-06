#pragma once
#pragma comment(lib, "OpenGL32.lib")
#include <Windows.h>
#include <stdio.h>
#include <gl/GL.h>
#include "gltext.h"

namespace GL
{
	namespace rgb
	{
		const GLubyte red[3] = { 255, 0, 0 };
		const GLubyte green[3] = { 0, 255, 0 };
		const GLubyte gray[3] = { 55, 55, 55 };
		const GLubyte lightgray[3] = { 192, 192, 192 };
		const GLubyte black[3] = { 0, 0, 0 };
	}

	extern GLint Cviewport[4];
	extern GLint ScreenWidth;
	extern GLint ScreenHeight;

	void SetupOrtho();
	void RestoreGl();

	void DrawLine(float x1, float y1, float x2, float y2, float lineWidth, const GLubyte color[3]);
	void DrawFilledRect(float x, float y, float width, float height, const GLubyte color[3]);
	void DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3]);
	void DrawCircle(float cx, float cy, float r, int num_segments, GLfloat lineWidth, const GLubyte color[3]);
}
