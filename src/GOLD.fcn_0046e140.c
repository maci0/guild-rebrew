void __cdecl fcn_00468e20(void);
int __cdecl fcn_00479010(int);
void __cdecl fcn_0046d3c0(void);
int __cdecl fcn_004790d0(void*);
void __cdecl fcn_0041e390(void);

/* ADDRESS: GOLD 0x0046e140 */
void __cdecl fcn_0046e140(void)
{
	fcn_00468e20();
	if (fcn_00479010(*(int *)0x6ed924) != 0) {
		fcn_0046d3c0();
		fcn_004790d0(*(void**)0x6ed924);
		fcn_0041e390();
	}
}
