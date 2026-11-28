

void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLDDE 0x00403320 */
void __cdecl ch_FreeAuxData(char* p)
{
	if (*(void**) (p + 0x124) != 0) {
		m_FreeTracked(*(void**) (p + 0x124));
		*(void**) (p + 0x124) = 0;
	}
}
