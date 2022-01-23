#pragma once
#include "include.h"

struct viewMatrix_t
{
	float matrix[16];
};

struct  GlobalVar
{
	uintptr_t modbase;
	viewMatrix_t VMatrix;

	DWORD LPlayer;

	bool test = false;
};

extern GlobalVar global;