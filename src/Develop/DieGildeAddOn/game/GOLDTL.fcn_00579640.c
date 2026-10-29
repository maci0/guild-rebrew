


char* __cdecl fcn_005463a0(int, ...);
char* __cdecl he_fn_Handlung(void);

int __cdecl fcn_00579640(char* a, char* b)
{
	char* u;

	for (u = fcn_005463a0(1, 0, 0x88); u != 0; u = he_fn_Handlung()) {
		if (*(int*) (b + 4) == *(unsigned short*) (u + 8) && *(int*) (u + 0xb0) == *(int*) (a + 4)) {
			return 0;
		}
	}
	return 1;
}
