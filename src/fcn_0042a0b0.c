// FUNCTION: GOLDTL 0x42a0b0
// SIZE: 48

void __cdecl fcn_0042ad00(void);
void __cdecl fcn_0042a760(void);
void __cdecl fcn_0042a350(void);
typedef void (__stdcall* fcn_0042a0b0_f)(void);

int __cdecl fcn_0042a0b0(void)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		fcn_0042ad00();
		fcn_0042a760();
		fcn_0042a350();
		(*(fcn_0042a0b0_f*) 0x66245c)();
		*(int*) 0x6b7f90 = r;
	} else {
		r = -1;
	}
	return r;
}
