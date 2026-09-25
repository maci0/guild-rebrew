// FUNCTION: GOLDTL 0x00411610
// SIZE: 176

extern unsigned short g_14cf300[];

char __cdecl fcn_00411610(int shift, int ctrl, int alt, char key)
{
	int k;
	int i;

	k = key;
	if (k == 'R') {
		return '0';
	}
	if (k == 'O') {
		return '1';
	}
	if (k == 'P') {
		return '2';
	}
	if (k == 'Q') {
		return '3';
	}
	if (k == 'K') {
		return '4';
	}
	if (k == 'L') {
		return '5';
	}
	if (k == 'M') {
		return '6';
	}
	if (k == 'G') {
		return '7';
	}
	if (k == 'H') {
		return '8';
	}
	if (k == 'I') {
		return '9';
	}
	if (k == 'J') {
		return '-';
	}
	if (k == 'N') {
		return '+';
	}
	if (shift != 0) {
		k |= 0x100;
	}
	if (ctrl != 0) {
		k |= 0x200;
	}
	if (alt != 0) {
		k |= 0x400;
	}
	for (i = 0; i < 0x100; i++) {
		if (g_14cf300[i] == k) {
			return (char) i;
		}
	}
	return 0;
}
