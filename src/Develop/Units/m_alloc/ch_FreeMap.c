

void __cdecl m_FreeTracked(int);

/* ADDRESS: GOLDDE 0x004073e0 */
void __cdecl ch_FreeMap(int allocation)
{
	m_FreeTracked(allocation);
}
