extern char* g_99ec10;
// FUNCTION: GOLD 0x00500080
// FUNCTION: GOLDTL 0x00502ec0

void __cdecl fcn_004be280(int);

void __cdecl fcn_00502ec0(unsigned short* a1)
{
	if ((g_99ec10 + *a1 * 64)[*a1] == 0x1d && *(int*) ((char*) a1 + 0x29) != 0) {
		fcn_004be280(*(int*) ((char*) a1 + 0x29));
		*(int*) ((char*) a1 + 0x29) = 0;
	}
}
