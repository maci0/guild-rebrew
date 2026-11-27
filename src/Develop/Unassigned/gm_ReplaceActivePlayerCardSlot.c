

int __cdecl gm_ReplaceCardSlot(void*, int);

int __cdecl gm_ReplaceActivePlayerCardSlot(int a1)
{
	return gm_ReplaceCardSlot((void*) (*(int*) 0x1007cd4 + 4), a1);
}
