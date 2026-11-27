

typedef int (__stdcall* D3_TEX_RELEASE_FN)(void*);

void __cdecl d3_ReleaseTextureInterface(char* p)
{
	void* q;

	if (p[0] == 0x2a) {
		q = *(void**) (p + 0x50);
		if (q != 0) {
			*(int*) 0x14ce728 = ((D3_TEX_RELEASE_FN) ((int*) *(int*) q)[2])(q);
			*(int*) (p + 0x50) = 0;
		}
		return;
	}
	q = *(void**) (p + 0x50);
	if (q != 0) {
		*(int*) 0x14ce728 = ((D3_TEX_RELEASE_FN) ((int*) *(int*) q)[2])(q);
		*(int*) (p + 0x50) = 0;
	}
}
