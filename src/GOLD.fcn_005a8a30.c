// FUNCTION: GOLD 0x005a8a30
// fcn_005a8a30 — p=fcn_005a8690([a+1]); return p ? *(float*)(p+0x38) : *(float*)0x5eb780.

int __cdecl fcn_005a8690(int);

float __cdecl fcn_005a8a30(char* a)
{
	int p;
	p = fcn_005a8690(*(int*) (a + 1));
	if (p != 0) {
		return *(float*) (p + 0x38);
	}
	return *(float*) 0x5eb780;
}
