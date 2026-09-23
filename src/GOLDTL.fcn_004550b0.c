// FUNCTION: GOLDTL 0x4550b0
// SIZE: 48

void __cdecl fcn_004379a0(int, int, int, int, int);

void __cdecl fcn_004550b0(int a1, int* a2)
{
	if (a2 == 0) {
		return;
	}
	if (a1 == 0) {
		return;
	}
	fcn_004379a0(*(int*) 0x67a370, a1, a2[0x44 / 4] | 0x280, 0x455000, (int) a2);
}
