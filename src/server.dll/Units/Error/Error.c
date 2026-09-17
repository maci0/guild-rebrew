#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

void __cdecl DispatchLogOutput(const char* text, unsigned char output_mask, int severity);
extern void (*g_panic_callback)(void);

/* Dispatches a log message to the configured output handlers
 * (file, debugger, etc.). Routes based on severity level. */

// FUNCTION: SERVER 0x10002640
// DispatchLogOutput



/* THREE ints, not twelve.  The reference gives this table 12 bytes
 * (0x10027078..0x10027084, where g_log_format_table begins) and DispatchLogOutput
 * only ever indexes [0..2].  The initialiser was written as the twelve BYTES
 * 01 00 00 00 02 00 00 00 08 00 00 00 but spelled `int[12]`, which emits 48
 * bytes -- a 36-byte surplus that pushed every later symbol in the section. */
int g_log_level_table[3] = {
    0x01, 0x02, 0x08,
};

/* Three 0x20-byte log-file names, not one.  InitializeLogAndErrorHandler walks
 * this table from 0x10027084 in 0x20 steps until 0x100270e4 and DispatchLogOutput
 * indexes it as `g_log_format_table + idx * 32`, and the reference has
 * "__server.log", "gilde_server.log" and "__dbg.log" there.  Declaring only the
 * first 13 bytes left the other two absent from the image entirely. */
char g_log_format_table[96] = {
    0x5f, 0x5f, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x2e, 0x6c, 0x6f, 0x67,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x69, 0x6c, 0x64,
    0x65, 0x5f, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x2e, 0x6c, 0x6f, 0x67,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x5f, 0x5f, 0x64, 0x62, 0x67, 0x2e, 0x6c, 0x6f,
    0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
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
		fclose(stream);
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

