
/* ADDRESS: GOLDTL 0x004f5bb0 */
void __cdecl fcn_004f5bb0(int mask)
{
	int cursor;

	for (cursor = 0x7f4e88; cursor < 0x85a288; cursor += 0x21c) {
		if (*(char*) (cursor - 0x1e6) == 6 || *(char*) (cursor - 0x1e6) == 7) {
			*(int*) cursor &= ~mask;
		}
	}
}
