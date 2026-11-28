

typedef void (__stdcall* f)(void*);

/* ADDRESS: GOLDDE 0x00469270 */
void __cdecl d2_ResetRenderToSurface(void)
{
	void* p;

	p = *(void**) 0x7725ec;
	if (p != 0) {
		(*(f) ((int*) *(int*) p)[0x20 / 4])(p);
	}
}
