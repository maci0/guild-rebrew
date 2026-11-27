
// fcn_00476b00 — for table: if(*p) fcn_00476890(*p, [0x6ed924]).

int __cdecl d2_DrawAnimatedSprite(int, int);

void __cdecl d2_DrawAllSprites(void)
{
	int p;
	for (p = 0xf8f0a0; p < 0xf8f120; p += 4) {
		if (*(int*) p != 0) {
			d2_DrawAnimatedSprite(*(int*) p, *(int*) 0x6ed924);
		}
	}
}
