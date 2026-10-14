/* ADDRESS: GOLD 0x00461e60 */
// fcn_00461e60 — write LE 16-bit to [a+8][a+0x14].

void __cdecl fcn_00461e60(char* a, int v)
{
	char* base;
	int idx;
	base = *(char**) (a + 8);
	idx = *(int*) (a + 0x14);
	*(char*) (base + idx) = (char) (v >> 8);
	idx++;
	*(int*) (a + 0x14) = idx;
	*(char*) (base + idx) = (char) (v & 0xff);
	idx++;
	*(int*) (a + 0x14) = idx;
}
