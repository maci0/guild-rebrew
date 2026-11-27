

void __cdecl d3_RemoveSkyLayer(void*, void*);
void __cdecl d3_ReleaseSkyDomeBuffers(void*);
void __cdecl m_FreeTracked(void*);

void __cdecl d3_FreeSkyDome(char* p)
{
	if (p == 0) {
		return;
	}
	while (*(void**) (p + 0x24) != 0) {
		d3_RemoveSkyLayer(p, *(void**) (p + 0x24));
	}
	d3_ReleaseSkyDomeBuffers(p);
	m_FreeTracked(p);
}
