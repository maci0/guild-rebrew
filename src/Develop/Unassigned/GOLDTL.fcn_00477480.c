

typedef int (__stdcall* D2_COM_RELEASE_FN)(void*);

void __cdecl d2_ReleaseRenderToSurface(void)
{
	void* p;

	p = *(void**) 0x7725ec;
	if (p != 0) {
		*(int*) 0x14ce728 = ((D2_COM_RELEASE_FN) ((int*) *(int*) p)[2])(p);
		*(int*) 0x7725ec = 0;
	}
}
