// FUNCTION: GOLD 0x005a8a70
// fcn_005a8a70 — if([0x6f26c0]) fcn_005a84e0(h); reset 0.

int __cdecl fcn_005a84e0(int);

void __cdecl fcn_005a8a70(void)
{
	int h;
	h = *(int*) 0x6f26c0;
	if (h != 0) {
		fcn_005a84e0(h);
	}
	*(int*) 0x6f26c0 = 0;
}
