// FUNCTION: GOLD 0x004e6f10
// SIZE: 32
// fcn_004e6f10 — a < 0x28 ? [0x60ed3c + a*0x18] : 0.

int __cdecl fcn_004e6f10(int a)
{
	if (a >= 0x28) {
		return 0;
	}
	return *(int*) (0x60ed3c + a * 0x18);
}
