// FUNCTION: GOLD 0x004c3f20
// SIZE: 37
// fcn_004c3f20 — if([0x60bd64] < 4) fcn_004c4db0(0x12, &x).

int __cdecl fcn_004c4db0(int, int*);

void __cdecl fcn_004c3f20(void)
{
	int x;
	if (*(int*) 0x60bd64 >= 4) {
		return;
	}
	x = *(int*) 0x60bd64 + 1;
	fcn_004c4db0(0x12, &x);
}
