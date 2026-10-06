// FUNCTION: GOLDTL 0x4162c0

void __cdecl fcn_0045bfb0(int);
void __cdecl fcn_0041ddd0(void*);

void __cdecl fcn_004162c0(char* p)
{
	if (p == 0) {
		return;
	}
	fcn_0045bfb0(*(int*) (p + 0x90));
	if (*(int*) (p + 0x38) != 0) {
		fcn_0041ddd0(*(void**) (p + 0x38));
		*(int*) (p + 0x38) = 0;
	}
	fcn_0041ddd0(p);
}
