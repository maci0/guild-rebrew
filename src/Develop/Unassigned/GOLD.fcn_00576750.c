
/* fcn_0057ecf0: return 0 if *a is 0x19, 0x1b or 0x29, otherwise 1. */

/* ADDRESS: GOLD 0x00576750 */
/* ADDRESS: GOLDTL 0x0057ecf0 */
int __cdecl fcn_0057ecf0(int* a)
{
	if (*a == 0x19 || *a == 0x1b || *a == 0x29) {
		return 0;
	}
	return 1;
}

