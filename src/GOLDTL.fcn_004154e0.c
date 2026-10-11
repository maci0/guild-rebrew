// FUNCTION: GOLDTL 0x4154e0

void __cdecl m_FreeTracked(void*);

void __cdecl fcn_004154e0(char* p)
{
	if (p == 0) {
		return;
	}
	if (*(int*) (p + 0x10) != 0) {
		m_FreeTracked(*(int*) (p + 0x10));
		*(int*) (p + 0x10) = 0;
	}
	m_FreeTracked(p);
}
