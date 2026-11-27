#include "Develop/DieGildeAddOn/game/game_data.h"
extern double g_664f10;
extern char g_68bdc4[];
extern char g_68bda8[];

unsigned int __cdecl cut_RandMod(int n);
int __cdecl d3_CreateSceneModelObject(int a, char* pos, float* rot, char* name);
int __cdecl d3_ApplyObjectAnimation(int h, char* name, int k);

/* ADDRESS: GOLDTL 0x004dfd10 */
int __cdecl d3_SpawnBlutlacheEffect(char* e)
{
	float rot[3];
	int h;

	rot[0] = 0.0f;
	rot[1] = 0.0f;
	rot[2] = 0.0f;
	rot[1] = cut_RandMod(0x168) * g_6628fc * g_664f10;
	h = d3_CreateSceneModelObject(0, *(char**) (*(char**) (e + 0x14) + 0x34) + 0x4c, rot, g_68bdc4);
	return d3_ApplyObjectAnimation(h, g_68bda8, 0x12);
}
