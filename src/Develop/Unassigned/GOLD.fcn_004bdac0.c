
// fcn_004bdac0 — if([0x602a70]!=-1) fcn_0046c5f0(h); [0x602a70]=-1.

int __cdecl d2_ClearRadioGroup(int);

void __cdecl d2_ClearRouteMarkerGroup(void)
{
	int h;
	h = *(int*) 0x602a70;
	if (h != -1) {
		d2_ClearRadioGroup(h);
	}
	*(int*) 0x602a70 = 0xffffffff;
}
