#include "Entity.h"

uintptr_t Ent::localplayer()
{
	return *(uintptr_t*)(global.modbase + OFFSET_LOCALPLAYER);
}

bool Ent::isAlive(uintptr_t ent)
{
	
}
