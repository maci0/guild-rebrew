typedef int(__stdcall* Fn1)(void* self);

extern unsigned long d3_LastReleaseRefCount;

void __cdecl d3_LoadTextureSurfaceTl(char* a);

/* ADDRESS: GOLDTL 0x0045d040 */
/* ADDRESS: GOLDDE 0x00451ff0 */
char __cdecl d3_ReloadTexture(char* a)
{
	void** t;

	if (a != 0 && (a[0x54] & 2) == 0) {
		t = *(void***) (a + 0x50);
		if (t != 0) {
			(*(int*)&d3_LastReleaseRefCount) = ((Fn1) ((void**) *t)[2])(t);
			*(void**) (a + 0x50) = 0;
		}
		if (*(int*) (a + 0x44) != 0 && *a != '*') {
			d3_LoadTextureSurfaceTl(a);
		}
	}
	return 0;
}
