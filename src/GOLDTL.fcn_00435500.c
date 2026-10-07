// FUNCTION: GOLDTL 0x435500

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

void __cdecl fcn_00434760(char*, int);
void __cdecl fcn_004315c0(int);
void __cdecl fcn_004316c0(int);

void __cdecl fcn_00435500(char* o, char* name)
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
			fcn_00434760(slots[i].name, 0);
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
	fcn_004315c0(h);
	fcn_004316c0(h);
}
