/* Initializes the log/error handler: stores the module/severity
 * settings, installs the crash-dump filter, resolves the log file
 * directory, and installs per-level log file handles. */

extern unsigned char g_file_write_mode[3];
// GLOBAL: SERVER 0x10034614
extern void* g_crash_callback;

// GLOBAL: SERVER 0x1003461c
char g_crash_dump_all_frames = 0; /* 0x117660e0 - byte access in this TU */

// FUNCTION: SERVER 0x10003320
// InitializeLogAndErrorHandler
// SIZE: 404

#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

extern void (*g_panic_callback)(void);
extern unsigned int g_log_mode_flags; /* 0x10034618 */
extern int g_owner_window;
extern int __cdecl sprintf(char* buf, const char* fmt, ...);
extern long __cdecl time(long* t);
extern char* __cdecl ctime(const long* t);
extern void* __cdecl fopen(const char* path, const char* mode);
extern int __cdecl fseek(void* file, long off, int whence);
extern long __cdecl ftell(void* file);
extern int __cdecl fclose(void* file);
extern int __cdecl fputs(const char* s, void* file);
extern char* __cdecl strrchr(const char* s, int c);

void __cdecl InitializeLogAndErrorHandler(int a, int b, unsigned int c, unsigned int d)
{
	int now;
	char buf[0x104]; /* target frame: now@0, buf@4..0x108, path@0x108 */
	char path[0x100];
	char* file;
	char* string_cursor;

	g_panic_callback = a;
	g_log_mode_flags = d;
	g_crash_callback = (void*) b;
	g_owner_window = c;
	g_crash_dump_all_frames = (d >> 4) & 1;
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) 0x10002770);
	now = time(0);
	GetWindowTextA((HWND) c, path, 0x100);
	((void (__stdcall*)(int, const char*, int)) *(void**) 0x1002403c)(0, (const char*) 0x11766100, 0x104);
	*strrchr((char*) 0x11766100, 0x5c) = 0;
	sprintf((char*) 0x117640e0, (char*) 0x1002735c, path, ctime((long*) &now));
	if (g_log_mode_flags & 1) {
		string_cursor = (char*) 0x10027084;
		do {
			sprintf(buf, (char*) 0x100270fc, (char*) 0x11766100, string_cursor);
			file = fopen(buf, "at");
			if (file != 0) {
				fseek(file, 0, 2);
				if (ftell(file) > 0x10000) {
					fclose(file);
					file = fopen(buf, (const char*) g_file_write_mode);
					fputs((char*) 0x1002733c, file);
				}
				fclose(file);
			}
			string_cursor += 0x20;
		} while ((int) string_cursor < 0x100270e4);
	}
	if (g_log_mode_flags & 8) {
		((void (__stdcall*)(void)) *(void**) 0x10024048)();
		g_log_file_handle = ((int (__stdcall*)(int)) *(void**) 0x10024044)(-0xb);
	}
	string_cursor = (char*) 0x10027078;
	do {
		DispatchLogOutput((char*) 0x117640e0, g_log_mode_flags, *(int*) string_cursor);
		string_cursor += 4;
	} while ((int) string_cursor < 0x10027084);
}
