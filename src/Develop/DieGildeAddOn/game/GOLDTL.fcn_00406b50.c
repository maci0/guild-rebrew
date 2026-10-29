#include <stdio.h>

char* __cdecl fcn_00404300(char*, char*, char);
void __cdecl fcn_00407800(char*, int, char*);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
int __cdecl fcn_004042b0(char*);
void __cdecl ch_CheckAniMorph(char*);


/* Steps a drop-object event: plays the drop motion and releases the object
 * at the motion's trigger frame. */
/* ADDRESS: GOLDTL 0x00406b50 */
void __cdecl ch_DroppingObject(char* ev)
{
	char* obj;
	char msg[0x100];

	obj = *(char**) (ev + 0x14);
	if (*(int*) (ev + 0xc) == 0) {
		if (*(int*) (obj + 0x64) == 0) {
			fcn_004050c0(ev);
			return;
		}
		if (ev[0xf0] != 0) {
			*(char**) (ev + 0x174) = fcn_00404300(obj, ev + 0xf0, 1);
		}
		if (*(int*) (obj + 0x80) != 0) {
			return;
		}
		fcn_00407800(*(char**) (ev + 0x14), *(int*) (ev + 0x38), 0);
		fcn_004050c0(ev);
		return;
	}
	if (*(int*) (obj + 0x80) != 0) {
		return;
	}
	if (*(int**) (obj + 0x70) != 0 && **(int**) (obj + 0x70) >= *(int*) (ev + 0x30)) {
		fcn_00407800(*(char* volatile*) (ev + 0x14), *(int*) (ev + 0x38), 0);
		*(int*) (ev + 0x30) = 99999999;
	}
	if (*(int*) (obj + 0x80) == 0 && fcn_004042b0(obj)) {
		if (*(int*) (ev + 0x30) != 99999999) {
			fcn_00407800(*(char**) (ev + 0x14), *(int*) (ev + 0x38), 0);
			sprintf(msg, "ch_DroppingObject(): object not dropped yet (should be in frame:%i)!", *(int*) (ev + 0x30));
		}
		ch_CheckAniMorph(obj);
		fcn_004050c0(ev);
	}
}
