/* Initializes the log/error handler: stores the module/severity
 * settings, installs the crash-dump filter, resolves the log file
 * directory, and installs per-level log file handles.
 * TL import carried server VAs throughout; re-derived from TL disasm
 * (round 1140): filter 0x41cbc0, IAT slots 0x6622d4/0x6620c0/0x662088/
 * 0x66205c, tables 0x677948->0x677ac8 and 0x677918->0x677948, fmts
 * 0x677cc8/0x677adc/0x677ca8/0x677ad8. NEAR 397/404: the >0x10000 reopen
 * branch differs structurally (TL: fclose+sprintf+f(0x677ca8,count)+fclose;
 * server twin: fclose+fopen+fputs) — rare path, parked. */

// FUNCTION: GOLDTL 0x41d6b0
// SIZE: 404
// InitializeLogAndErrorHandler
// SIZE: 404

#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

extern int g_panic_callback;
extern void* g_crash_callback;
extern unsigned int g_log_mode_flags; /* TL image: re-derive VA from TL disasm, not 0x10034618 */
extern char g_crash_dump_all_frames;
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
	g_crash_callback = b;
	g_owner_window = c;
	g_crash_dump_all_frames = (d >> 4) & 1;
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) 0x0041cbc0);
	now = time(0);
	GetWindowTextA((HWND) c, path, 0x100);
	((void (__stdcall*)(int, const char*, int)) *(void**) 0x006620c0)(0, (const char*) 0x14ce620, 0x104);
	*strrchr((char*) 0x14ce620, 0x5c) = 0;
	sprintf((char*) 0x14cc600, (char*) 0x677cc8, path, ctime((long*) &now));
	if (g_log_mode_flags & 1) {
		string_cursor = (char*) 0x677948;
		do {
			sprintf(buf, (char*) 0x677adc, (char*) 0x14ce620, string_cursor);
			file = fopen(buf, "at");
			if (file != 0) {
				fseek(file, 0, 2);
				if (ftell(file) > 0x10000) {
					fclose(file);
					file = fopen(buf, "wt");
					fputs((char*) 0x677ca8, file);
				}
				fclose(file);
			}
			string_cursor += 0x20;
		} while ((int) string_cursor < 0x677ac8);
	}
	if (g_log_mode_flags & 8) {
		((void (__stdcall*)(void)) *(void**) 0x0066208c)();
		g_log_file_handle = ((int (__stdcall*)(int)) *(void**) 0x0066205c)(-0xb);
	}
	string_cursor = (char*) 0x677918;
	do {
		DispatchLogOutput((char*) 0x14cc600, g_log_mode_flags, *(int*) string_cursor);
		string_cursor += 4;
	} while ((int) string_cursor < 0x677948);
}
