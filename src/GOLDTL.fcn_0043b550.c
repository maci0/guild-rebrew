// FUNCTION: GOLDTL 0x43b550
// SIZE: 44

char* __cdecl fcn_0043b550(int a1)
{
	int i;
	unsigned off;

	i = 0;
	for (off = 0; off < 0x120; off += 0x24, i++) {
		if (a1 == *(int*) (0x67a490 + off)) {
			return (char*) (0x67a470 + i * 0x24);
		}
	}
	return (char*) 0x67a594;
}
