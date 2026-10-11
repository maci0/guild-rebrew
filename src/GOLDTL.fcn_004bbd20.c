// FUNCTION: GOLDTL 0x4bbd20

void* __cdecl m_alloc(int, void*);

void __cdecl fcn_004bbd20(void)
{
	void* p;

	p = m_alloc(0x2480, (void*) 0x6813d0);
	*(void**) 0x7728e8 = p;
	*(int*) 0x7728e4 = 0;
	*(int*) p = 0;
}
