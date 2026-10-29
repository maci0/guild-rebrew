


char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);

int __cdecl fcn_00577850(int k)
{
	char* r;

	for (r = fcn_005463a0(1, 0, 0x99); r != 0; r = he_fn_Handlung()) {
		if (*(int*) (r + 0xb0) == k) {
			return 1;
		}
	}
	return 0;
}
