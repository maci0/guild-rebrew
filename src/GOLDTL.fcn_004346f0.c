/* ADDRESS: GOLD 0x00434a80 */
/* ADDRESS: GOLDTL 0x004346f0 */

int __cdecl fcn_004346f0(char* o)
{
	int r = 0;
	char* m;

	if (o == 0 || (m = *(char**) (o + 0x15c)) == 0) {
		return -1;
	}
	if (*(int*) (m + 0xbc) != 0) {
		r = *(int*) (o + 0x140) * 12;
	}
	if (*(int*) (m + 0xb4) != 0) {
		r += *(int*) (o + 0x140) * 3;
	}
	if (*(int*) (m + 0xb8) != 0) {
		r += *(int*) (o + 0x140) * 3;
	}
	return (r + 0xc0) * *(int*) (o + 0x148) + 0x16c;
}
