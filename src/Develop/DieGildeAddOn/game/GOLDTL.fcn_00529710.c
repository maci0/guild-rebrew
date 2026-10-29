extern unsigned char* lpGebaeudePROT;
extern char g_10432c0[];




char* __cdecl fcn_00445600(char*, int, int, char*);
void __cdecl fcn_00455350(char*, char*, float*);
#include "client_scene_transform.h"

int __cdecl fcn_00529710(char* a, unsigned char* b)
{
	float r;
	float pos[4];
	char* d;
	char* x;

	r = 650.0f;
	if (lpGebaeudePROT[*b * 0x24d] == 10) {
		r = 1950.0f;
	}
	d = *(char**) (a + 0x3b);
	if (*(char**) (b + 0x61) != 0) {
		if (d == 0) {
			return 0;
		}
		if (*(char**) (d + 0x88) == g_10432c0) {
			x = fcn_00445600(*(char**) (b + 0x61), 0x100, 0, "dummy_TUER");
			if (x != 0) {
				fcn_00455350(x, x + 0x4c, pos);
			} else {
				fcn_00455350(*(char**) (b + 0x61), *(char**) (b + 0x61) + 0x4c, pos);
				r = 3250.0f;
			}
			if (fcn_00451840((float*) (*(char**) (d + 0x34) + 0x4c), pos, r) != 0) {
				return 1;
			}
		}
	}
	if (d != 0 && *(int*) (d + 0x2c) == *(int*) (b + 1)) {
		return 1;
	}
	return 0;
}
