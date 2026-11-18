

void* __cdecl m_alloc(int, void*);

void __cdecl fcn_00456530(int count, int a2)
{
	*(int*) 0x6b89a8 = count;
	*(int*) 0x6b89ac = a2;
	*(void**) 0x6b89b4 = m_alloc(count * 20, (void*) 0x67bca4);
}
