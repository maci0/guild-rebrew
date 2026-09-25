// FUNCTION: GOLDTL 0x00420120
// SIZE: 126

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
extern CRITICAL_SECTION g_14cc5a0;
void __cdecl fcn_00420700(Chan* c, int mode);
void __cdecl fcn_0042ad90(int h, int f);
void __cdecl fcn_0042ac40(int h);

void __cdecl fcn_00420120(Chan* c, int fade)
{
	if (g_6b71a4 != 0) {
		EnterCriticalSection(&g_14cc5a0);
		if (c->active != 0) {
			if (fade != 0) {
				fcn_00420700(c, 2);
			} else {
				fcn_0042ad90(c->handle, 1);
				fcn_0042ac40(c->handle);
				c->handle = 0;
				c->active = 0;
			}
		}
		LeaveCriticalSection(&g_14cc5a0);
	}
}
