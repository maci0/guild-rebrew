#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity);
extern char* __cdecl ctime(const time_t*);

char __cdecl check_memory_protection(unsigned int);
char __cdecl AnalyzeInstruction(int, int, int, int*);
unsigned int __cdecl EmitCrashModuleLine(int*);
char* __cdecl GetDebugRecordByIndex();
void __cdecl DispatchLogOutput(const char* text, int output_mask, int severity);
extern int g_log_level_table[];
extern unsigned int g_log_mode_flags;
extern int g_console_handle;
extern int g_owner_window;
extern void (*g_panic_callback)(void);
extern char g_log_message_buffer;
extern int g_handler_started;
extern int g_log_mode_flags;
extern char g_msg_buf[];
void __cdecl write_log(char*, int, char*);

/* Dispatches a log message to the configured output handlers
 * (file, debugger, etc.). Routes based on severity level. */

/* string referenced by ShutdownLogAndErrorHandler asm (was in the init body) */
static char s_Error_Handler_closed__100273ac[] = "Error-Handler closed.\n";

// FUNCTION: SERVER 0x100034c0
// ShutdownLogAndErrorHandler
void __cdecl ShutdownLogAndErrorHandler(void)
{
	int i;

	for (i = 0; i < 3; i++) {
		DispatchLogOutput((char*) 0x100273ac, g_log_mode_flags, g_log_level_table[i]);
	}
	if (g_log_mode_flags & 8) {
		FreeConsole();
		g_console_handle = 0;
	}
	g_panic_callback = 0;
	g_owner_window = 0;
	g_log_mode_flags = 0;
}


/* Reports a fatal error with a message, then terminates the
 * process via _exit(). Does not return. */

// FUNCTION: SERVER 0x10003520
// ReportFatalError
__declspec(noreturn) void __cdecl _exit(int);

void __cdecl ReportFatalError(char* modulePath, unsigned int lineNumber, char* message)
{
	unsigned int flags;
	int dialogResult;

	if (g_panic_callback == 0) {
		MessageBoxA((HWND) 0, "ERROR Handler has not been started!", "Error!", 0x30);
		return;
	}
	flags = g_log_mode_flags;
	if (flags == 0) {
		return;
	}
	if ((flags & 0xf) != 0) {
		sprintf(&g_log_message_buffer, "FATAL ERROR (%s:%lu):\n%s\n", modulePath, lineNumber, message);
		flags = g_log_mode_flags;
	}
	if ((flags & 0xd) != 0) {
		DispatchLogOutput(&g_log_message_buffer, flags, 1);
		flags = g_log_mode_flags;
	}
	if ((flags & 2) == 0) {
		return;
	}
	dialogResult = MessageBoxA((HWND) g_owner_window, &g_log_message_buffer, "Fatal Error! Abort Program?", 0x124);
	if (dialogResult != 6) {
		return;
	}
	g_panic_callback();
	_exit(0xf);
}

/* Reports a non-fatal message through the logging system.
 * Dispatches to DispatchLogOutput with default severity. */

// FUNCTION: SERVER 0x100035C0
// ReportMessage

void __cdecl ReportMessage(char* msg)
{
	if (!g_panic_callback) {
		MessageBoxA(0, "ERROR-Handler has not been started...", "Error!", 0x10030);
		return;
	}
	if (!g_log_mode_flags) {
		return;
	}
	if (g_log_mode_flags & 0x0d) {
		sprintf(g_msg_buf, "MESSAGE: %s\n", msg);
		write_log(g_msg_buf, g_log_mode_flags, (char*) 1);
	}
	if (g_log_mode_flags & 2) {
		MessageBoxA(0, msg, "Message:", 0x1030);
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
		((void (__stdcall*)(int, char*, char*, int)) *(void**) 0x10024148)(0, (char*) 0x100273fc, (char*) 0x10027424, 0x10030);
		return;
	}
	flags = *(unsigned char*) 0x10034618;
	if (flags & 1) {
		if (flags & 0x20) {
			sprintf((char*) 0x117640e0, (char*) 0x10027464, ((int (__cdecl*)(void)) *(void**) 0x10024154)(), module, line, msg);
		} else {
			sprintf((char*) 0x117640e0, (char*) 0x10027448, module, line, msg);
		}
		DispatchLogOutput((char*) 0x117640e0, *(int*) 0x10034618, severity);
	}
}
extern unsigned int g_player_slot_overflow;
unsigned char g_file_append_mode[1] = {
    0x61,
};
