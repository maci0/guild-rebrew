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

typedef struct Key4 {
	unsigned char id;
	unsigned char b;
	Bits8 f;
	unsigned char d;
} Key4;
// SIZE 0x4

void __cdecl fcn_0045d1e0(unsigned char* a, Key4 k, char c);

// FUNCTION: GOLDTL 0x45d3b0
void __cdecl fcn_0045d3b0(unsigned char* a, Key4 k, char c)
{
	if (a[0x58] >= 0xff && !((Bits8*) (a + 0x5a))->b0 && (k.id != 0xff || k.f.b0)) {
		fcn_0045d1e0(a, k, c);
	}
}
