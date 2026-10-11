// FUNCTION: GOLD 0x004bb810
// fcn_004bb810 — p=fcn_004223c0(0x2480, 0x602768); [0x6f0738]=p; [0x6f0734]=0; *p=0.

void* __cdecl m_alloc(int, int);

void __cdecl fcn_004bb810(void)
{
	void* p;
	p = m_alloc(0x2480, 0x602768);
	*(void**) 0x6f0738 = p;
	*(int*) 0x6f0734 = 0;
	*(int*) p = 0;
}
