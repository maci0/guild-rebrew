/* Initializes the log/error handler: stores the module/severity
 * settings, installs the crash-dump filter, resolves the log file
 * directory, and installs per-level log file handles. */

// FUNCTION: SERVER 0x10003320
// InitializeLogAndErrorHandler
// SIZE: 404

#include <windows.h>

extern int g_panic_callback;
extern void* g_crash_callback;
extern unsigned int g_log_mode_flags; /* 0x10034618 */
extern char g_crash_dump_all_frames;
extern int g_owner_window;
extern int g_log_file_handle;
extern int __cdecl sprintf(char* buf, const char* fmt, ...);
extern long __cdecl time(long* t);
extern char* __cdecl ctime(const long* t);
extern void* __cdecl fopen(const char* path, const char* mode);
extern int __cdecl fseek(void* f, long off, int whence);
extern long __cdecl ftell(void* f);
extern int __cdecl fclose(void* f);
extern int __cdecl fputs(const char* s, void* f);
extern char* __cdecl strrchr(const char* s, int c);

void __cdecl InitializeLogAndErrorHandler(int a, int b, unsigned int c, unsigned int d)
{
	int h;
	char buf[0x104]; /* target frame: h@0, buf@4..0x108, path@0x108 */
	char path[0x100];
	char* f;
	char* sp;

	g_panic_callback = a;
	g_log_mode_flags = d;
	g_crash_callback = b;
	g_owner_window = c;
	g_crash_dump_all_frames = (d >> 4) & 1;
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) 0x10002770);
	h = time(0);
	GetWindowTextA((HWND) c, path, 0x100);
	((void (__stdcall*)(int, const char*, int)) *(void**) 0x1002403c)(0, (const char*) 0x11766100, 0x104);
	*strrchr((char*) 0x11766100, 0x5c) = 0;
	sprintf((char*) 0x117640e0, (char*) 0x1002735c, path, ctime((long*) &h));
	if (g_log_mode_flags & 1) {
		sp = (char*) 0x10027084;
		do {
			sprintf(buf, (char*) 0x100270fc, (char*) 0x11766100, sp);
			f = fopen(buf, "at");
			if (f != 0) {
				fseek(f, 0, 2);
				if (ftell(f) > 0x10000) {
					fclose(f);
					f = fopen(buf, "wt");
					fputs((char*) 0x1002733c, f);
				}
				fclose(f);
			}
			sp += 0x20;
		} while ((int) sp < 0x100270e4);
	}
	if (g_log_mode_flags & 8) {
		((void (__stdcall*)(void)) *(void**) 0x10024048)();
		g_log_file_handle = ((int (__stdcall*)(int)) *(void**) 0x10024044)(-0xb);
	}
	sp = (char*) 0x10027078;
	do {
		DispatchLogOutput((char*) 0x117640e0, g_log_mode_flags, *(int*) sp);
		sp += 4;
	} while ((int) sp < 0x10027084);
}
