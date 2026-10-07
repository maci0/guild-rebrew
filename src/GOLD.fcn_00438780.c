// FUNCTION: GOLD 0x00438780
// fcn_00438780 — r=vfn([0x633418]); [0x14661a4]=r; if(!r) fcn_00418e90(0x5f944c, 0x4f0, 0x5faf08).

int __cdecl fcn_00418e90(int, int, int);

void __cdecl fcn_00438780(void)
{
	int r;
	void* p;
	p = *(void**) 0x633418;
	r = (int) ((int (__stdcall*)(void*)) *(void**) (*(void***) p)[0x28])(p);
	*(int*) 0x14661a4 = r;
	if (r == 0) {
		fcn_00418e90(0x5f944c, 0x4f0, 0x5faf08);
	}
}
