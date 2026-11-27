#include "Develop/DieGildeAddOn/game/game_data.h"
extern double g_664f10;
extern char g_68bdc4[];
extern char g_68bda8[];
extern char g_68bdd4[];

unsigned int __cdecl cut_RandMod(int n);
int __cdecl sb_PlayVoice(int, char*, int, int, int, int, int);
int __cdecl fcn_00442910(int, char*, float*, char*);
int __cdecl d3_ApplyObjectAnimation(int, char*, int);

/* ADDRESS: GOLDTL 0x004d4700 */
int __cdecl ch_RunDeathFallAction(char* e)
{
	float rot[3];
	int h;

	rot[0] = 0.0f;
	rot[1] = 0.0f;
	rot[2] = 0.0f;
	rot[1] = cut_RandMod(0x168) * g_6628fc * g_664f10;
	sb_PlayVoice(0, g_68bdd4, 1, 63, 127, 0, 0);
	h = fcn_00442910(0, *(char**) (*(char**) (e + 0x14) + 0x34) + 0x4c, rot, g_68bdc4);
	return d3_ApplyObjectAnimation(h, g_68bda8, 0x12);
}
