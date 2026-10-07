/* Initializes the log/error handler: stores the module/severity
 * settings, installs the crash-dump filter, resolves the log file
 * directory, and installs per-level log file handles. */

// FUNCTION: GOLD 0x004220b0
// FUNCTION: GOLDTL 0x41d6b0
// InitializeLogAndErrorHandler

#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

extern void (*g_panic_callback)(void);
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
extern char g_14cc600[];
extern char g_14ce620[];
extern char g_677918[];
extern char g_677948[];
extern char g_677ac8[];
extern char g_677adc[];
extern char g_677ca8[];
extern char g_677cc8[];
LONG __stdcall fcn_0041cbc0(struct _EXCEPTION_POINTERS* info);

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
	SetUnhandledExceptionFilter(fcn_0041cbc0);
	now = time(0);
	GetWindowTextA((HWND) c, path, 0x100);
	GetModuleFileNameA(0, g_14ce620, 0x104);
	*strrchr(g_14ce620, 0x5c) = 0;
	sprintf(g_14cc600, g_677cc8, path, ctime((long*) &now));
	if (g_log_mode_flags & 1) {
		string_cursor = g_677948;
		do {
			sprintf(buf, g_677adc, g_14ce620, string_cursor);
			file = fopen(buf, "at");
			if (file != 0) {
				fseek(file, 0, 2);
				if (ftell(file) > 0x10000) {
					fclose(file);
					file = fopen(buf, "wt");
					fputs(g_677ca8, file);
				}
				fclose(file);
			}
			string_cursor += 0x20;
		} while ((int) string_cursor < (int) g_677ac8);
	}
	if (g_log_mode_flags & 8) {
		AllocConsole();
		g_log_file_handle = (int) GetStdHandle(STD_OUTPUT_HANDLE);
	}
	string_cursor = g_677918;
	do {
		DispatchLogOutput(g_14cc600, g_log_mode_flags, *(int*) string_cursor);
		string_cursor += 4;
	} while ((int) string_cursor < (int) g_677948);
}
