// FUNCTION: GOLDTL 0x477070
// fcn_00479cc0 (client variant) — if(e){ e[0x2c]=a; e[0x30]=b; e[0x34]=a+c;
// e[0x38]=b+d; }.  The GOLD build stores the same four values at
// +0x24/+0x28/+0x2c/+0x30, so the two are twins, not one body.

void __cdecl fcn_00479cc0(int a, int b, int c, int d, char* e)
{
	if (e != 0) {
		*(int*) (e + 0x2c) = a;
		*(int*) (e + 0x30) = b;
		*(int*) (e + 0x34) = a + c;
		*(int*) (e + 0x38) = b + d;
	}
}
