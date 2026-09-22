// FUNCTION: GOLDTL 0x545580
// SIZE: 48

int __cdecl fcn_00545580(int a1, int a2, int a3)
{
	if (a1 < 0 || a1 >= 0xa7) {
		return 1;
	}
	((int*) 0x7d1d80)[a1] = a2;
	((int*) 0x7dc440)[a1] = a3;
	return 0;
}
