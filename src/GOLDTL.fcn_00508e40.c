// FUNCTION: GOLDTL 0x508e40
// SIZE: 64

char* __cdecl fcn_00508e40(int a1)
{
	int i;
	int a;

	for (i = 0, a = 0x7f4ca4; a < 0x85a0a4; a += 0x21c, i++) {
		if (*(unsigned short*) (a - 4) != 0xffff && *(int*) a == a1) {
			return (char*) (0x7f4ca0 + i * 540);
		}
	}
	return 0;
}
