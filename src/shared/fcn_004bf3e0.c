// FUNCTION: GOLD 0x004bf3e0
// SIZE: 36
// fcn_004bf3e0 — first i with [0xf812a0+i*8]!=-1 && [0xf812a4+i*8]==a.

int __cdecl fcn_004bf3e0(int a)
{
	int i;
	for (i = 0; i < 8; i++) {
		if (*(int*) (0xf812a0 + i * 8) != -1 &&
		    *(int*) (0xf812a4 + i * 8) == a) {
			return i;
		}
	}
	return -1;
}
