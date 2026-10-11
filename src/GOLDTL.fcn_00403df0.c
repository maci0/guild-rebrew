// FUNCTION: GOLDTL 0x403df0

void __cdecl m_FreeTracked(void*);

void __cdecl fcn_00403df0(char* p)
{
	if (*(void**) (p + 0x124) != 0) {
		m_FreeTracked(*(void**) (p + 0x124));
		*(void**) (p + 0x124) = 0;
	}
}
