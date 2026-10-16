/* ADDRESS: GOLD 0x00479b80 */
int __cdecl fcn_00479b80(int x, int y, unsigned short v, int s)
{
	if (x < 0
	    || x >= *(int *)(s + 4)
	    || y < 0
	    || y >= *(int *)(s + 8)
	    || x < *(int *)(s + 0x24)
	    || x >= *(int *)(s + 0x2c)
	    || y < *(int *)(s + 0x28)
	    || y >= *(int *)(s + 0x30))
		return 0;
	*(unsigned short *)(*(int *)(s + 0x1c) + (*(int *)(s + 0x10) * y + x) * 2) = v;
	return 1;
}
