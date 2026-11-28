extern char d2_RadioSlots[];
/* fcn_004bfc70 — release the entry's handle and clear the pair. */

void __cdecl d2_DestroyElement(int);

/* ADDRESS: GOLDTL 0x004bfc70 */
/* ADDRESS: GOLDDE 0x004ad7f0 */
void __cdecl d2_ClearRoutePointSlot(int index)
{
	d2_DestroyElement(*(int*) ((int) &d2_RadioSlots + index * 8));
	*(int*) ((int) &d2_RadioSlots + index * 8) = -1;
	*(int*) (((int) &d2_RadioSlots + 0x4) + index * 8) = 0;
}
