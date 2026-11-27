#include "rgb.h"

typedef struct {
	char pad0[0x18];
	int* items;
} D2_SPRITE_BANK_SET;
// SIZE 0x1c

extern RGB_COLOR g_100f1b8;

int __cdecl fcn_0047bdd0(int, int, int, float, unsigned char, unsigned char, unsigned char);


/* ADDRESS: GOLDTL 0x0047cd20 */
int __cdecl d2_DrawBankSpriteColored(int a1, int a2, int a3, D2_SPRITE_BANK_SET* s, int idx)
{
	if (s == 0)
		return 0;
	return fcn_0047bdd0(a1, a2, s->items[idx], 1.0f, g_100f1b8.r, g_100f1b8.g, g_100f1b8.b) != 0;
}
