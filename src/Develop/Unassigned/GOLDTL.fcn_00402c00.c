extern void* g_14d0020[];
extern char g_10432c0[];


#include "client_scene_transform.h"

int __cdecl fcn_00402c00(int a1, int a2, float* pos, float tolerance)
{
	int count;
	void** cursor;
	void* obj;

	count = 0;
	cursor = g_14d0020;
	do {
		obj = *cursor;
		if (obj != 0) {
			if (a1 == -1 ||
			    *(int*) ((char*) obj + 0x88) == (int) (g_10432c0 + a1 * 0x3dc)) {
				if (a2 != 0 ||
				    *(int*) (*(int*) ((char*) obj + 0x34) + 0x218) != 1) {
					if (CompareVector3WithinTolerance((float*) (*(char**) ((char*) obj + 0x34) + 0x4c),
					                 pos, tolerance) != 0) {
						count++;
					}
				}
			}
		}
		cursor++;
	} while ((int) cursor < 0x14d0c20);
	return count;
}
