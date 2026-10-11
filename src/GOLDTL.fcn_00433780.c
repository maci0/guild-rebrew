// FUNCTION: GOLD 0x00433b10
// FUNCTION: GOLDTL 0x433780

void __cdecl m_FreeTracked(int);

void __cdecl fcn_00433780(void* a1)
{
	if (*(int*) ((char*) a1 + 0x1d0) != 0) {
		m_FreeTracked(*(int*) ((char*) *(int*) ((char*) a1 + 0x1d0) + 0x40));
		*(int*) ((char*) *(int*) ((char*) a1 + 0x1d0) + 0x40) = 0;
		m_FreeTracked(*(int*) ((char*) a1 + 0x1d0));
		*(int*) ((char*) a1 + 0x1d0) = 0;
	}
}
