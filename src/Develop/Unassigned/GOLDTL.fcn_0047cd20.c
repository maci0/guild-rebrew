#include "rgb.h"

typedef struct {
	char pad0[0x18];
	int* items;
} D2_SPRITE_BANK_SET;
// SIZE 0x1c

extern RGB_COLOR g_100f1b8;

int __cdecl d2_DrawTintedSprite(int, int, int, float, unsigned char, unsigned char, unsigned char);


/* ADDRESS: GOLDTL 0x0047cd20 */
int __cdecl d2_DrawBankSpriteColored(int x, int y, int surface, D2_SPRITE_BANK_SET* bank, int idx)
{
	if (bank == 0)
		return 0;
	return d2_DrawTintedSprite(x, y, bank->items[idx], 1.0f, g_100f1b8.r, g_100f1b8.g, g_100f1b8.b) != 0;
}
