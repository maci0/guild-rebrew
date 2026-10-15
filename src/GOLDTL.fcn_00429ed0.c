#include <stdarg.h>
#include <string.h>

// SIZE 0x4c
struct cmd_429ed0 {
	char name[0x20];
	int nargs;
	int types[8];
	void* fn;
	int flags;
};

extern void* g_6b7e9c;

#include "Develop/Units/Error/error_message.h"
int __cdecl fcn_00429e60(const char*);

/* ADDRESS: GOLD 0x0042b5b0 */
/* ADDRESS: GOLDTL 0x00429ed0 */

/* evt_ImportCommand: registers a script command with its argument types. */
int __cdecl fcn_00429ed0(const char* name, void* fn, int flags, int nargs, ...)
{
	int i;
	int k;
	va_list ap;

	i = 0;
	if (strlen(name) > 0x1f) {
		fcn_0041d9e0("evt_ImportCommand: Commandnamelength is invalid...");
		return 0;
	}
	if (fcn_00429e60(name)) {
		fcn_0041d9e0("evt_ImportCommand: Commandname already exists...");
		return 0;
	}
	for (; i < 0x100; i++) {
		if (((struct cmd_429ed0*)g_6b7e9c)[i].fn == 0) {
			break;
		}
	}
	if (i >= 0x100) {
		fcn_0041d9e0("evt_ImportCommand: Too many commands!");
		return 0;
	}
	((struct cmd_429ed0*)g_6b7e9c)[i].fn = fn;
	((struct cmd_429ed0*)g_6b7e9c)[i].nargs = nargs;
	((struct cmd_429ed0*)g_6b7e9c)[i].flags = flags;
	va_start(ap, nargs);
	for (k = 0; k < nargs; k++) {
		((struct cmd_429ed0*)g_6b7e9c)[i].types[k] = va_arg(ap, int);
	}
	va_end(ap);
	strcpy(((struct cmd_429ed0*)g_6b7e9c)[i].name, name);
	return 1;
}
