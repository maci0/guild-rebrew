/* fcn_004e7390 — drop every entry of a pointer table. */

void __cdecl ch_AssertValidCharacterSlot(int);

/* ADDRESS: GOLDTL 0x004e7390 */
void __cdecl ch_ValidateAllCharacterAllocations(void)
{
	int* entry;

	for (entry = (int*) 0x14d0020; (int) entry < (int) 0x14d0c20; entry++) {
		if (*entry != 0) {
			ch_AssertValidCharacterSlot(*entry);
		}
	}
}
