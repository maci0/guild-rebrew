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

// FUNCTION: SERVER 0x10002640
// DispatchLogOutput

// DATA: SERVER 0x11766100
extern char g_log_buffer[256];

// DATA: SERVER 0x11766204
extern int g_log_file_handle;

// DATA: SERVER 0x10027078
int g_log_level_table[12] = {
    0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
};

// DATA: SERVER 0x10027084
char g_log_format_table[13] = {
    0x5f, 0x5f, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x2e, 0x6c, 0x6f, 0x67, 0x00,
};

/* The log module's own literal pool copies (this TU's .data), used because
 * the same text occurs earlier in .rdata/.data and content-scan binding
 * would resolve to those copies instead of the ones this code targets. */

// DATA: SERVER 0x100270e4
char g_log_newline[2] = { 0x0a, 0x00, };

// DATA: SERVER 0x100270e8
char g_log_default_name[13] = {
    0x5f, 0x5f, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x2e, 0x6c, 0x6f, 0x67, 0x00,
};

void __cdecl DispatchLogOutput(const char* msg, unsigned char flags, int level)
{
	char buf[260];
	unsigned int written;
	FILE* stream;
	int idx;

	if (flags & 1) {
		idx = 0;
		while (idx < 3) {
			if (level == g_log_level_table[idx]) {
				goto found;
			}
			idx++;
		}
		goto fallback;

	found:
		sprintf(buf, "%s\\%s", g_log_buffer, g_log_format_table + idx * 32);
		stream = (FILE*) fopen(buf, "at");
		if (stream != 0) {
			goto do_write;
		}

	fallback:
		sprintf(buf, "%s\\%s", g_log_buffer, g_log_default_name);
		stream = (FILE*) fopen(buf, "at");
		if (stream == 0) {
			goto skip;
		}

	do_write:
		fputs(msg, stream);
		fputs(g_log_newline, stream);
		fflush(stream);
	skip:;
	}

	if (flags & 4) {
		OutputDebugStringA(msg);
		OutputDebugStringA(g_log_newline);
	}

	if (flags & 8) {
		WriteConsoleA((HANDLE) g_log_file_handle, msg, strlen(msg), &written, 0);
		WriteConsoleA((HANDLE) g_log_file_handle, g_log_newline, 1, &written, 0);
	}
}

/* Unhandled exception filter for crash dumps. Creates a
 * minidump file with module info and stack trace when the
 * process crashes. */

