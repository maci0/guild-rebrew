

void __cdecl m_FreeTracked(void*);

void __cdecl fcn_00418c60(void)
{
	if (*(int*) 0x6b5d08 != 0) {
		m_FreeTracked((void*) *(int*) 0x6b5d08);
	}
	*(int*) 0x6b5d08 = 0;
}
