// FUNCTION: GOLDTL 0x437890
char* __cdecl fcn_00437890(char* a)
{
	int c;

	c = *(int*) (a + 0x1fc);
	a = *(char**) (a + 0x1f4);
	if (c == 0) {
		while (a != 0 && (a[0x214] & 1) == 0) {
			a = *(char**) (a + 0x1f4);
		}
	}
	return a;
}
