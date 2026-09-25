// FUNCTION: GOLD 0x565550
// SIZE: 347
// FUNCTION: GOLDTL 0x56d8c0
// SIZE: 347

#include <string.h>

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

extern struct pos14 g_7f4c00;

char* __cdecl gm_StartFilteredEntitySearch(int, int, ...);
char* __cdecl gm_AddObjekt(void);
int __cdecl gm_CheckEntityType(char*);
int __cdecl fcn_00505340(char*);
unsigned short __cdecl fcn_0042e410(unsigned short);
int __cdecl fcn_00451840(char*, char*, float);

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
	for (e = gm_StartFilteredEntitySearch(1, 6); e != 0; e = gm_AddObjekt()) {
		if (gm_CheckEntityType(e) == 0 && fcn_00505340(e) == 0 && *(char**) (e + 0x61) != 0) {
			list[n++] = e;
		}
	}
	memset(u + 0xb0, 0xff, 0x3c);
	if (*(int*) (u + 0xac) == -1) {
		p = list[fcn_0042e410(n)];
		*(int*) (u + 0xac) = *(int*) (p + 1);
	} else {
		p = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0xac));
	}
	for (i = 0; i < n; i++) {
		if (k >= 0x10) {
			break;
		}
		e = list[i];
		if (e != p && fcn_00451840(*(char**) (e + 0x61) + 0x4c, *(char**) (p + 0x61) + 0x4c, (float) *(int*) (u + 0xf0)) != 0) {
			*(int*) (u + 0xac + k++ * 4) = *(int*) (e + 1);
		}
	}
	*(int*) (u + 0x100) = 0;
	*(int*) (u + 0x104) = 0;
	*(struct pos14*) (u + 0x52) = g_7f4c00;
}
