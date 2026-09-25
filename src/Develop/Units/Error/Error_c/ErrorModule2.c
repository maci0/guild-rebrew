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

// DATA: SERVER 0x100273ac
char s_Error_Handler_closed__100273ac[] = "Error-Handler closed.\n";

// DATA: SERVER 0x100273c4
char s_Fatal_Error_Abort_Program_100273c4[] = "Fatal Error! Abort Program?";

// DATA: SERVER 0x100273e0
char s_FATAL_ERROR_s_lu_s_100273e0[] = "FATAL ERROR (%s:%lu):\n%s\n";

// DATA: SERVER 0x100273fc
char s_ERROR_Handler_has_not_been_100273fc[] = "ERROR-Handler has not been started...";

// DATA: SERVER 0x10027424
char s_Error_10027424[] = "Error!";

// DATA: SERVER 0x1002742c
char s_Message_1002742c[] = "Message:";

// DATA: SERVER 0x10027438
char s_MESSAGE_s_10027438[] = "MESSAGE: %s\n";

// DATA: SERVER 0x10027448
char s_tModule_s_Line_lu_s_10027448[] = "tModule '%s':\tLine:%lu:\t%s";

// DATA: SERVER 0x10027464
char s_Time_8lu_Module_s_Line_10027464[] = "Time:%8lu\tModule '%s':\tLine:%lu:\t%s";

// GLOBAL: SERVER 0x10034618
unsigned int g_log_mode_flags = 0;

// GLOBAL: SERVER 0x117640e0
extern char g_log_message_buffer[];

/* Dispatches a log message to the configured output handlers
 * (file, debugger, etc.). Routes based on severity level. */

/* string referenced by ShutdownLogAndErrorHandler asm (was in the init body) */


/* REF 0x100273ac..0x10027488 — named emit; kill anonymous COMDATs in this TU. */

// GLOBAL: SERVER 0x117660e0
extern int g_owner_window;
extern void (*g_panic_callback)(void);
// FUNCTION: SERVER 0x100034c0
// ShutdownLogAndErrorHandler
void __cdecl ShutdownLogAndErrorHandler(void)
{
	int i;

	for (i = 0; i < 3; i++) {
		DispatchLogOutput(s_Error_Handler_closed__100273ac, g_log_mode_flags, g_log_level_table[i]);
	}
	if (g_log_mode_flags & 8) {
		FreeConsole();
		g_log_file_handle = 0;
	}
	g_panic_callback = 0;
	g_owner_window = 0;
	g_log_mode_flags = 0;
}


/* Reports a fatal error with a message, then terminates the
 * process via _exit(). Does not return. */

// FUNCTION: GOLDTL 0x41d8b0
// SIZE: 160
// FUNCTION: SERVER 0x10003520

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


// FUNCTION: SERVER 0x100035C0
// ReportMessage

void __cdecl ReportMessage(char* msg)
{
	if (!g_panic_callback) {
		MessageBoxA(0, s_ERROR_Handler_has_not_been_100273fc, s_Error_10027424, 0x10030);
		return;
	}
	if (!g_log_mode_flags) {
		return;
	}
	if (g_log_mode_flags & 0x0d) {
		sprintf(g_log_message_buffer, s_MESSAGE_s_10027438, msg);
		DispatchLogOutput(g_log_message_buffer, g_log_mode_flags, 1);
	}
	if (g_log_mode_flags & 2) {
		MessageBoxA(0, msg, s_Message_1002742c, 0x1030);
	}
}

/* Core logging function: formats and dispatches a log message
 * with source module path, line number, message text, and
 * severity level (1=error, 8=info, etc.). */

// FUNCTION: SERVER 0x10003640
// LogMessageInternal

void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity)
{
	unsigned char flags;

	if (*(int*) 0x10034610 == 0) {
		((void (__stdcall*)(int, char*, char*, int)) *(void**) 0x10024148)(0, s_ERROR_Handler_has_not_been_100273fc, s_Error_10027424, 0x10030);
		return;
	}
	flags = *(unsigned char*) 0x10034618;
	if (flags & 1) {
		if (flags & 0x20) {
			sprintf((char*) 0x117640e0, s_Time_8lu_Module_s_Line_10027464, ((int (__cdecl*)(void)) *(void**) 0x10024154)(), module, line, msg);
		} else {
			sprintf((char*) 0x117640e0, s_tModule_s_Line_lu_s_10027448, module, line, msg);
		}
		DispatchLogOutput((char*) 0x117640e0, *(int*) 0x10034618, severity);
	}
}
