/* ADDRESS: GOLD 0x004ef760 */
int __cdecl gv_IsGraveSlotEmpty(void* a0, void* a1)
{
	return *(int*) ((char*) a1 + 4) == -1;
}
