
// fcn_0045ab50 — [0x633db8]=a; [0x633dbc]=b; [0x633dd0]=fcn_004223c0(a*20, 0x5fcde0).

void* __cdecl m_alloc(int, int);

void __cdecl fcn_0045ab50(int a, int b)
{
	*(int*) 0x633db8 = a;
	*(int*) 0x633dbc = b;
	*(void**) 0x633dd0 = m_alloc(a * 20, 0x5fcde0);
}
