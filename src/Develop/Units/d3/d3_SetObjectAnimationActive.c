#include <string.h>

/* SIZE 0x7c */
typedef struct Slot {
	char* name;
	int a;
	int b;
	unsigned char bit0 : 1;
	unsigned char active : 1;
	int rest[27];
} Slot;

#if defined(REBREW_GOLD)
extern int gm_GameTicks;

/* ADDRESS: GOLD 0x00435870 */
void __cdecl d3_SetObjectAnimationActive(char* obj, char* name, unsigned char bit)
{
	char* rec;
	int n;

	if (obj == 0) {
		return;
	}
	*(int*) (*(int*) (obj + 0x18) + 0x40) = gm_GameTicks;
	rec = obj + 0x90;
	n = 3;
	do {
		if (*(char**) (rec - 0xc) != 0 && strcmp(name, *(char**) (rec - 0xc)) == 0) {
			*rec = (char) ((*rec & ~2) | ((bit & 1) << 1));
		}
		rec += 0x7c;
		n--;
	} while (n != 0);
}
#else
extern volatile int gm_GameTicks;

/* ADDRESS: GOLDTL 0x00435630 */
/* ADDRESS: GOLDDE 0x0042ebf0 */
void __cdecl d3_SetObjectAnimationActive(char* obj, char* name, unsigned char bit)
{
	Slot* slots;
	int i;
	char *clock_base;

	if (obj == 0) {
		return;
	}
	clock_base = *(char**) (obj + 0x320);
	*(int*) (clock_base + 0x40) = gm_GameTicks;
	slots = (Slot*) (obj + 0x390);
	for (i = 0; i < 3; i++) {
		if (slots[i].name != 0 && strcmp(name, slots[i].name) == 0) {
			slots[i].active = bit;
		}
	}
}
#endif
