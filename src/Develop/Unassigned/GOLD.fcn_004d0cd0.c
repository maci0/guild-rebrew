// fcn_004d0cd0 — first index holding -1 in the 16-int array, else -1.

/* ADDRESS: GOLDTL 0x004d1d20 */
int __cdecl gm_FindFirstFreeDuelistSlot(int* slots)
{
	int i;
	for (i = 0; i < 0x10; i++) {
		if (slots[i] == -1) {
			return i;
		}
	}
	return -1;
}
