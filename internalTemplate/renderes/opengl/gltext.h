#pragma once
#pragma comment(lib, "OpenGL32.lib")
#include <Windows.h>
#include <stdio.h>
#include <gl/GL.h>
#include "../../utils/math.h"
#include "glhook.h"

namespace GL
{
	class Font
	{
	public:
		bool bBuilt = false;
		unsigned int base;
		HDC hDc = nullptr;
		int height;
		int width;

		void Build(int height);
		
	};

	void Print(float x, float y, const GLubyte color[3], const char* format, ...);
	vec2 centerText(float x, float y, float width, float height, float textWidth, float textHeight);
	float centerTextf(float x, float width, float textWidth);
}

namespace glHook {
	extern GL::Font glFont;
}
