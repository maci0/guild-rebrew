// FUNCTION: GOLDTL 0x402ab0

void __cdecl fcn_00438b40(int, int);
void __cdecl fcn_004053a0(void*, int);
void __cdecl fcn_00403e20(void*, int);
void __cdecl fcn_004033e0(void*);

void __cdecl fcn_00402ab0(void* a1, int a2)
{
	fcn_00438b40(*(int*) ((char*) a1 + 0x34), a2);
	fcn_004053a0(a1, 0);
	if (*(int*) ((char*) a1 + 0x124) != 0) {
		fcn_00403e20(a1, 0);
	}
	if (*(int*) ((char*) a1 + 0x22c) != 0) {
		fcn_004033e0(a1);
	}
}
