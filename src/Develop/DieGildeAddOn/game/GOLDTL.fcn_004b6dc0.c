/* g_662a48 is owned (both targets) by src/GOLDTL.fcn_004b6fe0.c; g_6640e8 by
   src/GOLDTL.fcn_004b6f00.c; g_773d75 by src/GOLDTL.fcn_005b24b0.c. */
extern double g_662a48;
extern double g_6640e8;
extern unsigned char g_773d75;

#include <string.h>

unsigned char* __cdecl fcn_00508e40(int);
int __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);
void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void* __cdecl gm_FindNextFilteredEntity(void);


/* ADDRESS: GOLD 0x004b6bf0 */
/* ADDRESS: GOLDTL 0x004b6dc0 */
int __cdecl fcn_004b6dc0(void* a1)
{
	int arr[0xc];
	char buf[0x400];
	int n;
	double d;
	unsigned char* p;
	void* e;
	int i;
	int r;
	unsigned int len;

	i = 0;
	p = fcn_00508e40(*(int*) a1);
	if (p == 0) {
		return 1;
	}
	e = gm_StartFilteredEntitySearch(1, 5, 0x16);
	if (e != 0) {
		while (e != 0) {
			if (i >= 0xc) {
				break;
			}
			arr[i] = *(int*) ((char*) e + 1);
			i++;
			e = gm_FindNextFilteredEntity();
		}
	}
	if (i == 0) {
		return 0x400;
	}
	{
		gm_StartFilteredEntitySearch(1, 1, arr[gm_RandomMod(i) & 0xffff]);
		n = gm_RandomMod(5) & 0xffff;
		d = (double) n + g_662a48;
		n = gm_WalkEntityChain(*(short*) p);
		r = (int) (((double) n * d) * g_6640e8);
		fcn_0051af00(buf, *(unsigned short*) ((char*) a1 + 4) + 0x12e7, r);
		fcn_004c51a0(*(int*) a1, -1, g_773d75, r);
		len = strlen(buf);
		fcn_00545d40(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
		    0x100 < len, 0x603, 0);
		return 0;
	}
	return 0x400;
}
