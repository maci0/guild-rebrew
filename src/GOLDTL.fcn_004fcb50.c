#include <string.h>

extern char g_7f4ca0[];

int __cdecl fcn_004fffb0(unsigned short id);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_004eb180(int k);
void __cdecl fcn_004fc600(unsigned short id, int* out, int c);
void __cdecl fcn_004fc700(unsigned short id, int* out, int c);
void __cdecl fcn_004fca70(unsigned short id, int* out, int c);
void __cdecl fcn_004fc800(unsigned short id, int* out, int c);
void __cdecl fcn_004fc940(unsigned short id, int* out, int c);

// FUNCTION: GOLD 0x4fa4b0
// FUNCTION: GOLDTL 0x004fcb50
int __cdecl fcn_004fcb50(unsigned short id, int* out, int c)
{
	int o;

	o = id * 0x21c;
	memset(out, 0, 0xe * sizeof(int));
	if (*(unsigned short*) (g_7f4ca0 + o) == 0xffff) {
		return 0;
	}
	if (*(unsigned char*) (g_7f4ca0 + o + 8) == 0) {
		return 0;
	}
	if (fcn_004fffb0(id) != 0) {
		return 0;
	}
	if (fcn_004eb180(gm_MapEntityStatRange(*(unsigned char*) (g_7f4ca0 + o + 0x164))) != 0) {
		fcn_004fc700(id, out, c);
	} else {
		fcn_004fc600(id, out, c);
	}
	fcn_004fca70(id, out, c);
	if (*(int*) (g_7f4ca0 + o + 0x1a8) > 0) {
		fcn_004fc800(id, out, c);
	}
	fcn_004fc940(id, out, c);
	return 1;
}
