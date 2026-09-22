// FUNCTION: GOLDTL 0x4d7d30
// SIZE: 51

void __cdecl fcn_004d7d30(char* p)
{
	if (*(int*) 0x772ea8 != 0) {
		*(int*) (p + 0x354) = 0;
		*(int*) (p + 0x358) = *(int*) 0x772eac;
		return;
	}
	*(int*) (p + 0x354) = 1;
}
