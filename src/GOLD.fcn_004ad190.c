// FUNCTION: GOLD 0x004ad190
// fcn_004ad190 — if((unsigned)[0x6f0720]<3) return [0x5edb78 + h*4]; return 0.

int __cdecl fcn_004ad190(void)
{
	unsigned int h;
	h = *(unsigned int*) 0x6f0720;
	if (h >= 3) {
		return 0;
	}
	return *(int*) (0x5edb78 + h * 4);
}
