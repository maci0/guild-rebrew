// FUNCTION: GOLDTL 0x4d0050
// SIZE: 30

void __cdecl fcn_00471e30(int);

void __cdecl fcn_004d0050(void)
{
	if (*(int*) 0x68b7a0 != -1) {
		fcn_00471e30(*(int*) 0x68b7a0);
		*(int*) 0x68b7a0 = -1;
	}
}
