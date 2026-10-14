typedef int(__stdcall* Fn1)(void* self);

extern unsigned long g_14ce728;

void __cdecl fcn_0045ce90(char* a);

/* ADDRESS: GOLDTL 0x0045d040 */
char __cdecl fcn_0045d040(char* a)
{
	void** t;

	if (a != 0 && (a[0x54] & 2) == 0) {
		t = *(void***) (a + 0x50);
		if (t != 0) {
			(*(int*)&g_14ce728) = ((Fn1) ((void**) *t)[2])(t);
			*(void**) (a + 0x50) = 0;
		}
		if (*(int*) (a + 0x44) != 0 && *a != '*') {
			fcn_0045ce90(a);
		}
	}
	return 0;
}
