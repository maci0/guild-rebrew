
/* fcn_004bb810: p=m_alloc(0x2480, 0x602768); [0x6f0738]=p; [0x6f0734]=0; *(int*)p=0. */

void* __cdecl m_alloc(int, int);

void __cdecl fcn_004bb810(void)
{
	void* p;
	p = m_alloc(0x2480, 0x602768);
	*(void**) 0x6f0738 = p;
	*(int*) 0x6f0734 = 0;
	*(int*) p = 0;
}
