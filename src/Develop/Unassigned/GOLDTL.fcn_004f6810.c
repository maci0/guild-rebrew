
/* ADDRESS: GOLDTL 0x004f6810 */
int __cdecl fcn_004f6810(char* a1, unsigned int kind)
{
	int r;

	r = 0;
	if (a1 == 0) {
		return -1;
	}
	if (kind >= 10) {
		return -3;
	}
	if (kind == 5) {
		if (a1[0x166] == 0) {
			r = -4;
		}
	} else if (kind == 7) {
		if (a1[0xd] == 0) {
			r = -4;
		}
	}
	return r;
}
