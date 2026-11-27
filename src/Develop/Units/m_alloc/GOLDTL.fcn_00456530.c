

void* __cdecl m_alloc(int, void*);

void __cdecl d3s_AllocCache(int count, int maxAge)
{
	*(int*) 0x6b89a8 = count;
	*(int*) 0x6b89ac = maxAge;
	*(void**) 0x6b89b4 = m_alloc(count * 20, (void*) 0x67bca4);
}
