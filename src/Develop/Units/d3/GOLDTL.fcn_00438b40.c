#include "Develop/Units/d3/d3_camera.h"
extern int g_67a370;

void __cdecl fcn_00438af0(unsigned char a);
void __cdecl fcn_00438ac0(char* p, int a);
void __cdecl d3_TraverseSceneObjects(int list, char* p, int mask, void(__cdecl* fn)(void));
void __cdecl d3_ClearAuxSlotState(void);

/* ADDRESS: GOLDTL 0x00438b40 */
void __cdecl fcn_00438b40(char* p, int* v)
{
	if (p == ((char*)d3_ActiveCamera)) {
		fcn_00438af0(1);
	} else {
		fcn_00438ac0(p, 1);
	}
	d3_TraverseSceneObjects(g_67a370, p, 0xc0, d3_ClearAuxSlotState);
	*(int*) (p + 0x4c) = v[0];
	*(int*) (p + 0x50) = v[1];
	*(int*) (p + 0x54) = v[2];
}
