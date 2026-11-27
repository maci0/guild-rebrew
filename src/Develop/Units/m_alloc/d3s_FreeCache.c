void __cdecl m_FreeTracked(void*);

#if defined(REBREW_GOLD)

/* ADDRESS: GOLD 0x0045ab80 */
void __cdecl d3s_FreeCache(void)
{
	void* p;

	p = *(void**) 0x633dd0;
	*(int*) 0x633dbc = 0;
	*(int*) 0x633db8 = 0;
	m_FreeTracked(p);
	*(int*) 0x633dd0 = 0;
}

#else

/* ADDRESS: GOLDTL 0x00456560 */
void __cdecl d3s_FreeCache(void)
{
	void* p;

	p = *(void**) 0x6b89b4;
	*(int*) 0x6b89ac = 0;
	*(int*) 0x6b89a8 = 0;
	m_FreeTracked(p);
	*(int*) 0x6b89b4 = 0;
}

#endif
