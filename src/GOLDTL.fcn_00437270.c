typedef int(__stdcall* Fn1)(void* self);
typedef int(__stdcall* Fn3)(void* self, int a, int b);
typedef int(__stdcall* Fn4)(void* self, int a, int b, int c);

extern void* g_6b5de0;
extern unsigned char g_6b7ffd;

/* ADDRESS: GOLDTL 0x00437270 */
void __cdecl fcn_00437270(void)
{
	((Fn3) ((void**) *((void**)g_6b5de0))[0xc8 / 4])(((void**)g_6b5de0), 0x1c, 0);
	(*(char*)&g_6b7ffd) = 0;
	((Fn3) ((void**) *((void**)g_6b5de0))[0xf4 / 4])(((void**)g_6b5de0), 0, 0);
	((Fn3) ((void**) *((void**)g_6b5de0))[0x154 / 4])(((void**)g_6b5de0), 0, 0);
	((Fn4) ((void**) *((void**)g_6b5de0))[0x14c / 4])(((void**)g_6b5de0), 0, 0, 0);
	((Fn1) ((void**) *((void**)g_6b5de0))[0x8c / 4])(((void**)g_6b5de0));
}
