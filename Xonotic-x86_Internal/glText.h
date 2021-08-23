#pragma once
#pragma comment(lib, "OpenGL32.lib")
#include <Windows.h>
#include <stdio.h>
#include <gl/GL.h>
#include "mem.h"
#include "vector.h"

namespace GL {
	class font {
	public:
		bool bBuilt = false;
		unsigned int base;
		HDC hdc = nullptr;
		int height;
		int width;

		void build(int height);
		void print(float x, float y, const unsigned char color[3], const char* format, ...);

		Vector3 centerText(float x, float y, float width, float height, float textWidth, float textHeight);
		float centerText(float x, float width, float textWidth);

	};
}