// FUNCTION: GOLDTL 0x44df20

typedef struct S0044df20 {
	int pad0[5];
	int f14;
	int pad18;
	int f1c;
	int pad20;
	int f24;
	int pad28;
	int f2c;
} S0044df20;
// SIZE 0x30

void __cdecl fcn_0044df20(int a, S0044df20* p)
{
	p->f1c += p->f14;
	p->f14 = 0;
	p->f2c += p->f24;
	p->f24 = 0;
}
