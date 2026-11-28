extern char d2_OverlaySprites[];


void __cdecl d2_ReleaseOverlaySprite(int);

/* ADDRESS: GOLDDE 0x00466300 */
void __cdecl d2_FreeAllSprites(void)
{
	int a;
	int v;

	for (a = (int) &d2_OverlaySprites; a < ((int) &d2_OverlaySprites + 0x80); a += 4) {
		v = *(int*) a;
		if (v != 0) {
			d2_ReleaseOverlaySprite(v);
			*(int*) a = 0;
		}
	}
}
