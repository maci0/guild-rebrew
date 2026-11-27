// SIZE 0x1c
typedef struct {
	char pad0[0x18];
	int* items;
} D2_SPRITE_SET;

int __cdecl fcn_0047bdd0(int, int, int, float, unsigned char, unsigned char, unsigned char);


/* ADDRESS: GOLDTL 0x0047cba0 */
int __cdecl d2_DrawSpriteFromSet(int x, int y, int a3, D2_SPRITE_SET* s, int idx)
{
	if (s == 0)
		return 0;
	return fcn_0047bdd0(x, y, s->items[idx], 1.0f, 0xc8, 0xc8, 0xc8) != 0;
}
