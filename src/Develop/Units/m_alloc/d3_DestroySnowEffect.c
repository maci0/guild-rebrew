

void __cdecl d3_ReleaseTexture(int);
void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLDDE 0x004146c0 */
void __cdecl d3_DestroySnowEffect(char* p)
{
	if (p == 0) {
		return;
	}
	d3_ReleaseTexture(*(int*) (p + 0x90));
	if (*(int*) (p + 0x38) != 0) {
		m_FreeTracked(*(void**) (p + 0x38));
		*(int*) (p + 0x38) = 0;
	}
	m_FreeTracked(p);
}
