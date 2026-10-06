// FUNCTION: GOLD 0x00479cc0
// fcn_00479cc0 — if(e){ e[0x24]=a; e[0x28]=b; e[0x2c]=a+c; e[0x30]=b+d; }.

void __cdecl fcn_00479cc0(int a, int b, int c, int d, char* e)
{
	if (e != 0) {
		*(int*) (e + 0x24) = a;
		*(int*) (e + 0x28) = b;
		*(int*) (e + 0x2c) = a + c;
		*(int*) (e + 0x30) = b + d;
	}
}
