// FUNCTION: GOLD 0x004176f0
// SIZE: 29
// fcn_004176f0 — if([0x631130]) fcn_00422620([0x631130]); [0x631130]=0.

int __cdecl fcn_00422620(int);

void __cdecl fcn_004176f0(void)
{
	int h;
	h = *(int*) 0x631130;
	if (h != 0) {
		fcn_00422620(h);
	}
	*(int*) 0x631130 = 0;
}
