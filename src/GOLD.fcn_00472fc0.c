// FUNCTION: GOLD 0x00472fc0
// SIZE: 267

#include <string.h>

typedef struct
{
	char pad00[0x18];
	int* list;
	short count;
	char pad1e[0x26c - 0x1e];
	int id;
	char pad270[0x3c4 - 0x270];
} fcn_00472fc0_Win;
// SIZE 0x3c4

typedef struct
{
	int id;
	char pad04[0x30 - 0x4];
	fcn_00472fc0_Win* parent;
	char pad34[0x2ec - 0x34];
} fcn_00472fc0_Ent;
// SIZE 0x2ec

extern fcn_00472fc0_Win g_00f8f120[]; /* 0x00f8f120 */
extern fcn_00472fc0_Ent** g_006ed964; /* 0x006ed964 */

void __cdecl fcn_00472f40(int id);

void __cdecl fcn_00472fc0(int win)
{
	fcn_00472fc0_Win* w;
	fcn_00472fc0_Ent* tmp[0x181];
	int i;
	int first;
	int last;
	int n;

	first = -1;
	last = -1;
	w = &g_00f8f120[win];
	for (i = 0x2ff; i >= 0; i--) {
		if (g_006ed964[i] != 0 && g_006ed964[i]->id == w->id) {
			last = i;
			break;
		}
		if (g_006ed964[i] != 0 && g_006ed964[i]->parent == w && first == -1) {
			first = i;
		}
	}
	if (first == -1) {
		first = last;
	}
	n = (first - last) * 4 + 4;
	memcpy(tmp, &g_006ed964[last], n);
	memmove(&g_006ed964[last], &g_006ed964[first + 1], 0xbf8 - first * 4);
	for (i = 0x2ff; i >= 0; i--) {
		if (g_006ed964[i] != 0) {
			break;
		}
	}
	memcpy(&g_006ed964[i + 1], tmp, n);
	for (i = 0; i < w->count; i++) {
		fcn_00472f40(w->list[i]);
	}
}
