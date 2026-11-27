#include <math.h>

extern int g_104049c;
#include "GOLDTL.fcn_00440670_gconf.h"
extern double g_662958;
extern double g_662cd8;
extern double g_662cd0;
extern double g_662cc8;
extern double g_662cc0;
extern double g_662cb8;
extern double g_662cb0;
extern double g_662ad0;

int __cdecl d3_FindTextureVariant(int, int);

/* ADDRESS: GOLDTL 0x00440670 */
void __cdecl d3_UpdateAnimatedFloorMaterials(unsigned int time, unsigned int count, char* p)
{
	char* e;
	float dt;
	float t[4];
	int elapsed;
	int i;
	unsigned int c;
	double di;
	float* o;
	if (count <= 0) {
		return;
	}
	c = count;
	do {
		e = *(char**) p;
		if (e != 0) {
			if (*(unsigned char*) (e + 0x5c) > 0 && (*(unsigned char*) (e + 0x5e) & 0xf) > 0) {
				*(int*) (p + 4) = d3_FindTextureVariant(
				    (int) (e - (char*) g_104049c) / 0x70,
				    (time / g_662ea8[*(unsigned char*) (e + 0x5e) & 0xf]) % *(unsigned char*) (e + 0x5c));
			}
		}
		elapsed = time - *(unsigned int*) (p + 0x150);
		if (elapsed > 0) {
			dt = (float) elapsed;
			*(float*) (p + 0x148) = (float) fmod(dt * *(float*) (p + 0xc) + *(float*) (p + 0x148), 1.0);
			*(float*) (p + 0x14c) = (float) fmod(dt * *(float*) (p + 0x10) + *(float*) (p + 0x14c), 1.0);
			for (i = 0; i < 4; i++) {
				*(float*) (p + 0x138 + i * 4) = (float) fmod(dt * *(float*) (p + 0x18 + i * 4) + *(float*) (p + 0x138 + i * 4), 6.2831854820251465);
			}
			for (i = 0; i < 0x10; i++) {
				di = (double) i;
				o = (float*) (p + 0x38 + ((i & 3) + (i >> 2) * 4) * 0x10);
				t[0] = (float) sin((cos(2.7 * di) * 6.2831854820251465 + *(float*) (p + 0x138)) + di);
				t[1] = (float) cos((sin(3.1415927410125732 - g_662cd0 * di) * 6.2831854820251465 + *(float*) (p + 0x13c)) + di);
				t[2] = (float) sin(di - cos(g_662cc0 * di) * 6.2831854820251465 + *(float*) (p + 0x140) + 2.2);
				t[3] = (float) cos(di - sin(g_662cb0 * di + 3.1415927410125732) * 6.2831854820251465 + *(float*) (p + 0x144) + 4.0);
				o[0] = t[0] * *(float*) (p + 0x28);
				o[1] = t[1] * *(float*) (p + 0x2c);
				o[2] = t[2] * *(float*) (p + 0x30);
				o[3] = t[3] * *(float*) (p + 0x34);
			}
			*(int*) (p + 0x150) = time;
		}
		p += 0x158;
	} while (--c);
}
