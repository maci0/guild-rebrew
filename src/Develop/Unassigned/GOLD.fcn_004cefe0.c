
// fcn_004cefe0 — if([0x60cb40]!=-1) { fcn_004758e0(h); [0x60cb40]=-1; }.

int __cdecl d2_FreeWindowSlot(int);

void __cdecl d2_DestroyHudForm(void)
{
	int h;
	h = *(int*) 0x60cb40;
	if (h != -1) {
		d2_FreeWindowSlot(h);
		*(int*) 0x60cb40 = 0xffffffff;
	}
}
