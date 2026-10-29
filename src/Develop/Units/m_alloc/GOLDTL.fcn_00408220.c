

void* __cdecl m_alloc(int, void*);

void __cdecl fcn_00408220(int a1)
{
	void* p;

	p = m_alloc(0x14, (void*) 0x675ac0);
	*(int*) ((char*) p + 0x10) = a1;
}
