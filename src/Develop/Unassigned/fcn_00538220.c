void __cdecl fcn_005381a0(void);
void __cdecl fcn_00538160(void);
void __cdecl fcn_00538790(void);
void __cdecl fcn_00538140(void);
void __cdecl fcn_005386c0(int v);

/* ADDRESS: GOLDTL 0x00538220 */
void __cdecl fcn_00538220(void)
{
	fcn_005381a0();
	fcn_00538160();
	fcn_00538790();
	fcn_00538140();
	if (*(int*) 0x7e246c != 0)
		return;
	if (*(int*) 0x774974 == 0)
		return;
	fcn_005386c0(1);
}
