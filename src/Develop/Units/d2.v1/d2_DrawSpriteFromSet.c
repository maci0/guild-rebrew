// SIZE 0x1c
typedef struct {
	char pad0[0x18];
	int* items;
} D2_SPRITE_SET;

int __cdecl d2_DrawTintedSprite(int, int, int, float, unsigned char, unsigned char, unsigned char);


/* ADDRESS: GOLDTL 0x0047cba0 */
int __cdecl d2_DrawSpriteFromSet(int x, int y, int unused, D2_SPRITE_SET* set, int idx)
{
	if (set == 0)
		return 0;
	return d2_DrawTintedSprite(x, y, set->items[idx], 1.0f, 0xc8, 0xc8, 0xc8) != 0;
}
