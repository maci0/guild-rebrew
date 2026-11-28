
/* ADDRESS: GOLDTL 0x004f1850 */
/* ADDRESS: GOLDDE 0x004dd940 */
int __cdecl gm_IsSlotEntryValid(int a1, char* a2)
{
	return *(int*) (a2 + 4) != -1;
}
