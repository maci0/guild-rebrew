#include "Develop/Units/d3/d3_object.h"
extern void* g_14d0020[];
extern int g_67a370;
extern int g_6b8010;

void __cdecl fcn_00405130(char*);
void __cdecl fcn_00404560(char*);
int __cdecl fcn_00413190(int);
void __cdecl fcn_004432d0(int, int);

void __cdecl fcn_00403df0(char*);
void __cdecl m_FreeTracked(char*);

/* ADDRESS: GOLD 0x004028a0 */
/* ADDRESS: GOLDTL 0x004030e0 */

/* Removes an object from the live-object table and releases its scene
 * nodes. */
int __cdecl fcn_004030e0(char* obj)
{
	int i = 0;
	int saved;

	if (obj != 0) {
		while (((char**)g_14d0020)[i] != obj && i < 0x300) {
			i++;
		}
		if (i < 0x300) {
			((char**)g_14d0020)[i] = 0;
			*(int*) obj = -1;
			fcn_00405130(obj);
			if (*(int*) (obj + 0x34) != 0) {
				saved = -1;
				fcn_00404560(obj);
				if (g_67a370 != *(int*) (obj + 0x88)) {
					saved = g_6b8010;
					fcn_004432d0(fcn_00413190(*(int*) (obj + 0x88)), 1);
				}
				if (*(void (__cdecl**)(char*)) (obj + 0x228) != 0) {
					(*(void (__cdecl**)(char*)) (obj + 0x228))(obj);
				}
				d3_DestroyObject((D3_OBJECT*) (*(void**) (obj + 0x34)));
				*(int*) (obj + 0x34) = 0;
				if (*(void***) (obj + 0x124) != 0 && **(void***) (obj + 0x124) != 0) {
					d3_DestroyObject((D3_OBJECT*) (**(void***) (obj + 0x124)));
				}
				if (*(void**) (obj + 0x22c) != 0) {
					d3_DestroyObject((D3_OBJECT*) (*(void**) (obj + 0x22c)));
				}
				if (saved != -1) {
					fcn_004432d0(saved, 1);
				}
			}
			if (*(int*) (obj + 0x124) != 0) {
				fcn_00403df0(obj);
			}
			m_FreeTracked(obj);
			return 1;
		}
	}
	return 0;
}
