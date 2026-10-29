


char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);

int __cdecl fcn_0057b9d0(char* p, int a, int b)
{
	char* r;

	for (r = fcn_005463a0(2, 3, *(int*) (p + 1), 0, 0x8d); r != 0; r = he_fn_Handlung()) {
		if (*(int*) (r + 0xb0) == a && *(unsigned char*) (r + 0xb4) == b) {
			return 1;
		}
	}
	return 0;
}
