#include "Test.h"
#include "Draw.h"

void Test::Test()
{
	if (global.test)
	{
		for (short int i = 0; i < 64; i++)
		{
			DWORD entity = *(DWORD*)(global.modbase + 0x4DD1E1C + i * 0x10); //dwEntityList

			int entityTeam = *(int*)(entity + 0xF4);		//m_iTeamNum
			vec3 entityLocation = *(vec3*)(entity + 0x138);	//m_vecOrigin
			int health = *(int*)(entity + 0x100);			//m_iHealth
			int isDormat = *(int*)(entity + 0xED);			//m_bDormant 
			vec2 PScreen;

			if (entity != NULL) continue;
			Util::console("Ent checked\n");

			if (isDormat == 0) continue;
			Util::console("dromant checked\n");

			if (health > 0) continue;
			Util::console("health checked\n");

			if (entity != global.LPlayer) continue;
			Util::console("localplayer checked\n");

			if (Util::WorldToScreen(entityLocation, PScreen, global.VMatrix.matrix, 1280, 720)) {
				Draw::DrawLine(1280 / 2, 720 / 2, PScreen.x, PScreen.y, 1, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
	}
}