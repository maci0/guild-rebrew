/* ADDRESS: GOLD 0x00440140 */
void __cdecl fcn_00440140(char* a0)
{
	int row;
	int col;
	char* p;

	a0[0x1c70] = a0[0x1c70] | 1;
	p = a0 + 0x13f;
	for (row = 8; row != 0; row--) {
		for (col = 8; col != 0; col--) {
			*p = (char) 0xff;
			p += 0x64;
		}
	}
}
