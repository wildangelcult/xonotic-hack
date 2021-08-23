#pragma once
#pragma comment(lib, "OpenGL32.lib")
#include <Windows.h>
#include <stdio.h>
#include <GL/glew.h>
#include "mem.h"

namespace colors {
	const GLubyte red[3] = { 255, 0, 0 };
	const GLubyte green[3] = { 0, 255, 0 };
	const GLubyte blue[3] = { 0, 0, 255 };
	const GLubyte gray[3] = { 55, 55, 55 };
	const GLubyte light_gray[3] = { 192, 192, 192 };
	const GLubyte black[3] = { 0, 0, 0 };
	const GLubyte white[3] = { 255, 255, 255 };
}

namespace GL {
	void setupOrtho();
	void restoreGL();

	void drawFilledRect(float x, float y, float width, float height, const GLubyte color[3]);
	void drawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3]);
	void drawLine(float from_x, float from_y, float to_x, float to_y, float lineWidth, const GLubyte color[3]);
	void drawPoint(float x, float y, float pointSize, const GLubyte color[3]);
}