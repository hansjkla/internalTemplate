#include "drawing.h"

void Dx9Drawing::DrawFilledRect(float x, float y, float width, float height, const unsigned char color[3])
{
	if (!hooks::realDevice)
	{
		MessageBox(NULL, "No valid device", "Error", MB_OK);
		return;
	}

	D3DRECT rect = { (LONG)x, (LONG)y, (LONG)(x + width), (LONG)(y + height) };
	hooks::realDevice->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, color[0], color[1], color[2]), 0, 0);
}
