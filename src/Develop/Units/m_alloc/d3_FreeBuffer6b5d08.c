void __cdecl m_FreeTracked(void*);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x004176f0 */
void __cdecl d3_FreeBuffer6b5d08(void)
{
	int h;
	h = *(int*) 0x631130;
	if (h != 0) {
		m_FreeTracked((void*) h);
	}
	*(int*) 0x631130 = 0;
}
#else
/* ADDRESS: GOLDTL 0x00418c60 */
void __cdecl d3_FreeBuffer6b5d08(void)
{
	if (*(int*) 0x6b5d08 != 0) {
		m_FreeTracked((void*) *(int*) 0x6b5d08);
	}
	*(int*) 0x6b5d08 = 0;
}
#endif
