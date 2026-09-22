// FUNCTION: GOLD 0x0051ad90
// SIZE: 32
// fcn_0051ad90 — a==-1 ? 0 : [0x631050] + a*0x194.

int __cdecl fcn_0051ad90(int a)
{
	if (a == -1) {
		return 0;
	}
	return *(int*) 0x631050 + a * 0x194;
}
