

void __cdecl m_FreeTracked(void*);

void __cdecl gm_FreeBuffer773d44(void)
{
	if (*(int*) 0x773d44 != 0) {
		m_FreeTracked((void*) *(int*) 0x773d44);
		*(int*) 0x773d44 = 0;
	}
}
