int __cdecl fcn_004aaa60(char*, int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);

// FUNCTION: GOLD 0x0049d270
// FUNCTION: GOLDTL 0x49ccb0

int __cdecl fcn_0049ccb0(char* a, int b, int c)
{
	if (fcn_004aaa60(a, b, c) != 0) {
		fcn_004c5420(*(int*) (a + 4), 0x1e8, 4, 0x100, 0);
		return 0x29;
	}
	return 0;
}
