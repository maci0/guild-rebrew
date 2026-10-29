#include "Develop/Units/d3/d3_camera.h"

void __cdecl fcn_00438100(char* obj, char* cam, char force);

/* ADDRESS: GOLDTL 0x00414ab0 */
void __cdecl fcn_00414ab0(float* a0, float* a1, char* ent)
{
	float* p;
	int i;

	if (*(int*) (ent + 0x1cc) == 0) {
		return;
	}
	if (!(*(unsigned char*) (ent + 0x216) & 0x20)) {
		fcn_00438100(ent, g_6b8014, 0);
	}
	p = (float*) ((float* (__cdecl*) (char*, char*, int))
		*(int*) (*(int*) (*(int*) (ent + 0x1cc) + 0x318) + 0x1f0))
		(ent, *(char**) (ent + 0x1cc), *(int*) (ent + 0x1ec) + 8);
	if (p == 0) {
		return;
	}
	a0[0] = p[0];
	a0[1] = p[1];
	a0[2] = p[2];
	a1[0] = p[0];
	a1[1] = p[1];
	a1[2] = p[2];
	i = 7;
	do {
		p += 0x14;
		a0[0] = (a0[0] < p[0]) ? a0[0] : p[0];
		a0[1] = (p[1] < a0[1]) ? p[1] : a0[1];
		a0[2] = (p[2] < a0[2]) ? p[2] : a0[2];
		a1[0] = (a1[0] < p[0]) ? p[0] : a1[0];
		a1[1] = (p[1] < a1[1]) ? a1[1] : p[1];
		a1[2] = (p[2] < a1[2]) ? a1[2] : p[2];
		i--;
	} while (i != 0);
}
