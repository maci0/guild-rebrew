// FUNCTION: GOLDTL 0x51fd30
// SIZE: 32

// fcn_0051ad90 — a==-1 ? 0 : [0x6b5c20] + a*0x194.

int __cdecl fcn_0051ad90(int a)
{
	if (a == -1) {
		return 0;
	}
	return *(int*) 0x6b5c20 + a * 0x194;
}
