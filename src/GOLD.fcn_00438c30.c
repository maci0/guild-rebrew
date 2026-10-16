/* ADDRESS: GOLD 0x00438c30 */

char* __cdecl fcn_00438c30(char* a)
{
	int c;

	c = *(int*) (a + 0x1f8);
	a = *(char**) (a + 0x1f0);
	if (c == 0) {
		while (a != 0 && (a[0x210] & 1) == 0) {
			a = *(char**) (a + 0x1f0);
		}
	}
	return a;
}
