// FUNCTION: GOLD 0x004c3140
// SIZE: 56
// fcn_004c3140 — if([0x6f0b80]){ f(h,0); f(h,1); f(h); reset; }.

int __cdecl fcn_00417dd0(int, int);
int __cdecl fcn_00417db0(int, int);
int __cdecl fcn_004177b0(int);

void __cdecl fcn_004c3140(void)
{
	if (*(int*) 0x6f0b80 != 0) {
		fcn_00417dd0(*(int*) 0x6f0b80, 0);
		fcn_00417db0(*(int*) 0x6f0b80, 1);
		fcn_004177b0(*(int*) 0x6f0b80);
		*(int*) 0x6f0b80 = 0;
	}
}
