/* ADDRESS: GOLD 0x00440140 */
void __cdecl fcn_00440140(char* obj)
{
	int row;
	int col;
	char* cursor;

	obj[0x1c70] = obj[0x1c70] | 1;
	cursor = obj + 0x13f;
	for (row = 8; row != 0; row--) {
		for (col = 8; col != 0; col--) {
			*cursor = (char) 0xff;
			cursor += 0x64;
		}
	}
}
