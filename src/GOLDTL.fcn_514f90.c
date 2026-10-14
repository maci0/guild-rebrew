/* ADDRESS: GOLDTL 0x00514f90 */

// fcn_00511840 — if([a+0x220] in {3,4,1,0}) a[0x213] |= 4.

void __cdecl fcn_00511840(char* a)
{
	int t;
	t = *(int*) (a + 0x220);
	if (t == 3 || t == 4 || t == 1 || t == 0) {
		a[0x217] |= 1;
	}
}
