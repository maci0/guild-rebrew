

void __cdecl m_FreeTracked(int);

void __cdecl ch_FreeMap(int allocation)
{
	m_FreeTracked(allocation);
}
