// fcn_00479cc0 (client variant) — if(e){ e[0x2c]=a; e[0x30]=b; e[0x34]=a+c;
// e[0x38]=b+d; }.  The GOLD build stores the same four values at
// +0x24/+0x28/+0x2c/+0x30, so the two are twins, not one body.

/* ADDRESS: GOLDTL 0x00477070 */
void __cdecl d2_SetSurfaceClipRect(int x, int y, int w, int h, char* surf)
{
	if (surf != 0) {
		*(int*) (surf + 0x2c) = x;
		*(int*) (surf + 0x30) = y;
		*(int*) (surf + 0x34) = x + w;
		*(int*) (surf + 0x38) = y + h;
	}
}
