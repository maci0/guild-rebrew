int __cdecl fcn_004aac00(char*, int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);

// FUNCTION: GOLD 0x0049d450
// SIZE: 65
// FUNCTION: GOLDTL 0x49ce90
// SIZE: 65

int __cdecl fcn_0049ce90(char* a, int b, int c)
{
	if (fcn_004aac00(a, b, c) != 0) {
		fcn_004c5420(*(int*) (a + 4), 0x1e8, 4, 0x200, 0);
		return 0x2a;
	}
	return 0;
}
