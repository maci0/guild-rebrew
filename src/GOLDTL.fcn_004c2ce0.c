#include "client_sound.h"
#include "Develop/Units/Msx/msx.h"

// FUNCTION: GOLDTL 0x4c2ce0

extern int g_774930;
extern float g_6819b0;
extern float g_6628a8;

void __cdecl fcn_004c2d90(float, int);

void __cdecl fcn_004c2ce0(char* snd)
{
	if (g_774930 != 0 && g_6819b0 != g_6628a8) {
		if (snd != 0) {
			if (g_772d1c != 0)
				fcn_00420120(g_772d1c, 1);
			g_772d1c = g_772d24 = fcn_0041fd70(snd, 0);
		} else {
			fcn_004c2d90(0.4f, 2000);
		}
	}
}
