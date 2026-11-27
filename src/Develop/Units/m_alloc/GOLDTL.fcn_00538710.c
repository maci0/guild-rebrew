typedef void* HWND;

extern HWND g_774940;
extern char g_6a3448[];




int sprintf(char*, const char*, ...);
__declspec(dllimport) int __stdcall CreateDirectoryA(const char*, void*);
void __cdecl InitializeLogAndErrorHandler(void*, void*, int, int);
void __cdecl m_init(int);
void __cdecl tr_AllocTraceBuffer(int);
void __cdecl vfs_init(char*, int);
void __cdecl tb_StartTimer(int, int);
void __cdecl main_ShutdownEngine(void);
void __cdecl main_NoopCrashCallback(void);

int __cdecl main_InitRuntime(void)
{
	char path[0x104];

	InitializeLogAndErrorHandler((void*) main_ShutdownEngine, (void*) main_NoopCrashCallback, (int) g_774940, 0x10);
	m_init(0xbb80);
	tr_AllocTraceBuffer(0x80);
	sprintf(path, "%sgamedata\\Screenshots", g_6a3448);
	CreateDirectoryA(path, 0);
	vfs_init(g_6a3448, 0);
	tb_StartTimer(0xe, 0);
	return 1;
}
