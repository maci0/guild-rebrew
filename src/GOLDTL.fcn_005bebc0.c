/* ADDRESS: GOLDTL 0x005bebc0 */

void __cdecl fcn_005bebc0(void)
{
	int a;

	for (a = 0x776730; a < 0x776ab0; a += 0x38) {
		*(int*) (a - 0x10) = 0;
		*(int*) a = -1;
		*(int*) (a + 0x10) = -1;
	}
}
