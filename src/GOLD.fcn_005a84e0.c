int __cdecl fcn_00422620(int);

/* ADDRESS: GOLD 0x005a84e0 */
/* fcn_005a84e0 — recursively free a[0x48] then a. */

int __cdecl fcn_005a84e0(char* a)
{
	int c;
	c = *(int*) (a + 0x48);
	if (c != 0) {
		fcn_005a84e0((char*) c);
	}
	return fcn_00422620((int) a);
}
