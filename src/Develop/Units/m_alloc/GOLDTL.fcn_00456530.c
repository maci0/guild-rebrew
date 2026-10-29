

void* __cdecl m_alloc(int, void*);

void __cdecl fcn_00456530(int a1, int a2)
{
	*(int*) 0x6b89a8 = a1;
	*(int*) 0x6b89ac = a2;
	*(void**) 0x6b89b4 = m_alloc(a1 * 20, (void*) 0x67bca4);
}
