// FUNCTION: GOLDTL 0x00420780
// SIZE: 192
// FUNCTION: GOLD 0x004243f0
// SIZE: 192

#include <string.h>
#include <windows.h>

// SIZE 0x128
#include "client_types.h"
typedef Chan_14cc460 Chan;

extern int g_6b71a8;
extern Chan_14cc460 g_14cc460;
extern CRITICAL_SECTION g_14cc5a0;
Chan* __cdecl fcn_004205e0(const char* name);
Chan* __cdecl fcn_00420690(void);
int __cdecl fcn_0041fe10(Chan* c, int a);
void __cdecl fcn_0042ac40(int h);
void __cdecl fcn_0041fc10(Chan* c, int a);

Chan* __cdecl fcn_00420780(const char* name, int a)
{
	Chan* c;

	if (g_6b71a8 == 0) {
		return &g_14cc460;
	}
	EnterCriticalSection(&g_14cc5a0);
	c = fcn_004205e0(name);
	if (c == 0) {
		c = fcn_00420690();
		if (c != 0) {
			memset(c, 0, sizeof(Chan));
			strcpy(c->name, name);
		}
	}
	if (c != 0) {
		c->b106 = 1;
		if (c->handle != 0) {
			fcn_0042ac40(c->handle);
			c->handle = 0;
		}
		if (fcn_0041fe10(c, 1) == 0) {
			fcn_0041fc10(c, a);
			LeaveCriticalSection(&g_14cc5a0);
			return c;
		}
	}
	LeaveCriticalSection(&g_14cc5a0);
	return 0;
}
