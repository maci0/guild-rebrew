#include <stdio.h>

char* __cdecl fcn_00404300(char*, char*, char);
void __cdecl fcn_00407800(char*, int, char*);
void __cdecl fcn_004050c0(char*);
int __cdecl fcn_004042b0(char*);
void __cdecl fcn_004045c0(char*);

// FUNCTION: GOLD 0x00405d40
// FUNCTION: GOLDTL 0x4068e0

/* Steps a play-motion event: loads the motion on the first step, fires the
 * follow-up command at its trigger frame and finishes once it has run out. */
void __cdecl ch_TakingObject(char* ev)
{
	char* obj;
	char msg[0x100];

	obj = *(char**) (ev + 0x14);
	if (*(int*) (ev + 0xc) == 0) {
		if (ev[0xf0] != 0) {
			*(char**) (ev + 0x170) = fcn_00404300(obj, ev + 0xf0, 1);
		} else {
			fcn_00407800(obj, *(int*) (ev + 0x38), ev + 0x130);
			fcn_004050c0(ev);
			return;
		}
	}
	if (*(int*) (ev + 0x30) != 99999999) {
		if (*(int*) (obj + 0x80) != 0) {
			return;
		}
		if (*(int**) (obj + 0x70) != 0 && **(int**) (obj + 0x70) >= *(int*) (ev + 0x30)) {
			fcn_00407800(*(char**) (ev + 0x14), *(int*) (ev + 0x38), ev + 0x130);
			*(int*) (ev + 0x30) = 99999999;
		}
	}
	if (*(int*) (obj + 0x80) == 0 && fcn_004042b0(obj)) {
		if (*(int*) (ev + 0x30) != 99999999) {
			sprintf(msg, "ch_TakingObject(): object not taken yet (should be in frame:%i)!", *(int*) (ev + 0x30));
			fcn_00407800(*(char**) (ev + 0x14), *(int*) (ev + 0x38), ev + 0x130);
		}
		if (*(int*) (obj + 0x80) != 0) {
			sprintf(msg, "ch_TakingObject(): c->NextAnim still valid %s!\n", *(int*) (obj + 0x80));
		}
		fcn_004045c0(obj);
		fcn_004050c0(ev);
	}
}
