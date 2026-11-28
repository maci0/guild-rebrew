

#include <string.h>

// SIZE 0x7c
typedef struct Slot {
	char* name;
	int a;
	int b;
	unsigned char bit0 : 1;
	unsigned char active : 1;
	int rest[27];
} Slot;

#include "Develop/Units/d3/d3_animation.h"
void __cdecl d3_BindAnimTrackNodes(int);
void __cdecl d3_UpdateObjectAnimPose(int);

/* ADDRESS: GOLDDE 0x0042eac0 */
void __cdecl d3_RemoveObjectAnimation(char* o, char* name)
{
	int h;
	Slot* slots;
	int i;

	if (o == 0) {
		return;
	}
	h = *(int*) (o + 0x320);
	slots = (Slot*) (o + 0x390);
	for (i = 0; i < 3; i++) {
		if (slots[i].name != 0 && strcmp(name, slots[i].name) == 0) {
			slots[i].active = 0;
			d3_ReleaseAnim(slots[i].name, 0);
			slots[i].name = 0;
		}
	}
	for (i = 0; i < 3; i++) {
		if (slots[i].name != 0) {
			break;
		}
	}
	if (i == 3) {
		o[0x4a0] = 0;
	}
	d3_BindAnimTrackNodes(h);
	d3_UpdateObjectAnimPose(h);
}
