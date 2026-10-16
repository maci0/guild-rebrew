/* ADDRESS: GOLD 0x004760a0 */
void __cdecl fcn_004760a0(int i, int val)
{
	int p;
	int kind;
	int n;

	p = *(int *)0xf8f080 + i * 748;
	kind = *(int *)(p + 0x18);
	*(unsigned short *)(p + 0x74) = (unsigned short)val;
	switch (kind) {
	case 0x40:
		n = *(int *)(p + 0x78);
		*(unsigned short *)(n * 964 + 0xf8f39c) = (unsigned short)val;
		return;
	case 0x41:
		n = *(int *)(p + 0x78);
		*(int *)(n * 352 + 0xfa6158) = val;
		return;
	}
}
