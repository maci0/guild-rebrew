/* ADDRESS: GOLD 0x0052ea60 */
void __cdecl fcn_0052ea60(int i)
{
	int p;
	int v;
	int q;

	p = i * 964;
	v = *(int *)(p + 0xf8f4a8);
	if (v == -1)
		return;
	q = *(int *)0x6ed918 + v * 84;
	*(unsigned short *)(p + 0xf8f128) = *(unsigned short *)(q + 0x50);
	*(unsigned short *)(p + 0xf8f12a) = *(unsigned short *)(q + 0x52);
	*(int *)(p + 0xf8f4b8) = 0x18;
	*(int *)(p + 0xf8f4bc) = 0x18;
	*(int *)(p + 0xf8f4c0) = 0x1b;
	*(int *)(p + 0xf8f4c4) = 0xb;
}
