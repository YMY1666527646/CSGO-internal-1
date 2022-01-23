#include "Draw.h"

IDirect3DDevice9Ex* p_Device;
ID3DXLine* p_Line;

void Draw::TestBox()
{
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(25 - 1, 25 - 1), ImVec2(100 + 1, 100 + 1), D3DCOLOR_ARGB(255, 0, 0, 0), 0, 1); //bigger than main rect
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(25 + 1, 25 + 1), ImVec2(100 - 1, 100 - 1), D3DCOLOR_ARGB(255, 0, 0, 0), 0, 1); //smaller than main rect, those 2 make outlines
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(25, 25), ImVec2(100, 100), D3DCOLOR_ARGB(255, 0, 0, 255), 0, 1);
}

void Draw::DrawFilledRectangle(int x, int y, int w, int h, D3DCOLOR color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(w, h), color, 0);
}

void Draw::DrawBorderBox(int x, int y, int x2, int y2, int thickness, D3DCOLOR color)
{
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(x - 1, y - 1), ImVec2(x2 + 1, y2 + 1), D3DCOLOR_ARGB(255, 0, 0, 0), 0, 1); //bigger than main rect
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(x + 1, y + 1), ImVec2(x2 - 1, y2 - 1), D3DCOLOR_ARGB(255, 0, 0, 0), 0, 1); //smaller than main rect, those 2 make outlines
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x2, y2), color, 0, thickness);
}

void Draw::DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color)
{
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), color, thickness);
}

void Draw::DrawCircle(int x, int y, float radius, float width, float rez, D3DCOLOR color)
{
	ImGui::GetOverlayDrawList()->AddCircle(ImVec2(x, y), radius, color, rez, width);
}

void Draw::DrawCorneredBox(float X, float Y, float W, float H, float thickness, D3DCOLOR color) {
	float lineW = (W / 4);
	float lineH = (H / 4);

	//black outlines
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0f, 1 / 255.0f, 1 / 255.0f, 255.f / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0f, 1 / 255.0f, 1 / 255.0f, 255.f / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0f, 1 / 255.0f, 1 / 255.0f, 255.f / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0f, 1 / 255.0f, 1 / 255.0f, 255.f / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0f, 1 / 255.0f, 1 / 255.0f, 255.f / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0f, 1 / 255.0f, 1 / 255.0f, 255.f / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0f, 1 / 255.0f, 1 / 255.0f, 255.f / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0f, 1 / 255.0f, 1 / 255.0f, 255.f / 255.0)), 3);

	//corners
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), color, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), color, thickness);
}

/*
vec3 RotatePoint(vec3 EntityPos, vec3 LocalPlayerPos, int posX, int posY, int sizeX, int sizeY, float angle, float zoom, bool* viewCheck)
{
	float r_1, r_2;
	float x_1, y_1;
	float yawToRadian;

	r_1 = -(EntityPos.y - LocalPlayerPos.y);
	r_2 = EntityPos.x - LocalPlayerPos.x;
	float Yaw = angle - 90.0f;

	if (globals.Minimaprot) { yawToRadian = Yaw * (float)(M_PI / 180.0F); }
	else { yawToRadian = (float)(M_PI / 180.0F); }

	x_1 = (float)(r_2 * (float)cos((double)(yawToRadian)) - r_1 * sin((double)(yawToRadian))) / 20;
	y_1 = (float)(r_2 * (float)sin((double)(yawToRadian)) + r_1 * cos((double)(yawToRadian))) / 20;

	*viewCheck = y_1 < 0;

	x_1 /= zoom;
	y_1 /= zoom;

	int sizX = sizeX / 2;
	int sizY = sizeY / 2;

	x_1 += sizX;
	y_1 += sizY;

	if (x_1 < 5)
		x_1 = 5;

	if (x_1 > sizeX - 5)
		x_1 = sizeX - 5;

	if (y_1 < 5)
		y_1 = 5;

	if (y_1 > sizeY - 5)
		y_1 = sizeY - 5;


	x_1 += posX;
	y_1 += posY;


	return vec3{ x_1, y_1, 0 };
}

void DrawRadarPoint(uintptr_t ent)
{
	bool out = false;
	vec3 siz;
	siz.x = globals.minimapw;
	siz.y = globals.minimaph;
	vec3 pos;
	pos.x = globals.minimapx;
	pos.y = globals.minimapy;
	bool ck = false;
	vec3 bruhang = Player::GetViewAngles(globals.localPlayer);


	vec3 targetHead = Player::GetBonePos(ent, 8);
	float dist = Driver.rpm<vec3>(globals.localPlayer + OFFSET_ORIGIN).DistTo(targetHead);
	float distM = Util::ToMeters(dist);
	vec3 single = RotatePoint(Player::GetEntityBasePosition(ent), Player::GetEntityBasePosition(globals.localPlayer), pos.x, pos.y, siz.x, siz.y, bruhang.y, globals.minimapdist, &ck);

	DrawCircle(single.x, single.y, 3, 1, 3, Util::Vec4toARGB(globals.Radarcol));
}
*/