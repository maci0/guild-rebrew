void __cdecl fcn_00476b10(int, int, unsigned char, unsigned char, unsigned char, int);

// FUNCTION: GOLDTL 0x476d00

void __cdecl fcn_00476d00(int a1, int a2, int n, unsigned char a4, unsigned char a5, unsigned char a6, int a7)
{
	int i;

	for (i = 0; i < n; i++)
		fcn_00476b10(a1, i + a2, a4, a5, a6, a7);
}
