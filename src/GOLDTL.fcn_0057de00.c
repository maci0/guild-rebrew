// FUNCTION: GOLD 0x005758c0
// SIZE: 57
// FUNCTION: GOLDTL 0x0057de00
// SIZE: 57

extern int g_7749f4;
extern char g_77df20[];

int __cdecl sprintf(char*, const char*, ...);
__declspec(dllimport) int __stdcall WritePrivateProfileStringA(const char*, const char*, const char*, const char*);

void __cdecl fcn_0057de00(void)
{
	char buf[12];

	sprintf(buf, "%d", g_7749f4);
	WritePrivateProfileStringA("Game", "message_filter_mask", buf, g_77df20);
}
