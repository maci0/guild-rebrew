// FUNCTION: GOLD 0x00564580
// FUNCTION: GOLDTL 0x56c8f0

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned char* g_868050;

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AddObjekt(void);
int __cdecl gm_CheckEntityType(char*);
int __cdecl fcn_00505340(char*);
unsigned short __cdecl fcn_0042e410(unsigned short);
void __cdecl fcn_00455350(char*, char*, float*);
int __cdecl fcn_00451840(float*, float*, float);

void __cdecl fcn_0056c8f0(char* u)
{
	unsigned short n;
	unsigned short m;
	float v2[4];
	float v1[4];
	char* list[0x100];
	char* e;
	char* t;
	char* pick;
	int i;

	n = 0;
	m = 1;
	for (e = gm_StartFilteredEntitySearch(1, 6); e != 0; e = gm_AddObjekt()) {
		t = ((char*)g_868050) + *(unsigned char*) e * 0x24d;
		if (gm_CheckEntityType(e) == 0 && fcn_00505340(e) == 0 && *(char**) (e + 0x61) != 0 && *t != 3) {
			list[n++] = e;
		}
	}
	for (i = 0; i < 15; i++) {
		((int*) (u + 0xb0))[i] = -1;
	}
	if (*(int*) (u + 0xac) == -1) {
		pick = list[fcn_0042e410(n)];
		*(int*) (u + 0xac) = *(int*) (pick + 1);
	} else {
		pick = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0xac));
	}
	for (i = 0; i < n && m < 0x10; i++) {
		e = list[i];
		fcn_00455350(*(char**) (e + 0x61), *(char**) (e + 0x61) + 0x4c, v1);
		fcn_00455350(*(char**) (pick + 0x61), *(char**) (pick + 0x61) + 0x4c, v2);
		if (e != pick && fcn_00451840(v1, v2, (float) *(int*) (u + 0xf0)) != 0) {
			((int*) (u + 0xac))[m++] = *(int*) (e + 1);
		}
	}
	*(int*) (u + 0xec) = *(int*) (pick + 1);
	*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
	if (*(unsigned short*) (u + 0x56) > 0x14) {
		*(unsigned short*) (u + 0x56) = fcn_0042e410(10) + 8;
		(*(int*) (u + 0x52))++;
	}
	*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
	if (*(unsigned short*) (u + 0x56) < 7) {
		*(unsigned short*) (u + 0x56) = fcn_0042e410(10) + 8;
	}
}
