typedef struct Bits8 {
	unsigned char b0 : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char b3 : 1;
	unsigned char b4 : 1;
	unsigned char b5 : 1;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
} Bits8;
// SIZE 0x1

extern char* g_104049c;

/* ADDRESS: GOLDTL 0x00459d00 */
int __cdecl fcn_00459d00(char* a)
{
	int r;

	r = 0;
	if (a != 0 && !((Bits8*) (a + 0x54))->b6) {
		r = 0x70;
		if (((Bits8*) (a + 0x54))->b1) {
			((Bits8*) (a + 0x54))->b6 = 1;
			a = g_104049c + *(int*) (a + 0x44) * 0x70;
		}
		if (!((Bits8*) (a + 0x54))->b6) {
			((Bits8*) (a + 0x54))->b6 = 1;
		}
	}
	return r;
}
