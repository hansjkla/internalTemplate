#pragma once
#include <d3d9.h>
#include <vector>
#include "hooks.h"

namespace Dx9Drawing
{
	struct Vertex
	{
		float x, y, z, rhw;
		D3DCOLOR color;
	};
	#define D3DFVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

	void DrawLine(float x1, float y1, float x2, float y2, float lineWidth, const unsigned char color[3]);
	void DrawFilledRect(float x, float y, float width, float height, const unsigned char color[3]);
	void DrawOutline(float x, float y, float width, float height, float lineWidth, const unsigned char color[3]);
	void DrawCircle(float cx, float cy, float r, int num_segments, float lineWidth, const unsigned char color[3]);
}
