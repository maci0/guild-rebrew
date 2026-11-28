

extern char str_empty[];
extern int main_LoopFlags;
extern int g_774a2c;
extern char g_6a3448[];
extern char g_6a9b68[];
extern int d2_ScreenSurface;
extern char* g_14b5f14;

void __cdecl d2_ShowStatusBanner(char*);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl fcn_0064d41a(char*, const char*, ...);
void __stdcall fcn_0060fa6b(char*, int, int, int, int);

void __cdecl d2_SaveScreenshot(void)
{
	char buf[0x80];

	d2_ShowStatusBanner(str_empty);
	main_RunFrameLoop(0, main_LoopFlags);
	fcn_0064d41a(buf, g_6a9b68, g_6a3448, g_774a2c++);
	fcn_0060fa6b(buf, 0, *(int*) (((char*)d2_ScreenSurface) + 0x24), 0, 0);
	d2_ShowStatusBanner(g_14b5f14);
}
