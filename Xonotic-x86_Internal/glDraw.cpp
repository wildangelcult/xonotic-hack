#include "glDraw.h"

GLint currProg;

void GL::setupOrtho() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport[2], viewport[3], 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetIntegerv(GL_CURRENT_PROGRAM, &currProg);
	glUseProgram(0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
}

void GL::restoreGL() {
	glUseProgram(currProg);
	glPopMatrix();
	glPopAttrib();
}

void GL::drawFilledRect(float x, float y, float width, float height, const GLubyte color[3]) {
	glColor3ub(color[0], color[1], color[2]);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();

}

void GL::drawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3]) {
	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);
	glColor3ub(color[0], color[1], color[2]);
	glVertex2f(x - 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y - 0.5f);
	glVertex2f(x + width, y + height + 0.5f);
	glVertex2f(x - 0.5f, y + height + 0.5f);
	glVertex2f(x - 0.5f, y - 0.5f);
	glEnd();
}

void GL::drawLine(float from_x, float from_y, float to_x, float to_y, float lineWidth, const GLubyte color[3]) {
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	glColor3ub(color[0], color[1], color[2]);
	glVertex2f(from_x, from_y);
	glVertex2f(to_x, to_y);
	glEnd();
}

void GL::drawPoint(float x, float y, float pointSize, const GLubyte color[3]) {
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	glColor3ub(color[0], color[1], color[2]);
	glVertex2f(x, y);
	glEnd();
}