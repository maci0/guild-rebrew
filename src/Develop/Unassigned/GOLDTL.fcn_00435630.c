

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

extern volatile int g_6b7fac;

void __cdecl fcn_00435630(char* o, char* name, char on)
{
	Slot* slots;
	int i;
	char *clock_base;

	if (o == 0) {
		return;
	}
	clock_base = *(char**) (o + 0x320);
	*(int*) (clock_base + 0x40) = g_6b7fac;
	slots = (Slot*) (o + 0x390);
	for (i = 0; i < 3; i++) {
		if (slots[i].name != 0 && strcmp(name, slots[i].name) == 0) {
			slots[i].active = on;
		}
	}
}
