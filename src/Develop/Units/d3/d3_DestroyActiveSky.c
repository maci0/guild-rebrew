int __cdecl d3_DestroySky(int);

void __cdecl d3_DestroyActiveSky(void)
{
	int h;

	h = *(int*) 0x633dd4;
	if (h != 0) {
		d3_DestroySky(h);
		*(int*) 0x633dd4 = 0;
	}
}
