/* fcn_004d36b0 — register the game in the pending table unless it exists. */

int __cdecl fcn_0064f170(int, int, int);

// FUNCTION: GOLDTL 0x4d36b0
// SIZE: 47
char __cdecl fcn_004d36b0(int a1)
{
	int index;

	if (fcn_0064f170(a1, 0x68b820, 0xa) == 0) {
		index = *(int*) 0x772f10;
		*(int*) (0x9b46c0 + index * 4) = a1;
		*(int*) 0x772f10 = index + 1;
	}
	return 1;
}
