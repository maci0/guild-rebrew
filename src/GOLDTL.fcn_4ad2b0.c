// FUNCTION: GOLDTL 0x4ad2b0
// SIZE: 32

// fcn_004ad190 — if((unsigned)[0x7728d0]<3) return [0x664e10 + h*4]; return 0.

int __cdecl fcn_004ad190(void)
{
	unsigned int h;
	h = *(unsigned int*) 0x7728d0;
	if (h >= 3) {
		return 0;
	}
	return *(int*) (0x664e10 + h * 4);
}
