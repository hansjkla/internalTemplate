#include "gldraw.h"

GLint GL::Cviewport[4];
GLint GL::ScreenWidth = NULL;
GLint GL::ScreenHeight = NULL;

void GL::SetupOrtho()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);

	Cviewport[0] = viewport[0];
	Cviewport[1] = viewport[1];
	Cviewport[2] = viewport[2];
	ScreenWidth = viewport[2];
	Cviewport[3] = viewport[3];
	ScreenHeight = viewport[3];

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
}

void GL::RestoreGl()
{
	glPopMatrix();
	glPopAttrib();
}

void GL::DrawLine(float x1, float y1, float x2, float y2, float lineWidth, const GLubyte color[3])
{
	glLineWidth(lineWidth);
	glColor3ub(color[0], color[1], color[2]);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void GL::DrawFilledRect(float x, float y, float width, float height, const GLubyte color[3])
{
	glColor3ub(color[0], color[1], color[2]);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

void GL::DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3])
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	glColor3ub(color[0], color[1], color[3]);
	glVertex2f(x - 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y  - 0.5f);
	glVertex2f(x + width + 0.5f, y + height + 0.5f);
	glVertex2f(x - 0.5f, y + height + 0.5f);
	glEnd();
}


void GL::DrawCircle(float cx, float cy, float r, int num_segments, GLfloat lineWidth, const GLubyte color[3])
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	glColor3ub(color[0], color[1], color[3]);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
}
