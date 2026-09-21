#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity);

void __cdecl DispatchLogOutput(const char* text, int output_mask, int severity);

extern void (*g_panic_callback)(void);
extern unsigned int g_log_mode_flags;
extern int g_owner_window;
extern char g_log_message_buffer[];
extern char s_ERROR_Handler_has_not_been_100273fc[];
extern char s_Error_10027424[];
extern char s_FATAL_ERROR_s_lu_s_100273e0[];
extern char s_Fatal_Error_Abort_Program_100273c4[];

// FUNCTION: GOLDTL 0x41d8b0
// SIZE: 160
// ReportFatalError
__declspec(noreturn) void __cdecl exit(int);

void __cdecl ReportFatalError(char* modulePath, unsigned int lineNumber, char* message)
{
	unsigned int flags;
	int dialogResult;

	if (g_panic_callback == 0) {
		MessageBoxA((HWND) 0, s_ERROR_Handler_has_not_been_100273fc, s_Error_10027424, 0x30);
		return;
	}
	flags = g_log_mode_flags;
	if (flags == 0) {
		return;
	}
	if ((flags & 0xf) != 0) {
		sprintf(g_log_message_buffer, s_FATAL_ERROR_s_lu_s_100273e0, modulePath, lineNumber, message);
		flags = g_log_mode_flags;
	}
	if ((flags & 0xd) != 0) {
		DispatchLogOutput(g_log_message_buffer, flags, 1);
		flags = g_log_mode_flags;
	}
	if ((flags & 2) == 0) {
		return;
	}
	dialogResult = MessageBoxA((HWND) g_owner_window, g_log_message_buffer, s_Fatal_Error_Abort_Program_100273c4, 0x124);
	if (dialogResult != 6) {
		return;
	}
	g_panic_callback();
	exit(0xf);
}

/* Reports a non-fatal message through the logging system.
 * Dispatches to DispatchLogOutput with default severity. */
