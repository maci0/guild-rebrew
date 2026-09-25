// FUNCTION: GOLDTL 0x5e4060
// SIZE: 66

int __cdecl fcn_005e4060(void)
{
	unsigned char* e;
	int r;

	r = 1;
	if (*(char*) 0x774964 != 0) {
		for (e = (unsigned char*) 0x7f4ca2; (int) e < 0x85a0a2; e += 0x21c) {
			if (e[6] > 0 && (e[0] == 6 || e[0] == 7) && *(int*) (e + 0x20a) != -1) {
				r = 0;
				break;
			}
		}
	} else {
		r = 0;
	}
	return r;
}
