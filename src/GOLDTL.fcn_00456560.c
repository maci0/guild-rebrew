// FUNCTION: GOLDTL 0x456560

void __cdecl m_FreeTracked(void*);

void __cdecl fcn_00456560(void)
{
	void* p;

	p = *(void**) 0x6b89b4;
	*(int*) 0x6b89ac = 0;
	*(int*) 0x6b89a8 = 0;
	m_FreeTracked(p);
	*(int*) 0x6b89b4 = 0;
}
