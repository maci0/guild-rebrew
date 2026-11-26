

void __cdecl ls_FreeListNodes(void*);

void __cdecl ls_FreeList774a78(void)
{
	if (*(int*) 0x774a78 != 0) {
		ls_FreeListNodes((void*) *(int*) 0x774a78);
	}
	*(int*) 0x774a78 = 0;
}
