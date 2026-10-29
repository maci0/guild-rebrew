
// fcn_0045ab80 — free(0x633dd0); zero 3 globals.

int __cdecl fcn_00422620(int);

void __cdecl fcn_0045ab80(void)
{
	int v;
	v = *(int*) 0x633dd0;
	*(int*) 0x633dbc = 0;
	*(int*) 0x633db8 = 0;
	fcn_00422620(v);
	*(int*) 0x633dd0 = 0;
}
