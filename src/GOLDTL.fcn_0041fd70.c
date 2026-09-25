// FUNCTION: GOLD 0x00423a90
// SIZE: 160
// FUNCTION: GOLDTL 0x0041fd70
// SIZE: 160

#include <string.h>
#include <windows.h>

// SIZE 0x128
typedef struct {
	char name[0x100];
	int handle;
	unsigned char active;
	unsigned char b105;
	unsigned char b106;
	unsigned char b107;
	int f108;
	int f10c;
	char pad110[0x128 - 0x110];
} Chan;

extern int g_6b71a4;
extern Chan g_14cc460;
extern CRITICAL_SECTION g_14cc5a0;
Chan* __cdecl fcn_004205e0(const char* name);
Chan* __cdecl fcn_00420690(void);
int __cdecl fcn_0041fe10(Chan* c, int a);

Chan* __cdecl fcn_0041fd70(const char* name, int a)
{
	Chan* c;

	if (g_6b71a4 == 0) {
		return &g_14cc460;
	}
	EnterCriticalSection(&g_14cc5a0);
	c = fcn_004205e0(name);
	LeaveCriticalSection(&g_14cc5a0);
	if (c == 0) {
		EnterCriticalSection(&g_14cc5a0);
		c = fcn_00420690();
		if (c != 0) {
			memset(c, 0, sizeof(Chan));
			strcpy(c->name, name);
		}
		LeaveCriticalSection(&g_14cc5a0);
	}
	c->b106 = 0;
	if (fcn_0041fe10(c, a) == -1) {
		c = 0;
	}
	return c;
}
