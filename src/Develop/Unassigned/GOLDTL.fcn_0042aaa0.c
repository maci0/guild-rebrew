typedef int (__stdcall* g_662450_f)(int);
extern g_662450_f g_662450;
extern g_662450_f g_662450;



#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl msx_FindSampleHandleIndex(int);

int __cdecl fcn_0042aaa0(int a1)
{
	int r = -1;

	if (g_6b7f90 != 0 && msx_FindSampleHandleIndex(a1) >= 0) {
		r = g_662450(a1);
	}
	return r;
}
