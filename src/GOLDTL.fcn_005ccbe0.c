/* ADDRESS: GOLDTL 0x005ccbe0 */

void __cdecl fcn_005ccbe0(void)
{
	int a;

	for (a = 0x6ac8b0; a < 0x6ac950; a += 0x14) {
		*(int*) (a - 4) = 0;
		*(int*) a = 0;
	}
}
