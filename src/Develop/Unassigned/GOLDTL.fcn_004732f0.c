

void __cdecl d2_ReleaseOverlaySprite(int);

void __cdecl d2_FreeAllSprites(void)
{
	int a;
	int v;

	for (a = 0x1015ec0; a < 0x1015f40; a += 4) {
		v = *(int*) a;
		if (v != 0) {
			d2_ReleaseOverlaySprite(v);
			*(int*) a = 0;
		}
	}
}
