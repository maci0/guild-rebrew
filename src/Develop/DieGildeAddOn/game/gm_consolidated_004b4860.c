#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl fcn_00500d20(void*, void*);
extern unsigned char* lpGebaeudePROT;

int __cdecl fcn_00506fd0(int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);
void* __cdecl fcn_00502cd0(int, int, int, int, int);

/* ADDRESS: GOLD 0x004b46f0 */
/* ADDRESS: GOLDTL 0x004b4860 */
int __cdecl fcn_004b4860(unsigned short* key, char* x)
{
	unsigned char* e;

	e = gm_StartFilteredEntitySearch(2, 4, key[0], 5, 2);
	while (e != 0) {
		if (*e >= 5 && *(int*) (e + 0x65) == *(int*) (key + 2) &&
		    fcn_00500d20(e + 0x69, ((char*)&g_7f4c00)) > *(int*) (x + 0x18))
			return 1;
		e = gm_FindNextFilteredEntity();
	}
	return 0;
}

/* ADDRESS: GOLD 0x004b4760 */
/* ADDRESS: GOLDTL 0x004b48d0 */
int __cdecl fcn_004b48d0(unsigned short* a1)
{
	unsigned char* e;
	int x;
	int cnt;
	int ok;
	int j;
	char* row;
	unsigned short v;

	x = fcn_00506fd0(*((unsigned char*) a1 + 0x164));
	if (x == 0)
		return 0;
	cnt = 0;
	e = gm_StartFilteredEntitySearch(2, 4, a1[0], 5, x);
	while (cnt < 3 && e != 0) {
		ok = 1;
		row = ((char*)lpGebaeudePROT) + *e * 0x24d;
		for (j = 0; j < 0x40; j++) {
			v = *(unsigned short*) (row + 0x23 + j * 2);
			if (v == 0)
				break;
			if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, v & 0x7fff) == 0) {
				ok = 0;
				break;
			}
		}
		cnt += ok;
		e = gm_FindNextFilteredEntity();
	}
	if (cnt >= 3)
		return 1;
	return 0;
}
