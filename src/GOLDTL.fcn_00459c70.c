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

/* ADDRESS: GOLDTL 0x00459c70 */
int __cdecl fcn_00459c70(char* a)
{
	int r;

	r = 0;
	if (a != 0 && !((Bits8*) (a + 0x2a1))->b0) {
		r = *(int*) (a + 0x1e8) * *(int*) (a + 0x1e4) + 0x2a4;
		if (*(int*) (a + 0x44) > 0) {
			r += (*(int*) (a + 0x44) * 3 + 0x18) * 8;
		}
		r += *(int*) (a + 0x4c) * 0x38;
		((Bits8*) (a + 0x2a1))->b0 = 1;
	}
	return r;
}
