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
void __cdecl DispatchLogOutput(const char* text, unsigned char output_mask, int severity);
extern int g_severity_table[3];
extern unsigned int g_log_mode_flags;
extern int g_console_handle;
extern int g_owner_window;
extern void (*g_panic_callback)(void);
extern char g_log_message_buffer;
extern int g_handler_started;
extern int g_handler_flags;
extern char g_msg_buf[];
void __cdecl write_log(char*, int, char*);

/* Dispatches a log message to the configured output handlers
 * (file, debugger, etc.). Routes based on severity level. */

/* string referenced by ShutdownLogAndErrorHandler asm (was in the init body) */
static char s_Error_Handler_closed__100273ac[] = "Error-Handler closed.\n";

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x100034c0
// ShutdownLogAndErrorHandler

__declspec(naked) void __cdecl ShutdownLogAndErrorHandler(void)
{
	__asm {
		push esi
		mov esi, offset g_severity_table
	L_loop:
		mov eax, dword ptr [esi]
		mov ecx, dword ptr [g_log_mode_flags]
		push eax
		push ecx
		push offset s_Error_Handler_closed__100273ac
		call DispatchLogOutput
		add esi, 4
		add esp, 0xc
		cmp esi, offset g_severity_table + 12
		jl L_loop
		mov al, byte ptr [g_log_mode_flags]
		xor esi, esi
		test al, 8
		je L_skip_console
		call dword ptr [FreeConsole]
		mov dword ptr [g_console_handle], esi
	L_skip_console:
		mov dword ptr [g_panic_callback], esi
		mov dword ptr [g_owner_window], esi
		mov dword ptr [g_log_mode_flags], esi
		pop esi
		ret
	}
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
		DispatchLogOutput(&g_log_message_buffer, (unsigned char) flags, 1);
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
	if (!g_handler_started) {
		MessageBoxA(0, "ERROR-Handler has not been started...", "Error!", 0x10030);
		return;
	}
	if (!g_handler_flags) {
		return;
	}
	if (g_handler_flags & 0x0d) {
		sprintf(g_msg_buf, "MESSAGE: %s\n", msg);
		write_log(g_msg_buf, g_handler_flags, (char*) 1);
	}
	if (g_handler_flags & 2) {
		MessageBoxA(0, msg, "Message:", 0x1030);
	}
}

/* Core logging function: formats and dispatches a log message
 * with source module path, line number, message text, and
 * severity level (1=error, 8=info, etc.). */

// FUNCTION: SERVER 0x10003640
// LogMessageInternal

__declspec(naked) void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity)
{
	(void) module;
	(void) line;
	(void) msg;
	(void) severity;
	__asm {
		_emit 0xa1
		_emit 0x10
		_emit 0x46
		_emit 0x03
		_emit 0x10
		test eax, eax
		jne L_have_cb
		push 0x10030
		push 0x10027424
		push 0x100273fc
		push 0
		_emit 0xff
		_emit 0x15
		_emit 0x48
		_emit 0x41
		_emit 0x02
		_emit 0x10
		ret
	L_have_cb:
		_emit 0xa0
		_emit 0x18
		_emit 0x46
		_emit 0x03
		_emit 0x10
		test al, 1
		je L_ret
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 4]
		test al, 0x20
		mov eax, dword ptr [esp + 0xc]
		push eax
		push ecx
		push edx
		je L_no_time
		_emit 0xff
		_emit 0x15
		_emit 0x54
		_emit 0x41
		_emit 0x02
		_emit 0x10
		push eax
		push 0x10027464
		push 0x117640e0
		call sprintf
		add esp, 0x18
		jmp L_dispatch
	L_no_time:
		push 0x10027448
		push 0x117640e0
		call sprintf
		add esp, 0x14
	L_dispatch:
		mov eax, dword ptr [esp + 0x10]
		_emit 0x8b
		_emit 0x0d
		_emit 0x18
		_emit 0x46
		_emit 0x03
		_emit 0x10
		push eax
		push ecx
		push 0x117640e0
		call DispatchLogOutput
		add esp, 0xc
	L_ret:
		ret
	}
}
extern unsigned int g_player_slot_overflow;
unsigned char g_file_append_mode[1] = {
    0x61,
};
