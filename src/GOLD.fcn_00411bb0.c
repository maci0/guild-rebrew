/* ADDRESS: GOLD 0x00411bb0 */

int __cdecl fcn_00411bb0(void)
{
	int i;
	int a;

	i = 0;
	for (a = 0xfd7f75; a < 0xfe7775; a += 0x3e0, i++) {
		if (*(char*) (a - 1) == 0 && *(char*) a == 0) {
			return i;
		}
	}
	return -1;
}
