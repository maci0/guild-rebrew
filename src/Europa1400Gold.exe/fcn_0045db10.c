// FUNCTION: GOLD 0x0045db10
// SIZE: 29
// fcn_0045db10 — if([0x633dd4]) fcn_0045da90([0x633dd4]); [0x633dd4]=0.

int __cdecl fcn_0045da90(int);

void __cdecl fcn_0045db10(void)
{
	int h;
	h = *(int*) 0x633dd4;
	if (h != 0) {
		fcn_0045da90(h);
	}
	*(int*) 0x633dd4 = 0;
}
