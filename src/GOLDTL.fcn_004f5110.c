// FUNCTION: GOLDTL 0x4f5110
// SIZE: 188
// FUNCTION: GOLD 0x4f2fe0
// SIZE: 188

int __cdecl fcn_004f4830(int, void*);
void __cdecl fcn_0051af00(void*, int, ...);

int __cdecl fcn_004f5110(void* a1, int a2)
{
	unsigned char local[0x24];
	unsigned char a;
	unsigned char b;
	int v;
	int r = 1;

	if (!fcn_004f4830(a2, local)) {
		return 0;
	}
	a = local[0];
	b = local[1];
	v = a * 5 + 0x13fd;
	switch (b) {
	case 0:
		fcn_0051af00(a1, v + 1, v, *(int*) (local + 0x18));
		break;
	case 1:
		fcn_0051af00(a1, v + 1, v, *(int*) (local + 0x18) + 0x13dd);
		break;
	case 2:
		fcn_0051af00(a1, v + 1, v, *(int*) (local + 0x18) + 0x13e6);
		break;
	case 3:
		fcn_0051af00(a1, v + 1, v, *(int*) (local + 0x18) + 0x13ec);
		break;
	default:
		r = 0;
		break;
	}
	return r;
}
