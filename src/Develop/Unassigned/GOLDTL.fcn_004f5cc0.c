/* ADDRESS: GOLDTL 0x004f5cc0 */
int __cdecl fcn_004f5cc0(unsigned char a0, int a1)
{
	int r;

	r = 0;
	switch (a1) {
	case 1:
		if ((a0 & 0xf0) < 0x30)
			r = 1;
		break;
	case 2: case 3:
		break;
	case 4: case 5:
		break;
	case 6: case 7:
		break;
	default:
		return 0;
	}
	return r;
}
