// FUNCTION: GOLDTL 0x403df0

void __cdecl fcn_0041ddd0(void*);

void __cdecl fcn_00403df0(char* p)
{
	if (*(void**) (p + 0x124) != 0) {
		fcn_0041ddd0(*(void**) (p + 0x124));
		*(void**) (p + 0x124) = 0;
	}
}
