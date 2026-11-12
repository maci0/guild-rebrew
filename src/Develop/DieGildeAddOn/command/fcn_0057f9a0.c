#include "Develop/DieGildeAddOn/game/game_player.h"

extern char g_7f4ca0[];
extern char g_675908[];
extern char g_6b5c60[];

int __cdecl fcn_00567030(char* slot, int* out1, int* out2);
void __cdecl cm_RequestChrMoveToUniverse(int h, int a, int b, char* tag);
void __cdecl fcn_004c5ba0(int h, int a, int b, char* tag);

/* ADDRESS: GOLDTL 0x0057f9a0 */
void __cdecl fcn_0057f9a0(int a0)
{
	char* p;
	int idx;
	char* slot;
	unsigned short key;
	int v1;
	int v2;

	if (a0 != 0) {
		return;
	}
	key = g_774970;
	idx = 0;
	p = g_7f4ca0 + 0x16c;
	for (;;) {
		char* rec = *(char**) p;
		if (rec != 0 && *(unsigned short*) (rec + 0x27) == key) {
			break;
		}
		p += 0x21c;
		idx++;
		if ((int) p >= (int)(g_7f4ca0 + 0x6556c)) {
			return;
		}
	}
	slot = g_7f4ca0 + idx * 0x21c;
	if (slot == 0) {
		return;
	}
	if (fcn_00567030(slot, &v1, &v2)) {
		cm_RequestChrMoveToUniverse(*(int*) (slot + 4), v1, v2, g_675908);
		fcn_004c5ba0(*(int*) (slot + 4), v1, v2, g_6b5c60);
	}
}
