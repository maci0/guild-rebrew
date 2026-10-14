#include "Develop/Units/d3/d3_object.h"



extern char g_868354[][0x2f4];
extern int g_7746a0;
extern char* g_7746a4;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern int g_14ce8cc;
extern int g_14ce8e0;
extern int g_774654;
extern char s_6a41a4[];

int __cdecl sprintf(char*, const char*, ...);
char* __cdecl fcn_005a3580(char*);
char* __cdecl fcn_005338d0(char*, char*, int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
char* __cdecl fcn_00443bf0(float, float, int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);
void __cdecl fcn_005a31b0(char*, int);

void __cdecl fcn_00533880(void);
void __cdecl fcn_00532ef0(void);

void __cdecl fcn_005a3680(void)
{
	char* items[4];
	int i;
	char* e;

	items[0] = 0;
	items[1] = 0;
	items[2] = 0;
	items[3] = 0;
	for (i = 0; i < 3; i++) {
		items[i] = fcn_005a3580(g_868354[i]);
		sprintf(items[i], s_6a41a4, g_868354[i]);
		fcn_005338d0(items[i], g_868354[i], 0);
	}
	fcn_00473a90(0, 0);
	fcn_005338a0();
	if (fcn_005373e0((void*) fcn_005a3680, 0x677d7) != 0) {
		do {
			(*(char**)&g_7746a0) = 0;
			for (i = 0; i < 3; i++) {
				fcn_005338d0(items[i], g_868354[i], 0);
			}
			g_7746a4 = fcn_00443bf0((float) g_14ce8c0, (float) g_14ce8c2, 0x60, 1);
			if (g_14ce8cc != 0 && g_7746a4 != 0) {
				(*(char**)&g_7746a0) = g_7746a4;
				for (i = 0; i < 3; i++) {
					if ((*(char**)&g_7746a0) == items[i]) {
						for (e = gm_StartFilteredEntitySearch(1, 0, 0x47); e != 0; e = gm_AddObjekt()) {
							if (*(int*) (e + 0x65) == i + 1) {
								fcn_005a31b0(e, 1);
								break;
							}
						}
					}
				}
			}
			else if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
		} while (fcn_005373e0((void*) fcn_005a3680, 0x677d7) != 0);
	}
	fcn_005338a0();
	for (i = 0; i < 3; i++) {
		if (items[i] != 0) {
			d3_DestroyObject((D3_OBJECT*) (items[i]));
		}
	}
	fcn_00533880();
	fcn_00532ef0();
}
