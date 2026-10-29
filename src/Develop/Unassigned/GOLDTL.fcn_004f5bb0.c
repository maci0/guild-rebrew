
/* ADDRESS: GOLDTL 0x004f5bb0 */
void __cdecl fcn_004f5bb0(int a1)
{
	int a;

	for (a = 0x7f4e88; a < 0x85a288; a += 0x21c) {
		if (*(char*) (a - 0x1e6) == 6 || *(char*) (a - 0x1e6) == 7) {
			*(int*) a &= ~a1;
		}
	}
}
