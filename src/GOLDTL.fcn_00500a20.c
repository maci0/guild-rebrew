// FUNCTION: GOLDTL 0x500a20

void __cdecl m_FreeTracked(void*);

void __cdecl fcn_00500a20(void)
{
	if (*(int*) 0x773d44 != 0) {
		m_FreeTracked((void*) *(int*) 0x773d44);
		*(int*) 0x773d44 = 0;
	}
}
