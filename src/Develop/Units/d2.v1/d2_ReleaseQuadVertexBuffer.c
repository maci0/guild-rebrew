

typedef int (__stdcall* f)(void*);

int __cdecl d2_ReleaseQuadVertexBuffer(void)
{
	return (*(f) ((int*) *(int*) *(int*) 0x772614)[2])(*(void**) 0x772614) == 0;
}
