// FUNCTION: GOLDTL 0x412cf0
// SIZE: 54

typedef struct
{
	int a;
	int b;
	int c;
} Vec3;
// SIZE 0xc

void __cdecl fcn_00412b10(int, int, int, int, int, int, int, int, int);

void __cdecl fcn_00412cf0(int a1, Vec3* a2, Vec3* a3, int a4, int a5)
{
	fcn_00412b10(a1, a2->a, a2->b, a2->c, a3->a, a3->b, a3->c, a4, a5);
}
