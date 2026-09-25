// FUNCTION: GOLDTL 0x00592400
// SIZE: 111

extern char g_6b5c60[];
extern int g_7e46ac;
extern int g_774a2c;
extern char g_6a3448[];
extern char g_6a9b68[];
extern char* g_77250c;
extern char* g_14b5f14;

void __cdecl fcn_00533a40(char*);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_0064d41a(char*, const char*, ...);
void __stdcall fcn_0060fa6b(char*, int, int, int, int);

void __cdecl fcn_00592400(void)
{
	char buf[0x80];

	fcn_00533a40(g_6b5c60);
	fcn_005373e0(0, g_7e46ac);
	fcn_0064d41a(buf, g_6a9b68, g_6a3448, g_774a2c++);
	fcn_0060fa6b(buf, 0, *(int*) (g_77250c + 0x24), 0, 0);
	fcn_00533a40(g_14b5f14);
}
