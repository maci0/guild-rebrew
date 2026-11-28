#include <stdio.h>

char* __cdecl ch_LoadCharacterMotion(char*, char*, char);
void __cdecl ch_SetBodyAttachment(char*, int, char*);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
int __cdecl ch_IsAnimationFinished(char*);
void __cdecl ch_CheckAniMorph(char*);

char* __cdecl ch_LoadCharacterMotion(char*, char*, char);
void __cdecl ch_SetBodyAttachment(char*, int, char*);
int __cdecl ch_IsAnimationFinished(char*);
void __cdecl ch_CheckAniMorph(char*);

/* Steps a play-motion event: loads the motion on the first step, fires the
 * follow-up command at its trigger frame and finishes once it has run out. */
/* ADDRESS: GOLDTL 0x004068e0 */
/* ADDRESS: GOLDDE 0x00405a80 */
void __cdecl ch_TakingObject(char* ev)
{
	char* obj;
	char msg[0x100];

	obj = *(char**) (ev + 0x14);
	if (*(int*) (ev + 0xc) == 0) {
		if (ev[0xf0] != 0) {
			*(char**) (ev + 0x170) = ch_LoadCharacterMotion(obj, ev + 0xf0, 1);
		} else {
			ch_SetBodyAttachment(obj, *(int*) (ev + 0x38), ev + 0x130);
			ch_RemoveQueueEntry(ev);
			return;
		}
	}
	if (*(int*) (ev + 0x30) != 99999999) {
		if (*(int*) (obj + 0x80) != 0) {
			return;
		}
		if (*(int**) (obj + 0x70) != 0 && **(int**) (obj + 0x70) >= *(int*) (ev + 0x30)) {
			ch_SetBodyAttachment(*(char**) (ev + 0x14), *(int*) (ev + 0x38), ev + 0x130);
			*(int*) (ev + 0x30) = 99999999;
		}
	}
	if (*(int*) (obj + 0x80) == 0 && ch_IsAnimationFinished(obj)) {
		if (*(int*) (ev + 0x30) != 99999999) {
			sprintf(msg, "ch_TakingObject(): object not taken yet (should be in frame:%i)!", *(int*) (ev + 0x30));
			ch_SetBodyAttachment(*(char**) (ev + 0x14), *(int*) (ev + 0x38), ev + 0x130);
		}
		if (*(int*) (obj + 0x80) != 0) {
			sprintf(msg, "ch_TakingObject(): c->NextAnim still valid %s!\n", *(int*) (obj + 0x80));
		}
		ch_CheckAniMorph(obj);
		ch_RemoveQueueEntry(ev);
	}
}

/* Steps a drop-object event: plays the drop motion and releases the object
 * at the motion's trigger frame. */
/* ADDRESS: GOLDTL 0x00406b50 */
/* ADDRESS: GOLDDE 0x00405cf0 */
void __cdecl ch_DroppingObject(char* ev)
{
	char* obj;
	char msg[0x100];

	obj = *(char**) (ev + 0x14);
	if (*(int*) (ev + 0xc) == 0) {
		if (*(int*) (obj + 0x64) == 0) {
			ch_RemoveQueueEntry(ev);
			return;
		}
		if (ev[0xf0] != 0) {
			*(char**) (ev + 0x174) = ch_LoadCharacterMotion(obj, ev + 0xf0, 1);
		}
		if (*(int*) (obj + 0x80) != 0) {
			return;
		}
		ch_SetBodyAttachment(*(char**) (ev + 0x14), *(int*) (ev + 0x38), 0);
		ch_RemoveQueueEntry(ev);
		return;
	}
	if (*(int*) (obj + 0x80) != 0) {
		return;
	}
	if (*(int**) (obj + 0x70) != 0 && **(int**) (obj + 0x70) >= *(int*) (ev + 0x30)) {
		ch_SetBodyAttachment(*(char**) (ev + 0x14), *(int*) (ev + 0x38), 0);
		*(int*) (ev + 0x30) = 99999999;
	}
	if (*(int*) (obj + 0x80) == 0 && ch_IsAnimationFinished(obj)) {
		if (*(int*) (ev + 0x30) != 99999999) {
			ch_SetBodyAttachment(*(char**) (ev + 0x14), *(int*) (ev + 0x38), 0);
			sprintf(msg, "ch_DroppingObject(): object not dropped yet (should be in frame:%i)!", *(int*) (ev + 0x30));
		}
		ch_CheckAniMorph(obj);
		ch_RemoveQueueEntry(ev);
	}
}
