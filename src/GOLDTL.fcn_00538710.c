typedef void* HWND;

extern HWND g_774940;
extern char g_6a3448[];

// FUNCTION: GOLD 0x531c00
// FUNCTION: GOLDTL 0x538710

int sprintf(char*, const char*, ...);
__declspec(dllimport) int __stdcall CreateDirectoryA(const char*, void*);
void __cdecl InitializeLogAndErrorHandler(void*, void*, int, int);
void __cdecl m_init(int);
void __cdecl fcn_0042dfb0(int);
void __cdecl fcn_00431070(char*, int);
void __cdecl fcn_0042dde0(int, int);
void __cdecl fcn_00538220(void);
void __cdecl fcn_00538700(void);

int __cdecl fcn_00538710(void)
{
	char path[0x104];

	InitializeLogAndErrorHandler((void*) fcn_00538220, (void*) fcn_00538700, (int) g_774940, 0x10);
	m_init(0xbb80);
	fcn_0042dfb0(0x80);
	sprintf(path, "%sgamedata\\Screenshots", g_6a3448);
	CreateDirectoryA(path, 0);
	fcn_00431070(g_6a3448, 0);
	fcn_0042dde0(0xe, 0);
	return 1;
}
