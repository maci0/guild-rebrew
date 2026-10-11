// FUNCTION: GOLDTL 0x5b1960

void __cdecl m_FreeTracked(void*);
void __cdecl fcn_005b1960(void* p);

void __cdecl fcn_005b1960(void* p)
{
	void* q;

	q = *(void**) ((char*) p + 0x48);
	if (q != 0) {
		fcn_005b1960(q);
	}
	m_FreeTracked(p);
}
