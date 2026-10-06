// FUNCTION: GOLD 0x004f48f0
// FUNCTION: GOLDTL 0x4f6ce0

int  __cdecl fcn_0050dac0(unsigned short);
void __cdecl fcn_0051af00(void*, int, ...);

void __cdecl fcn_004f6ce0(void* a1, int a2, void* a3)
{
	int v;
	int n;

	v = fcn_0050dac0(*(unsigned short*) a1);
	n = (int) ((float) v * 0.03f);
	switch (a2) {
	case 1:
		fcn_0051af00(a3, 0x1538, n);
		break;
	case 3:
		fcn_0051af00(a3, 0x153e, 4, n);
		break;
	default:
		fcn_0051af00(a3, a2 * 3 + 0x1535);
		break;
	}
}
