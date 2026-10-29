extern void* g_1468ae0[];
extern char g_10432c0[];


#include "client_scene_transform.h"

int __cdecl fcn_00402720(int a1, int a2, float* a3, float a4)
{
	int count;
	void** p;
	void* e;

	count = 0;
	p = g_1468ae0;
	do {
		e = *p;
		if (e != 0) {
			if (a1 == -1 ||
			    *(int*) ((char*) e + 0x88) == (int) (g_10432c0 + a1 * 0x3e0)) {
				if (a2 != 0 ||
				    *(int*) (*(int*) ((char*) e + 0x34) + 0x218) != 1) {
					if (fcn_00451840((float*) (*(char**) ((char*) e + 0x34) + 0x4c),
					                 a3, a4) != 0) {
						count++;
					}
				}
			}
		}
		p++;
	} while ((int) p < 0x14696e0);
	return count;
}
