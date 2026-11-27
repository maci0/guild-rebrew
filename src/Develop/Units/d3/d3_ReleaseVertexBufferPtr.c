

typedef int (__stdcall* D3_VB_RELEASE_FN)(void*);

void __cdecl d3_ReleaseVertexBufferPtr(void)
{
	void* p;

	p = *(void**) 0x104095c;
	*(int*) 0x14ce728 = ((D3_VB_RELEASE_FN) ((int*) *(int*) p)[2])(p);
	*(int*) 0x104095c = 0;
}
