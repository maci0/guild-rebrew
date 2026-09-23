// FUNCTION: GOLD 0x00520ef0
// SIZE: 23
// fcn_00520ef0 — [0x623794] = (float)[0x623798]; [0x623798] = 0.

void __cdecl fcn_00520ef0(void)
{
	int v;
	v = *(int*) 0x623798;
	*(float*) 0x623794 = (float) v;
	*(int*) 0x623798 = 0;
}
