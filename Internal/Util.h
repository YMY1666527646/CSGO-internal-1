#pragma once
#include "include.h"

namespace Util
{
	void console(const char* text);
	uint8_t* PatternScan(void* module, const char* signature);
	bool WorldToScreen(vec3 pos, vec2& screen, float matrix[16], int windowWidth, int windowHeight);
}

