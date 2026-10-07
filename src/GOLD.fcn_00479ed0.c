// FUNCTION: GOLD 0x00479ed0
// fcn_00479ed0 — if(![0xf8a630] && [0x6f0460]){ fcn_00422620(h); [0x6f0460]=0; }.

int __cdecl fcn_00422620(int);

void __cdecl fcn_00479ed0(void)
{
	int h;
	if (*(int*) 0xf8a630 != 0) {
		return;
	}
	h = *(int*) 0x6f0460;
	if (h != 0) {
		fcn_00422620(h);
		*(int*) 0x6f0460 = 0;
	}
}
