// SIZE 0x1c
typedef struct {
	char pad0[0x18];
	int* items;
} D2_HIGHLIGHT_SPRITE_SET;

int __cdecl d2_DrawTintedSprite(int, int, int, float, unsigned char, unsigned char, unsigned char);


/* ADDRESS: GOLDTL 0x0047ccd0 */
int __cdecl d2_DrawHighlightSprite(int x, int y, int unusedSurf, D2_HIGHLIGHT_SPRITE_SET* s, int idx)
{
	if (s == 0)
		return 0;
	return d2_DrawTintedSprite(x, y, s->items[idx], 1.0f, 0xff, 0xff, 0xff) != 0;
}
