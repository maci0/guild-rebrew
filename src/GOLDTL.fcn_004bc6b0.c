#include <string.h>

extern int g_67a370;

unsigned short __cdecl fcn_0042e410(unsigned short);
int __cdecl fcn_00406340(char*, char*, int);
int __cdecl fcn_004bc8a0(int*, int, float*);
char __cdecl fcn_0045b990(int, float*, int*, int*, int*);
char* __cdecl fcn_0040c120(char*, int, int, int, int);

// FUNCTION: GOLD 0x004bc1a0
// FUNCTION: GOLDTL 0x4bc6b0

void __cdecl fcn_004bc6b0(char** a1)
{
	int x;
	int g;
	int y;
	int z;
	float pts[8][4];
	float* pt;
	int n;
	char* o;

	if (*(int*) (a1[0] + 0x128) != 0)
		return;
	if (fcn_0042e410(0x64) > 0x14) {
		if (fcn_0042e410(0x64) > 0x32)
			fcn_00406340(a1[0], "bewegung/stehen", fcn_0042e410(3) + 1);
		else
			fcn_00406340(a1[0], "bewegung/fressen", fcn_0042e410(3) + 1);
		return;
	}
	g = *(int*) (((char*)g_67a370) + 0xb0);
	n = fcn_0042e410(3) + 1;
	n = fcn_004bc8a0((int*) (a1 + 4), n, pts[0]);
	if (n <= 0)
		return;
	for (pt = pts[0]; n != 0; n--, pt += 4) {
		if (fcn_0045b990(g, pt, &x, &y, &z) != 0) {
			o = fcn_0040c120(a1[0], 0x2d, x, y, 0);
			strcpy(o + 0x70, "anm_UpdateSheep");
		}
	}
}
