// SIZE 0x1c
typedef struct {
	char pad0[0x18];
	int* items;
} D2_SPRITE_BANK;

int __cdecl d2_DrawTintedSprite(int, int, int, float, unsigned char, unsigned char, unsigned char);


/* ADDRESS: GOLDTL 0x0047cc40 */
int __cdecl d2_DrawBankSpriteScaled(int x, int y, int unused, D2_SPRITE_BANK* bank, int idx, float scale)
{
	if (bank == 0)
		return 0;
	return d2_DrawTintedSprite(x, y, bank->items[idx], scale, 0xc8, 0xc8, 0xc8);
}
