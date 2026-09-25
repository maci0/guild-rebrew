#include <string.h>

typedef struct
{
	int i[0x3cc / 4];
} fcn_0046f540_Win;
// SIZE 0x3cc

typedef struct
{
	int id;
	char pad04[0x40 - 0x4];
	fcn_0046f540_Win* parent;
	char pad44[0x2f4 - 0x44];
} fcn_0046f540_Ent;
// SIZE 0x2f4

extern fcn_0046f540_Win g_1015f40[];
extern fcn_0046f540_Ent** g_772540;

void __cdecl fcn_0046f4c0(int id);

// FUNCTION: GOLDTL 0x46f540
// SIZE: 263
void __cdecl fcn_0046f540(int win)
{
	fcn_0046f540_Win* w;
	fcn_0046f540_Ent* tmp[0x181];
	fcn_0046f540_Ent* p;
	int i;
	int first;
	int last;
	int n;

	first = -1;
	last = -1;
	w = &g_1015f40[win];
	for (i = 0x3ff; i >= 0; i--) {
		if (g_772540[i] != 0 && g_772540[i]->id == w->i[0x27c / 4]) {
			last = i;
			break;
		}
		if (g_772540[i] != 0 && g_772540[i]->parent == w && first == -1) {
			first = i;
		}
	}
	if (first == -1) {
		first = last;
	}
	n = (first - last) * 4 + 4;
	memcpy(tmp, &g_772540[last], n);
	memmove(&g_772540[last], &g_772540[first + 1], 0xff8 - first * 4);
	for (i = 0x3ff; i >= 0; i--) {
		if (g_772540[i] != 0) {
			break;
		}
	}
	memcpy(&g_772540[i + 1], tmp, n);
	for (i = 0; i < w->i[0x2c / 4]; i++) {
		fcn_0046f4c0(((int*) w->i[0x28 / 4])[i]);
	}
}
