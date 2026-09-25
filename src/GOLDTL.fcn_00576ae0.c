// FUNCTION: GOLDTL 0x00576ae0
// SIZE: 88

int __cdecl fcn_00545580(int, void (__cdecl*)(void), void (__cdecl*)(void));
void __cdecl fcn_00576b40(void);
void __cdecl fcn_00576c90(void);
void __cdecl fcn_005776a0(void);
void __cdecl fcn_00577720(void);
void __cdecl fcn_00577730(void);
void __cdecl fcn_00577790(void);

int __cdecl fcn_00576ae0(void)
{
	if (fcn_00545580(0x99, fcn_00576b40, fcn_00576c90) || fcn_00545580(0x9a, fcn_005776a0, fcn_00577720) ||
	    fcn_00545580(0x9b, fcn_00577730, fcn_00577790)) {
		return 1;
	}
	return 0;
}
