
// fcn_0045ab80 — free(0x633dd0); zero 3 globals.

int __cdecl m_FreeTracked(int);

void __cdecl d3s_FreeCache(void)
{
	int v;
	v = *(int*) 0x633dd0;
	*(int*) 0x633dbc = 0;
	*(int*) 0x633db8 = 0;
	m_FreeTracked(v);
	*(int*) 0x633dd0 = 0;
}
