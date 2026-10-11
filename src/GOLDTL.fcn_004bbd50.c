// FUNCTION: GOLDTL 0x4bbd50

void __cdecl m_FreeTracked(void*);

void __cdecl fcn_004bbd50(void)
{
	if (*(int*) 0x7728e8 != 0) {
		m_FreeTracked((void*) *(int*) 0x7728e8);
		*(int*) 0x7728e8 = 0;
	}
}
