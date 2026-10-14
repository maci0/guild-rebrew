/* ADDRESS: GOLD 0x00468610 */
// fcn_00468610 — if(!a || !a[0x7c/4]) return -102; return *(int*)(a[0x7c/4]+0x18).

int __cdecl fcn_00468610(char* a)
{
	char* p;
	if (a == 0) {
		return -102;
	}
	p = *(char**) (a + 0x7c);
	if (p == 0) {
		return -102;
	}
	return *(int*) (p + 0x18);
}
