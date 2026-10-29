


#include <math.h>

extern int g_67a370;
extern int g_772f10;

int __cdecl fcn_004d34b0(char*, char**);
void __cdecl fcn_004379a0(char*, int, int, int(__cdecl*)(char*, char**), char**);
void __cdecl fcn_00455350(char*, char*, float*);

char* __cdecl fcn_004d34f0(char* e)
{
	float best;
	float pos[4];
	char* list[32];
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
	fcn_004379a0(((char*)g_67a370), 0, 0xc0, fcn_004d34b0, list);
	c = *(char**) (*(char**) (e + 0x184) + 0x34);
	fcn_00455350(c, c + 0x4c, pos);
	for (i = 0; i < g_772f10; i++) {
		c = list[i];
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
