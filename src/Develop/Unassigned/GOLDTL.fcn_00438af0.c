extern int g_67a370;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_6b8300;

char __cdecl fcn_00438a80(void* p, int arg);
void __cdecl d3_VisitSceneObjects(int list, int a, int mask, char(__cdecl* fn)(void*, int), int arg);
void __cdecl d3_ResetSkyDomeNormals(int a, int b);

/* ADDRESS: GOLDTL 0x00438af0 */
void __cdecl fcn_00438af0(unsigned char a)
{
	d3_VisitSceneObjects(g_67a370, 0, 0x1ff, fcn_00438a80, a);
	if (g_6b89c0 != 0) {
		d3_ResetSkyDomeNormals(g_6b89c0, 0);
	}
	if (((char*)g_6b8300) != 0) {
		((char*)g_6b8300)[0x8036] |= 1;
	}
}
