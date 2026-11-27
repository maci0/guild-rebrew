

int __cdecl d2_DrawTintedSprite(void*, int, void*, float, int, int, int);

int __cdecl d2_DrawSprite(void* x, int y, int unused, void* sprite)
{
	return d2_DrawTintedSprite(x, y, sprite, 1.0f, 0xc8, 0xc8, 0xc8) != 0;
}
