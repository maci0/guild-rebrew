void __cdecl fcn_00438d40(int, int, int, int, int);
void __cdecl fcn_00455750(int);

/* ADDRESS: GOLD 0x00447f70 */
unsigned char __cdecl fcn_00447f70(int obj, int *pair)
{
	int p;
	int n;

	fcn_00438d40(*pair, 0, 7, 0x452e30, obj);
	*(int *)(obj + 0x208) = pair[1];
	p = *(int *)(*pair + 0xa4);
	while (p != 0xfb9280) {
		n = *(int *)(p + 0x314);
		if (*(int *)(p + 0x2e0) == obj)
			fcn_00455750(p);
		p = n;
	}
	return 1;
}
