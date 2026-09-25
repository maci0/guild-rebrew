typedef struct Ent7c {
	int f0;
	int f4;
	char pad8[0x5c];
	int f64;
	int f68;
	int f6c;
	unsigned char b0 : 1;
	unsigned char b1 : 1;
	char pad71[0xb];
} Ent7c;
// SIZE 0x7c

// FUNCTION: GOLDTL 0x439e10
// SIZE: 88
void __cdecl fcn_00439e10(char* a, int v)
{
	int i;
	Ent7c* e;

	*(int*) (a + 0x49c) = 0;
	a[0x49c] = (char) 0xff;
	*(int*) (a + 0x324) = 0;
	*(int*) (a + 0x310) = 0;
	*(int*) (a + 0x314) = 0;
	*(int*) (a + 0x318) = 0;
	*(int*) (a + 0x320) = v;
	e = (Ent7c*) (a + 0x32c);
	for (i = 3; i != 0; i--) {
		e->b1 = 0;
		e->f64 = 0;
		e->f0 = 0;
		e->f4 = 0;
		((int*) e)[-1] = 0;
		e->f68 = 0;
		e++;
	}
}
