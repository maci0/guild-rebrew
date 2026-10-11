// FUNCTION: GOLDTL 0x408220

void* __cdecl m_AllocTracked(int, void*);

void __cdecl fcn_00408220(int a1)
{
	void* p;

	p = m_AllocTracked(0x14, (void*) 0x675ac0);
	*(int*) ((char*) p + 0x10) = a1;
}
