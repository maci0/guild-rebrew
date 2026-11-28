


#include "Develop/client_types.h"
#pragma pack(push, 1)
typedef Rec15_699058 Rec15;
// SIZE 0x15
#pragma pack(pop)

extern Rec15_699058 g_699058[37];

char* __cdecl gm_QueryEntities(int list, int a, int b, int c, ...);
char* __cdecl gm_AllocObjekt(int a, int b, int c);

/* ADDRESS: GOLDDE 0x004ef5d0 */
void __cdecl gm_InitBuildingStartingGoods(unsigned char* e)
{
	char* o;
	int i;
	int j;

	for (i = 0; i < 37; i++) {
		if (e[0] == g_699058[i].k) {
			o = gm_QueryEntities(*(int*) (e + 0x5d), 2, 6, 0, 0xff);
			if (o == 0) {
				o = gm_AllocObjekt(*(int*) (e + 1), 0xff, 1);
				if (o == 0) {
					continue;
				}
			}
			for (j = 0; j < 10; j++) {
				if (g_699058[i].ids[j] != 0 && !gm_QueryEntities(*(int*) (o + 0x14), 1, 0, g_699058[i].ids[j])) {
					gm_AllocObjekt(*(int*) (o + 2), g_699058[i].ids[j], 2);
				}
			}
		}
	}
}
