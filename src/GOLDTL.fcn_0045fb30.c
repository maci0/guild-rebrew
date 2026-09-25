// FUNCTION: GOLD 0x00463710
// SIZE: 43
// FUNCTION: GOLDTL 0x45fb30
// SIZE: 43

void __cdecl fcn_0064fb02(int, int);

void __cdecl fcn_0045fb30(int a1, unsigned a2)
{
	int i;

	for (i = 4; i != 0; i--) {
		fcn_0064fb02((int) (a2 & 0xff), a1);
		a2 >>= 8;
	}
}
