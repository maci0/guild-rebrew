typedef int(__stdcall* Fn1)(void* self);

extern char* g_1040c74;
extern char g_1040640[];
extern void** g_104095c;
extern int g_14ce728;

void __cdecl fcn_00452420(char* p);

// FUNCTION: GOLDTL 0x452300
// SIZE: 60
void __cdecl fcn_00452300(void)
{
	while (g_1040c74 != g_1040640) {
		fcn_00452420(g_1040c74);
	}
	g_14ce728 = ((Fn1) ((void**) *g_104095c)[2])(g_104095c);
	g_104095c = 0;
}
