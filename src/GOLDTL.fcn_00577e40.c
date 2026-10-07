// FUNCTION: GOLDTL 0x00577e40

char* __cdecl fcn_005462a0(void);

char* __cdecl fcn_00577e40(char* b)
{
	char* r;

	for (r = fcn_005462a0(); r != 0 && *r == 0x18; r = fcn_005462a0()) {
		if (*(int*) (r + 0xc4) == *(int*) (b + 4)) {
			return r;
		}
	}
	return 0;
}
