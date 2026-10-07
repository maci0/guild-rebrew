// FUNCTION: GOLD 0x004bdac0
// fcn_004bdac0 — if([0x602a70]!=-1) fcn_0046c5f0(h); [0x602a70]=-1.

int __cdecl fcn_0046c5f0(int);

void __cdecl fcn_004bdac0(void)
{
	int h;
	h = *(int*) 0x602a70;
	if (h != -1) {
		fcn_0046c5f0(h);
	}
	*(int*) 0x602a70 = 0xffffffff;
}
