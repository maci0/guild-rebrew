
/* ADDRESS: GOLDTL 0x004f1840 */
int __cdecl gv_IsGraveSlotFree(int unused, char* slot)
{
	return *(int*) (slot + 4) == -1;
}
