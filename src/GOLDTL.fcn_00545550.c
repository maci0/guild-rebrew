// FUNCTION: GOLD 0x53d830
// SIZE: 48
// FUNCTION: GOLDTL 0x545550
// SIZE: 48

void __cdecl fcn_00545510(void);
int __cdecl fcn_0055bc30(void);
int __cdecl fcn_005710f0(void);
int __cdecl fcn_005758e0(void);

int __cdecl fcn_00545550(void)
{
	fcn_00545510();
	if (fcn_0055bc30() != 0) {
		return 1;
	}
	if (fcn_005710f0() != 0) {
		return 1;
	}
	return fcn_005758e0() != 0;
}
