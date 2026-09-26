extern unsigned char* g_90e094;
// FUNCTION: GOLDTL 0x005224b0
// SIZE: 64

void __cdecl fcn_00510820(char*, char*, int);

char __cdecl fcn_005224b0(char* e)
{
	int i;
	char* r;

	for (i = 0; i < 0x100; i++) {
		r = ((char*)g_90e094) + i * 0xa9;
		if (*r != 0 && *(int*) (e + 0x204) == *(int*) (r + 1)) {
			fcn_00510820(e, r, 2);
		}
	}
	return 1;
}
