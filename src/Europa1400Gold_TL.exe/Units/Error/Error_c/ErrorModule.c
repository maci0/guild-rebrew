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

/* Dispatches a log message to the configured output handlers
 * (file, debugger, etc.). Routes based on severity level. */

// FUNCTION: GOLDTL 0x41d4d0
// SIZE: 48
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
