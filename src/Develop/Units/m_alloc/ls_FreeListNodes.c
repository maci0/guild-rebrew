

void __cdecl m_FreeTracked(void*);
void __cdecl ls_FreeListNodes(void* p);

/* ADDRESS: GOLDDE 0x00596360 */
void __cdecl ls_FreeListNodes(void* p)
{
	void* q;

	q = *(void**) ((char*) p + 0x48);
	if (q != 0) {
		ls_FreeListNodes(q);
	}
	m_FreeTracked(p);
}
