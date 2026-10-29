
/* ADDRESS: GOLDTL 0x004eb220 */
int __cdecl fcn_004eb220(char* a1)
{
	unsigned char c;
	int r;

	c = *(unsigned char*) (a1 + 0x169);
	if (c < 0x1e || c > 0x21) {
		return 0;
	}
	if ((*(int*) (a1 + 0x1c8) & 0x4000000) != 0) {
		return -1;
	}
	r = *(int*) (a1 + 0x194);
	if (r < 3) {
		return -2;
	}
	return 1;
}
