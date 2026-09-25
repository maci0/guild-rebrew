// FUNCTION: GOLD 0x005d0830
// SIZE: 156
// FUNCTION: GOLDTL 0x005dcd60
// SIZE: 156

void __cdecl fcn_004c5420(int, int, int, int, int);

int __cdecl fcn_005dcd60(char* o)
{
	int m;
	int v;

	m = *(int*) (o + 0x2c);
	if (m != 0) {
		v = 0;
		if (m & 0xf) {
			v = 7;
		}
		else if (m & 0xf0) {
			v = 0x30;
		}
		else if (m & 0xf00) {
			v = 0x300;
		}
		else if (m & 0x3000) {
			v = 0x1000;
		}
		else if (m & 0x1c000) {
			v = 0xc000;
		}
		else if (m & 0xe0000) {
			v = 0x20000;
		}
		else if (m & 0x700000) {
			v = 0x100000;
		}
		else if (m & 0x1800000) {
			v = 0x800000;
		}
		else if (m & 0x1e000000) {
			v = 0x6000000;
		}
		fcn_004c5420(*(int*) (o + 4), 0x2c, 4, 0, v);
	}
	return 1;
}
