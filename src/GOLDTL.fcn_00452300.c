typedef int(__stdcall* Fn1)(void* self);

extern char* g_1040c74;
extern char g_1040640[];
extern void* g_104095c;
extern unsigned long g_14ce728;

void __cdecl fcn_00452420(char* p);

/* ADDRESS: GOLDTL 0x00452300 */
void __cdecl fcn_00452300(void)
{
	while (g_1040c74 != g_1040640) {
		fcn_00452420(g_1040c74);
	}
	(*(int*)&g_14ce728) = ((Fn1) ((void**) *(*(void***)&g_104095c))[2])((*(void***)&g_104095c));
	(*(void***)&g_104095c) = 0;
}
