

void __cdecl fcn_005b1960(void*);

void __cdecl ls_FreeList774a78(void)
{
	if (*(int*) 0x774a78 != 0) {
		fcn_005b1960((void*) *(int*) 0x774a78);
	}
	*(int*) 0x774a78 = 0;
}
