#include "Develop/Units/d3/d3_camera.h"

void __cdecl d3_UpdateObjectCameraTransform(char* obj, char* cam, char force);

/* ADDRESS: GOLDTL 0x00414ab0 */
void __cdecl fcn_00414ab0(float* outA, float* outB, char* ent)
{
	float* p;
	int i;

	if (*(int*) (ent + 0x1cc) == 0) {
		return;
	}
	if (!(*(unsigned char*) (ent + 0x216) & 0x20)) {
		d3_UpdateObjectCameraTransform(ent, d3_ActiveCamera, 0);
	}
	p = (float*) ((float* (__cdecl*) (char*, char*, int))
		*(int*) (*(int*) (*(int*) (ent + 0x1cc) + 0x318) + 0x1f0))
		(ent, *(char**) (ent + 0x1cc), *(int*) (ent + 0x1ec) + 8);
	if (p == 0) {
		return;
	}
	outA[0] = p[0];
	outA[1] = p[1];
	outA[2] = p[2];
	outB[0] = p[0];
	outB[1] = p[1];
	outB[2] = p[2];
	i = 7; p += 0x14;
	do {

		outA[0] = (outA[0] < p[0]) ? outA[0] : p[0];
		outA[1] = ((double) outA[1] < (double) p[1]) ? outA[1] : p[1];
		outA[2] = ((double) outA[2] < (double) p[2]) ? outA[2] : p[2];
		outB[0] = (outB[0] > p[0]) ? outB[0] : p[0];
		outB[1] = ((double) outB[1] > (double) p[1]) ? outB[1] : p[1];
		outB[2] = ((double) outB[2] > (double) p[2]) ? outB[2] : p[2];
		i--; p += 0x14;
	} while (i != 0);
}
