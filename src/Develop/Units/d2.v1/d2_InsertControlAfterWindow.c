#include <string.h>

typedef struct Slot {
	int id;
	int used;
	int value;
	int pad0c;
	int x;
	int y;
	int w;
	int h;
	int type;
	char pad24[0x30 - 0x24];
	int top;
	int bottom;
	char pad38[0x40 - 0x38];
	char* link;
	int pad44;
	int hidden48;
	int hidden4c;
	char* owner;
	char pad54[0x88 - 0x54];
	int result;
	char pad8c[0x2f4 - 0x8c];
} Slot;
// SIZE 0x2f4

extern char* d2_Controls;
extern void** d2_ZOrderStack;
extern char s_67d59c[];

#include "Develop/Units/Error/error_message.h"
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x0046f650 */
void __cdecl d2_InsertControlAfterWindow(int slot, char* parent)
{
	int i;
	Slot* p;

	for (i = 0; i < 0x3ff; i++) {
		if (((Slot**)d2_ZOrderStack)[i] == (Slot*) &((D2_CONTROL_TL*) d2_Controls)[slot]) {
			if (i == 0x3ff) {
				((Slot**)d2_ZOrderStack)[0x3ff] = 0;
			} else if (i < 0x3ff) {
				memmove(&((Slot**)d2_ZOrderStack)[i], &((Slot**)d2_ZOrderStack)[i + 1], 0xff8 - i * 4);
			}
			break;
		}
	}
	for (i = 0x3ff; i >= 0; i--) {
		p = ((Slot**)d2_ZOrderStack)[i];
		if (p && ((p->link == parent && p->type != 0x40) || p->id == *(int*) (parent + 0x27c))) {
			break;
		}
	}
	if (i >= 0) {
		if (i < 0x3ff) {
			memmove(&((Slot**)d2_ZOrderStack)[i + 2], &((Slot**)d2_ZOrderStack)[i + 1], 0xff8 - i * 4);
		}
		((Slot**)d2_ZOrderStack)[i + 1] = (Slot*) &((D2_CONTROL_TL*) d2_Controls)[slot];
	} else {
		ReportClientMessage(s_67d59c);
	}
}
