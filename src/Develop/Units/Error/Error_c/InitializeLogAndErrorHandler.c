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
extern char g_log_message_buffer[0x2000];
extern char s_error_log_banner[];
extern char s_LogFile_has_been_deleted[];
LONG __stdcall CrashDumpUnhandledExceptionFilter(struct _EXCEPTION_POINTERS* info);
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
	SetUnhandledExceptionFilter(CrashDumpUnhandledExceptionFilter);
	now = time(0);
	GetWindowTextA((HWND) c, path, 0x100);
	GetModuleFileNameA(0, g_log_buffer, 0x104);
	*strrchr(g_log_buffer, 0x5c) = 0;
	sprintf(g_log_message_buffer, s_error_log_banner, path, ctime((long*) &now));
	if (g_log_mode_flags & 1) {
		string_cursor = g_log_format_table;
		do {
			sprintf(buf, "%s\\%s", g_log_buffer, string_cursor);
			file = fopen(buf, "at");
			if (file != 0) {
				fseek(file, 0, 2);
				if (ftell(file) > 0x10000) {
					fclose(file);
					file = fopen(buf, (const char*) g_file_write_mode);
					fputs(s_LogFile_has_been_deleted, file);
				}
				fclose(file);
			}
			string_cursor += 0x20;
		} while ((int) string_cursor < (int) (g_log_format_table + sizeof(g_log_format_table)));
	}
	if (g_log_mode_flags & 8) {
		AllocConsole();
		g_log_file_handle = (int) GetStdHandle(STD_OUTPUT_HANDLE);
	}
	string_cursor = (char*) g_log_level_table;
	do {
		DispatchLogOutput(g_log_message_buffer, g_log_mode_flags, *(int*) string_cursor);
		string_cursor += 4;
	} while ((int) string_cursor < (int) (g_log_level_table + 3));
}
