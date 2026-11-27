

void __cdecl ch_SetVisible(int, int);

void __cdecl ch_HideAttachedCharacter(char* entity)
{
	ch_SetVisible(*(int*) (*(int*) (entity + 0x17c) + 0x184), 0);
}
