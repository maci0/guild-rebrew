
/* ADDRESS: GOLDTL 0x004f1840 */
/* ADDRESS: GOLDDE 0x004dd930 */
int __cdecl gv_IsGraveSlotFree(int unused, char* slot)
{
	return *(int*) (slot + 4) == -1;
}
