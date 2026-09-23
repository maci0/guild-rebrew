// FUNCTION: GOLDTL 0x4e7160
// SIZE: 61

void __cdecl fcn_004e7160(int idx, int a2, int a3, int a4, int a5, unsigned char a6)
{
	int o;

	o = idx * 20;
	*(int*) (0x9b0840 + o) = a2;
	*(int*) (0x9b0844 + o) = a3;
	*(int*) (0x9b0848 + o) = a4;
	*(int*) (0x9b0850 + o) = a5;
	*(unsigned char*) (0x9b084c + o) = a6;
}
