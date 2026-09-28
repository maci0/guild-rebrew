#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
char __cdecl check_memory_protection(unsigned int);
char __cdecl AnalyzeInstruction(int, int, int, int*);
char* __cdecl GetDebugRecordByIndex();
extern void (*g_panic_callback)(void);

// DATA: SERVER 0x1002733c
char s_LogFile_has_been_deleted[] = "LogFile has been deleted!\n";

// DATA: SERVER 0x10027358
unsigned char g_file_write_mode[3] = {
    0x77, 0x74, 0x00,
};

// DATA: SERVER 0x1002735c
char s_error_log_banner[] = "* ------------------------------------------------------------ *\n[%s], Date: %s";
// FUNCTION: GOLD 0x421ed0
// SIZE: 48
// FUNCTION: GOLDTL 0x41d4d0
// SIZE: 48
// FUNCTION: SERVER 0x10003140

// GetDebugRecordByIndex

/* Variable-length record accessor - walks a record table to find the nth entry */

char* __cdecl GetDebugRecordByIndex(char* arg1, unsigned int arg2)
{
	char* result;

	if (arg2 < *(unsigned int*) (arg1 + 4)) {
		result = arg1 + 0x10;
		if (arg2 <= 0) {
			return result;
		}
		do {
			result = result + *(int*) result + 4;
		} while (--arg2);
		return result;
	}
	return 0;
}

/* Checks if a memory page's protection flags indicate it is
 * readable. Returns 1 if the protection includes read access. */


// FUNCTION: SERVER 0x10003170
// check_memory_protection

char __cdecl check_memory_protection(unsigned int protect)
{
	MEMORY_BASIC_INFORMATION mbi;

	VirtualQuery(check_memory_protection, &mbi, 0x1c);

	switch (protect & 0xFF) {
	case 2:
	case 4:
		return mbi.Protect == 2 || mbi.Protect == 4;
	case 0x10:
	case 0x20:
	case 0x40:
	case 0x80:
		return 1;
	}
	return 0;
}

/* Analyzes an x86 instruction at the given address to determine
 * its length and type. Used by the crash dump handler to decode
 * the faulting instruction context. */

// FUNCTION: GOLD 0x421ff0
// SIZE: 192
// FUNCTION: GOLDTL 0x41d5f0
// SIZE: 192
// FUNCTION: SERVER 0x10003260
// AnalyzeInstruction
char __cdecl AnalyzeInstruction(int arg1, int arg2, int arg3, int* arg4)
{
	*arg4 = 0;
	if (arg2 >= 5 && *(unsigned char *) (arg1 - 5) == 0xe8) {
		*arg4 = *(int *) (arg1 - 4) + arg3;
		return 1;
	}
	if (arg2 >= 3 && *(char *) (arg1 - 3) == -1 && *(unsigned char *) (arg1 - 2) == 0x14) return 2;
	if (arg2 >= 6 && *(char *) (arg1 - 6) == -1 && *(unsigned char *) (arg1 - 5) == 0x15) return 2;
	if (arg2 >= 2 && *(char *) (arg1 - 2) == -1 && *(unsigned char *) (arg1 - 1) < 0x40) return 2;
	if (arg2 >= 2 && *(char *) (arg1 - 2) == -1 && (*(unsigned char *) (arg1 - 1) & 0xf8) == 0xd0) return 2;
	if (arg2 >= 3 && *(char *) (arg1 - 3) == -1 && (*(unsigned char *) (arg1 - 2) & 0xf8) == 0x50) return 2;
	if (arg2 >= 7 && *(char *) (arg1 - 7) == -1 && (*(unsigned char *) (arg1 - 6) & 0xf8) == 0x90) return 2;
	return 0;
}


/* Initializes the logging and error handling subsystem.
 * Opens log files, sets up exception handlers, and configures
 * output severity filters. */
