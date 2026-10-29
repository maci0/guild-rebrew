


#include <string.h>

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

char* __cdecl gm_StartFilteredEntitySearch(int, int, ...);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_CheckEntityType(char*);
int __cdecl fcn_00505340(char*);
unsigned short __cdecl gm_RandomMod(unsigned short);
#include "client_scene_transform.h"

void __cdecl fcn_0056d8c0(char* u)
{
	int i;
	unsigned short k;
	char* list[0x100];
	char* e;
	char* p;
	unsigned short n;

	n = 0;
	k = 1;
	for (e = gm_StartFilteredEntitySearch(1, 6); e != 0; e = gm_FindNextFilteredEntity()) {
		if (gm_CheckEntityType(e) == 0 && fcn_00505340(e) == 0 && *(char**) (e + 0x61) != 0) {
			list[n++] = e;
		}
	}
	memset(u + 0xb0, 0xff, 0x3c);
	if (*(int*) (u + 0xac) == -1) {
		p = list[gm_RandomMod(n)];
		*(int*) (u + 0xac) = *(int*) (p + 1);
	} else {
		p = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0xac));
	}
	for (i = 0; i < n; i++) {
		if (k >= 0x10) {
			break;
		}
		e = list[i];
		if (e != p && fcn_00451840((float*) (*(char**) (e + 0x61) + 0x4c), (float*) (*(char**) (p + 0x61) + 0x4c), (float) *(int*) (u + 0xf0)) != 0) {
			*(int*) (u + 0xac + k++ * 4) = *(int*) (e + 1);
		}
	}
	*(int*) (u + 0x100) = 0;
	*(int*) (u + 0x104) = 0;
	*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
}
