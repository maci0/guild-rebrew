// FUNCTION: GOLDTL 0x42a080
// SIZE: 48

void __cdecl fcn_005eaad0(void);
typedef void (__stdcall* fcn_0042a080_f)(void);

int __cdecl fcn_0042a080(void)
{
	int r = 0;

	if (*(int*) 0x6b7f90 == 0) {
		fcn_005eaad0();
		(*(fcn_0042a080_f*) 0x6623b4)();
		(*(fcn_0042a080_f*) 0x6623b8)();
		*(int*) 0x6b7f90 = -1;
	} else {
		r = -1;
	}
	return r;
}
