extern char d2_OverlaySprites[];


// fcn_00472a50 — table: if(n && *(int*)n&8) { fcn_00476850(n); *p=0; } else if(n) *(int*)n|=4.

int __cdecl d2_FreeOverlaySprite(int);

/* ADDRESS: GOLDDE 0x00466330 */
void __cdecl d2_SweepFadeOverlays(void)
{
	int p;
	for (p = (int) &d2_OverlaySprites; p < ((int) &d2_OverlaySprites + 0x80); p += 4) {
		int n;
		int f;
		n = *(int*) p;
		if (n != 0) {
			f = *(int*) n;
			if (f & 8) {
				d2_FreeOverlaySprite(n);
				*(int*) p = 0;
			} else {
				*(int*) n = f | 4;
			}
		}
	}
}
