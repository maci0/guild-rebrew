/* ADDRESS: GOLD 0x00475b70 */
int __cdecl fcn_00475b70(int a, int b, int c)
{
	int n;
	int p;

	if (a != -1) {
		n = *(int *)(0xfb1024 + (b + a * 171) * 4);
		p = n * 964 + 0xf8f120;
	} else
		p = b * 964 + 0xf8f120;
	if (c > *(short *)(p + 0x1c))
		return -1;
	return *(int *)(*(int *)(p + 0x18) + c * 4);
}
