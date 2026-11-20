


char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);

int __cdecl fcn_00577850(int k)
{
	char* r;

	for (r = he_StartHandlungSearch(1, 0, 0x99); r != 0; r = he_fn_Handlung()) {
		if (*(int*) (r + 0xb0) == k) {
			return 1;
		}
	}
	return 0;
}
