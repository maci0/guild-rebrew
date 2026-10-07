// FUNCTION: GOLDTL 0x464600
int __cdecl fcn_00464600(const char* fileName1, const char* fileName2)
{
	for (;;) {
		char c1 = *(fileName1++);
		char c2 = *(fileName2++);
		if ((c1 >= 'a') && (c1 <= 'z')) {
			c1 -= 0x20;
		}
		if ((c2 >= 'a') && (c2 <= 'z')) {
			c2 -= 0x20;
		}
		if (c1 == '\0') {
			return ((c2 == '\0') ? 0 : -1);
		}
		if (c2 == '\0') {
			return 1;
		}
		if (c1 < c2) {
			return -1;
		}
		if (c1 > c2) {
			return 1;
		}
	}
}
