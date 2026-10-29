

char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);

int __cdecl fcn_0055c1a0(unsigned short* e, char* b)
{
	char* r;

	for (r = fcn_005463a0(2, 2, *e, 0, 0x18); r != 0; r = he_fn_Handlung()) {
		if (*(int*) (b + 4) == *(int*) (r + 0xc4)) {
			return 0;
		}
	}
	return 1;
}
