// SIZE 0x1c
typedef struct {
	char pad0[0x18];
	int* items;
} D2_SPRITE_FRAME_SET;

int __cdecl fcn_0047bdd0(int, int, int, float, unsigned char, unsigned char, unsigned char);


/* ADDRESS: GOLDTL 0x0047cbf0 */
int __cdecl d2_DrawDimmedSpriteFrame(int x, int y, int unusedSurface, D2_SPRITE_FRAME_SET* set, int idx)
{
	if (set == 0)
		return 0;
	return fcn_0047bdd0(x, y, set->items[idx], 1.0f, 0x80, 0x80, 0x80) != 0;
}
