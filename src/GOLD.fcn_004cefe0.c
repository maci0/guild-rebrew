// FUNCTION: GOLD 0x004cefe0
// SIZE: 30
// fcn_004cefe0 — if([0x60cb40]!=-1) { fcn_004758e0(h); [0x60cb40]=-1; }.

int __cdecl fcn_004758e0(int);

void __cdecl fcn_004cefe0(void)
{
	int h;
	h = *(int*) 0x60cb40;
	if (h != -1) {
		fcn_004758e0(h);
		*(int*) 0x60cb40 = 0xffffffff;
	}
}
