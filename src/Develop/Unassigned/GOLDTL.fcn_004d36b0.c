/* fcn_004d36b0 — register the game in the pending table unless it exists. */

int __cdecl fcn_0064f170(int, int, int);

/* ADDRESS: GOLDTL 0x004d36b0 */
char __cdecl fcn_004d36b0(int game)
{
	int index;

	if (fcn_0064f170(game, 0x68b820, 0xa) == 0) {
		index = *(int*) 0x772f10;
		*(int*) (0x9b46c0 + index * 4) = game;
		*(int*) 0x772f10 = index + 1;
	}
	return 1;
}
