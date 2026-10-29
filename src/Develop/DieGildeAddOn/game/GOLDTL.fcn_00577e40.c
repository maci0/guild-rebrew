

char* __cdecl he_fn_Handlung(void);

char* __cdecl fcn_00577e40(char* b)
{
	char* r;

	for (r = he_fn_Handlung(); r != 0 && *r == 0x18; r = he_fn_Handlung()) {
		if (*(int*) (r + 0xc4) == *(int*) (b + 4)) {
			return r;
		}
	}
	return 0;
}
