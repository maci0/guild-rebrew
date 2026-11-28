


void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLDDE 0x00566a60 */
void __cdecl d2_FreeTutorialNodes(char* node)
{
	if (node != 0) {
		if (*(char**) (node + 0x70) != 0) {
			d2_FreeTutorialNodes(*(char**) (node + 0x70));
		}
		if (*(void**) (node + 0x58) != 0) {
			m_FreeTracked(*(void**) (node + 0x58));
			*(void**) (node + 0x58) = 0;
		}
		if (*(void**) (node + 0x64) != 0) {
			m_FreeTracked(*(void**) (node + 0x64));
			*(void**) (node + 0x64) = 0;
		}
		m_FreeTracked(node);
	}
}
