#include "drawing.h"


void Dx9Drawing::DrawLine(float x1, float y1, float x2, float y2, float lineWidth, const unsigned char color[3])
{
	if (!hooks::realDevice) return;

	D3DCOLOR col = D3DCOLOR_ARGB(255, color[0], color[1], color[2]);

	Vertex line[2] =
	{
		{x1, y1, 0.0f, 1.0f, col},
		{x2, y2, 0.0f, 1.0f, col}
	};

	hooks::realDevice->SetFVF(D3DFVF_VERTEX);
	hooks::realDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, line, sizeof(Vertex));
}


void Dx9Drawing::DrawFilledRect(float x, float y, float width, float height, const unsigned char color[3])
{
	if (!hooks::realDevice) return;

	D3DRECT rect = { (LONG)x, (LONG)y, (LONG)(x + width), (LONG)(y + height) };
	hooks::realDevice->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, color[0], color[1], color[2]), 0, 0);
}


void Dx9Drawing::DrawOutline(float x, float y, float width, float height, float lineWidth, const unsigned char color[3])
{
	if (!hooks::realDevice) return;

	D3DCOLOR col = D3DCOLOR_ARGB(255, color[0], color[1], color[2]);

	Vertex outline[5] =
	{
		{x, y, 0.0f, 1.0f, col},
		{x + width, y, 0.0f, 1.0f, col},
		{x + width, y + height, 0.0f, 1.0f, col},
		{x, y + height, 0.0f, 1.0f, col},
		{x, y, 0.0f, 1.0f, col}
	};

	hooks::realDevice->SetFVF(D3DFVF_VERTEX);
	hooks::realDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, outline, sizeof(Vertex));
}


void Dx9Drawing::DrawCircle(float cx, float cy, float r, int num_segments, float lineWidth, const unsigned char color[3])
{

}
