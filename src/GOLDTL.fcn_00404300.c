#include <stdio.h>

void __cdecl fcn_0042e540(char*);
char* __cdecl fcn_00433ba0(char*);
int __cdecl fcn_0065f220(const char*, const char*);
char* __cdecl fcn_0044c620(char*, char*, int);

// FUNCTION: GOLDTL 0x404300
// SIZE: 262

/* Loads a character's motion into its motion slot and takes a reference. */
char* __cdecl fcn_00404300(char* obj, char* name, char slot)
{
	int looped;
	char* ani_obj;
	char ani[0x110];
	char path[0x110];

	looped = 0;
	if (*(char**) (obj + 0x80) != 0) {
		return 0;
	}
	fcn_0042e540(name);
	sprintf(path, "character/%s/%s_%s.baf", obj + 0x130, name, obj + 0x130);
	sprintf(ani, "%s_%s", name, obj + 0x130);
	fcn_0042e540(ani);
	ani_obj = fcn_00433ba0(ani);
	if (fcn_0065f220(name, "bewegung/gehen") == 0 || fcn_0065f220(name, "bewegung/karren_ziehen") == 0) {
		looped = 1;
	}
	if (ani_obj == 0) {
		*(char**) (obj + 0x80) = fcn_0044c620(path, ani, looped);
	} else {
		*(char**) (obj + 0x80) = ani_obj;
	}
	if (*(char**) (obj + 0x80) == 0) {
		return 0;
	}
	obj[0x84] = slot;
	(*(int*) (*(char**) (obj + 0x80) + 0x14c))++;
	return *(char**) (obj + 0x80);
}
