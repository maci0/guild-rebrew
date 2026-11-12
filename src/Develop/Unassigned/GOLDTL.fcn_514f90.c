
/* fcn_00511840: if (*(int*)(a+0x220) is 3, 4, 1 or 0) a[0x217] |= 1. */

/* ADDRESS: GOLDTL 0x00514f90 */
void __cdecl fcn_00511840(char* a)
{
	int t;
	t = *(int*) (a + 0x220);
	if (t == 3 || t == 4 || t == 1 || t == 0) {
		a[0x217] |= 1;
	}
}
