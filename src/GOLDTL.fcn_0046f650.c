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

extern Slot* g_1015ea0;
extern Slot** g_772540;
extern char s_67d59c[];

void __cdecl fcn_0041d9e0(const char* msg);

// FUNCTION: GOLDTL 0x46f650
// SIZE: 235
void __cdecl fcn_0046f650(int slot, char* parent)
{
	int i;
	Slot* p;

	for (i = 0; i < 0x3ff; i++) {
		if (g_772540[i] == &g_1015ea0[slot]) {
			if (i == 0x3ff) {
				g_772540[0x3ff] = 0;
			} else if (i < 0x3ff) {
				memmove(&g_772540[i], &g_772540[i + 1], 0xff8 - i * 4);
			}
			break;
		}
	}
	for (i = 0x3ff; i >= 0; i--) {
		p = g_772540[i];
		if (p && ((p->link == parent && p->type != 0x40) || p->id == *(int*) (parent + 0x27c))) {
			break;
		}
	}
	if (i >= 0) {
		if (i < 0x3ff) {
			memmove(&g_772540[i + 2], &g_772540[i + 1], 0xff8 - i * 4);
		}
		g_772540[i + 1] = &g_1015ea0[slot];
	} else {
		fcn_0041d9e0(s_67d59c);
	}
}
