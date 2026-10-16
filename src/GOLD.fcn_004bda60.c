/* ADDRESS: GOLD 0x004bda60 */

int __cdecl fcn_004bda60(char* p, char* target)
{
	int n;

	for (n = 0; p != 0; n++) {
		if (target == p) {
			return n;
		}
		p = *(char**) (p + 0x3c);
	}
	return n;
}
