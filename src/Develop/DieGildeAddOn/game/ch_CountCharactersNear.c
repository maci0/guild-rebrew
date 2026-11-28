extern void* g_1468ae0[];
extern void* ch_CharacterSlots[];
extern char g_10432c0[];

#include "client_scene_transform.h"

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00402720 */
int __cdecl ch_CountCharactersNear(int a1, int a2, float* position, float tolerance)
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
					if (CompareVector3WithinTolerance((float*) (*(char**) ((char*) e + 0x34) + 0x4c),
					                 position, tolerance) != 0) {
						count++;
					}
				}
			}
		}
		p++;
	} while ((int) p < 0x14696e0);
	return count;
}
#else
/* ADDRESS: GOLDTL 0x00402c00 */
int __cdecl ch_CountCharactersNear(int a1, int a2, float* pos, float tolerance)
{
	int count;
	void** cursor;
	void* obj;

	count = 0;
	cursor = ch_CharacterSlots;
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
#endif
