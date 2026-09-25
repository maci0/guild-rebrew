// FUNCTION: GOLDTL 0x412eb0
// SIZE: 90

void __cdecl fcn_004379a0(int, int, int, void*, int);
void __cdecl fcn_00412e80(void);

int __cdecl fcn_00412eb0(int a1, int a2)
{
	*(int*) 0x6b5cc4 = 0;
	if (a2 & 2) {
		fcn_004379a0(*(int*) 0x67a370, 0, 0x1e0, fcn_00412e80, a1);
		return *(int*) 0x6b5cc4;
	}
	fcn_004379a0(*(int*) 0x67a370, 0, 0x60, fcn_00412e80, a1);
	return *(int*) 0x6b5cc4;
}
