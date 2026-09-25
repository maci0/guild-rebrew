// FUNCTION: GOLD 0x004d25a0
// SIZE: 170
// FUNCTION: GOLDTL 0x4d3600
// SIZE: 170

#include <math.h>

extern char* g_67a370;
extern int g_772f10;
extern char* g_9b46c0[];

int __cdecl fcn_004d35b0(char*, char*);
void __cdecl fcn_004379a0(char*, int, int, int(__cdecl*)(char*, char*), char*);
void __cdecl fcn_00455350(char*, char*, float*);

char* __cdecl fcn_004d3600(char* e)
{
	float best;
	float pos[4];
	char* res;
	char* c;
	float dx;
	float dy;
	float dz;
	float d;
	int i;

	res = 0;
	best = 1000000.0f;
	g_772f10 = 0;
	fcn_004379a0(g_67a370, 0, 0x40, fcn_004d35b0, e);
	c = *(char**) (*(char**) (e + 0x184) + 0x34);
	fcn_00455350(c, c + 0x4c, pos);
	for (i = 0; i < g_772f10; i++) {
		c = g_9b46c0[i];
		dx = pos[0] - *(float*) (c + 0x4c);
		dy = pos[1] - *(float*) (c + 0x50);
		dz = pos[2] - *(float*) (c + 0x54);
		d = (float) sqrt(dz * dz + dy * dy + dx * dx);
		if (d < best) {
			best = d;
			res = c;
		}
	}
	return res;
}
