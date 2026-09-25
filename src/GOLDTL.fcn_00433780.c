// FUNCTION: GOLD 0x00433b10
// SIZE: 64
// FUNCTION: GOLDTL 0x433780
// SIZE: 64

void __cdecl fcn_0041ddd0(int);

void __cdecl fcn_00433780(void* a1)
{
	if (*(int*) ((char*) a1 + 0x1d0) != 0) {
		fcn_0041ddd0(*(int*) ((char*) *(int*) ((char*) a1 + 0x1d0) + 0x40));
		*(int*) ((char*) *(int*) ((char*) a1 + 0x1d0) + 0x40) = 0;
		fcn_0041ddd0(*(int*) ((char*) a1 + 0x1d0));
		*(int*) ((char*) a1 + 0x1d0) = 0;
	}
}
