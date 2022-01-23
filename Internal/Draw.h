#pragma once
#include "include.h"

namespace Draw
{
	void DrawFilledRectangle(int x, int y, int w, int h, D3DCOLOR color);
	void DrawBorderBox(int x, int y, int x2, int y2, int thickness, D3DCOLOR color);
	void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color);
	void DrawCircle(int x, int y, float radius, float width, float rez, D3DCOLOR color);
	void DrawCorneredBox(float X, float Y, float W, float H, float thickness, D3DCOLOR color);
	void TestBox();
	//void DrawRadarPoint(uintptr_t ent);
}