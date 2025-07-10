#pragma once
#include <d3d9.h>
#include <Windows.h>
#include "hooks.h"

namespace Dx9Drawing
{
	void DrawFilledRect(float x, float y, float width, float height, const unsigned char color[3]);
}
