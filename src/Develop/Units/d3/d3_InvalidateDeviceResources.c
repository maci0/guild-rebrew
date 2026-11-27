

typedef void (__stdcall* D3_FONT_LOST_FN)(void*);
typedef int (__stdcall* D3_COM_RELEASE_FN)(void*);

void __cdecl d3_InvalidateDeviceResources(void)
{
	void* p;

	p = *(void**) 0x6b5de4;
	if (p != 0) {
		((D3_FONT_LOST_FN) ((int*) *(int*) p)[9])(p);
	}
	p = *(void**) 0x6b5df4;
	if (p != 0) {
		*(int*) 0x14ce728 = ((D3_COM_RELEASE_FN) ((int*) *(int*) p)[2])(p);
		*(int*) 0x6b5df4 = 0;
	}
}
