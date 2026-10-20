#include <windows.h>
#include <string.h>

#pragma function(strlen)
extern int __cdecl GetPrimaryLen(char* s);
extern int __stdcall LangCountryEnumProc(char* s);

extern int g_776258;
extern int g_77625c;
extern int g_776260;
extern int g_776264;
extern char* g_776268;
extern char* g_77626c;
extern int g_776270;

/* ADDRESS: GOLDTL 0x0065ba0f */
void __cdecl fcn_0065ba0f(void)
{
	g_776264 = strlen(g_776268) == 3;
	g_77625c = strlen(g_77626c) == 3;
	g_776258 = 0;
	g_776260 = g_776264 ? 2 : GetPrimaryLen(g_776268);
	EnumSystemLocalesA(LangCountryEnumProc, 1);
	if (!(g_776270 & 0x100) || !(g_776270 & 0x200) || !(g_776270 & 7))
		g_776270 = 0;
}
