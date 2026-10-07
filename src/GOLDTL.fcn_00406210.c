// FUNCTION: GOLD 0x00405670
// FUNCTION: GOLDTL 0x00406210

#include <string.h>

// SIZE 0x4c
#include "client_types.h"
typedef Entry_14d0c40 Entry;

extern Entry_14d0c40 g_14d0c40[];
void __cdecl fcn_0041d9e0(const char* msg);

int __cdecl fcn_00406210(int idx, int handler, unsigned char kind, const char* name, int param)
{
	if (idx > 0x3f) {
		return 0;
	}
	if (g_14d0c40[idx].handler != 0) {
		fcn_0041d9e0("slot already in use");
		return 0;
	}
	g_14d0c40[idx].handler = handler;
	g_14d0c40[idx].kind = kind;
	g_14d0c40[idx].param = param;
	strcpy(g_14d0c40[idx].name, name);
	return 1;
}
