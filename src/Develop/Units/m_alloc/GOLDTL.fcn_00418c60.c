

void __cdecl m_FreeTracked(void*);

void __cdecl d3_FreeBuffer6b5d08(void)
{
	if (*(int*) 0x6b5d08 != 0) {
		m_FreeTracked((void*) *(int*) 0x6b5d08);
	}
	*(int*) 0x6b5d08 = 0;
}
