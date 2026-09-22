// FUNCTION: GOLD 0x004c3f50
// SIZE: 36
// fcn_004c3f50 — if([0x60bd64]) fcn_004c4db0(0x12, &x) where x=[0x60bd64]-1.

int __cdecl fcn_004c4db0(int, int*);

void __cdecl fcn_004c3f50(void)
{
	int x;
	if (*(int*) 0x60bd64 == 0) {
		return;
	}
	x = *(int*) 0x60bd64 - 1;
	fcn_004c4db0(0x12, &x);
}
