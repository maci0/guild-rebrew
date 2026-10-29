void __cdecl d2_SetForm(int, int);
void __cdecl fcn_00519190(int);
void __cdecl fcn_0046ac30(void);

/* ADDRESS: GOLDTL 0x00514570 */
void __cdecl fcn_00514570(unsigned int a0)
{
	d2_SetForm(*(int*) 0x7e1d40, 2);
	fcn_00519190(0x6811b0);
	fcn_00519190(a0);
	fcn_0046ac30();
}
