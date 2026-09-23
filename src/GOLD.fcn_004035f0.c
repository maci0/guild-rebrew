// FUNCTION: GOLD 0x004035f0
// SIZE: 36
// fcn_004035f0 — if(a[0x124]) { fcn_00422620(h); a[0x124]=0; }.

int __cdecl fcn_00422620(int);

void __cdecl fcn_004035f0(char* a)
{
	int h;
	h = *(int*) (a + 0x124);
	if (h != 0) {
		fcn_00422620(h);
		*(int*) (a + 0x124) = 0;
	}
}
