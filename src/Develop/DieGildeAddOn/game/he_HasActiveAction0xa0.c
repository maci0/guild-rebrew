

void __cdecl he_StartHandlungSearch(int, int, int, int, int);

/* ADDRESS: GOLDDE 0x00562800 */
void __cdecl he_HasActiveAction0xa0(char* entity)
{
	he_StartHandlungSearch(2, 0, 0xa0, 3, *(int*) (entity + 1));
}
