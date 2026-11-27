/* fcn_004bfc70 — release the entry's handle and clear the pair. */

void __cdecl d2_DestroyElement(int);

/* ADDRESS: GOLDTL 0x004bfc70 */
void __cdecl d2_ClearRoutePointSlot(int index)
{
	d2_DestroyElement(*(int*) (0x10058a0 + index * 8));
	*(int*) (0x10058a0 + index * 8) = -1;
	*(int*) (0x10058a4 + index * 8) = 0;
}
