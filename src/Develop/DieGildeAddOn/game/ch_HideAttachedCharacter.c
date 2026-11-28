

void __cdecl ch_SetVisible(int, int);

/* ADDRESS: GOLDDE 0x004c1e10 */
void __cdecl ch_HideAttachedCharacter(char* entity)
{
	ch_SetVisible(*(int*) (*(int*) (entity + 0x17c) + 0x184), 0);
}
