// FUNCTION: GOLD 0x00422c30
// FUNCTION: GOLDTL 0x41e3e0

int __cdecl fcn_0041e350(void*);

int __cdecl fcn_0041e3e0(int a1, int* a2)
{
	if (a1 != 0 && a2 != 0) {
		a2[0] = a1;
		a2[1] = 0;
		a2[2] = 0;
		return fcn_0041e350(a2);
	}
	return 0;
}
