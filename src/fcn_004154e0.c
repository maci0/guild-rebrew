// FUNCTION: GOLDTL 0x4154e0
// SIZE: 43

void __cdecl fcn_0041ddd0(void*);

void __cdecl fcn_004154e0(char* p)
{
	if (p == 0) {
		return;
	}
	if (*(int*) (p + 0x10) != 0) {
		fcn_0041ddd0(*(int*) (p + 0x10));
		*(int*) (p + 0x10) = 0;
	}
	fcn_0041ddd0(p);
}
