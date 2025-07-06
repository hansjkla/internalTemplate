#include "gltext.h"

void GL::Font::Build(int height)
{
	hDc = wglGetCurrentDC();
	base = glGenLists(96);
	HFONT hFont = CreateFontA(-height, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Consolas");
	HFONT hOldFont = (HFONT)SelectObject(hDc, hFont);
	wglUseFontBitmaps(hDc, 32, 96, base);
	SelectObject(hDc, hOldFont);
	DeleteObject(hFont);

	bBuilt = true;
}

void GL::Print(float x, float y, const GLubyte color[3], const char* format, ...)
{
	glColor3ub(color[0], color[1], color[2]);
	glRasterPos2f(x, y);

	char text[100];
	va_list args;

	va_start(args, format);
	vsprintf_s(text, 100, format, args);
	va_end(args);

	glPushAttrib(GL_LIST_BIT);
	glListBase(glHook::base - 32);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}

vec2 GL::centerText(float x, float y, float width, float height, float textWidth, float textHeight)
{
	vec2 text;
	text.x = x + (width - textWidth) / 2;
	text.y = y + textHeight;
	return text;
}

float GL::centerTextf(float x, float width, float textWidth)
{
	if (width > textWidth)
	{
		float difference = width - textWidth;
		return (x + (difference / 2));
	}
	float difference = textWidth - width;
	return (x - (difference / 2));
}
