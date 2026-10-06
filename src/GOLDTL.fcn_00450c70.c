typedef int(__stdcall* Fn3)(void* self, int a, int b);

extern void* g_6b5de0;
extern int g_6b86fc;
extern void* g_6b870c;

// FUNCTION: GOLDTL 0x450c70
void __cdecl fcn_00450c70(void)
{
	int i;

	for (i = 0; i < g_6b86fc; i++) {
		((Fn3) ((void**) *((void**)g_6b5de0))[0xb8 / 4])(((void**)g_6b5de0), i, 0);
		*(int*) (((char*)g_6b870c) + i * 0xc + 4) = 0;
	}
}
