// GLOBAL: GOLD 0x6332dc
extern char* g_6b7ebc;
extern char* g_6b7e98;
// GLOBAL: GOLD 0x5f8430
extern int g_6791c8;
#include <string.h>


void __cdecl fcn_0040c090();
char* __cdecl fcn_0040b400(char*, void (__cdecl*)(), unsigned char, int, ...);
void __cdecl fcn_004273d0(char*, int, const char*);

// FUNCTION: GOLD 0x40c4f0

/* TakeObjectScript(): queues a take-object animation task that runs a
 * script; the calling script waits for it when it blocks. */
int __cdecl fcn_0040c4f0(char** ch, char** ani, int* kind, char** dummy, unsigned char* level, char** func)
{
	char* task;

	if (g_6b7ebc != 0 && *(int (__cdecl**)()) (g_6b7ebc + 0x44) == (int (__cdecl*)()) fcn_0040c4f0) {
		if (*(int*) (*ch + 0x128) != 0) {
			*(int (__cdecl**)()) (g_6b7e98 + 0xc60) = (int (__cdecl*)()) fcn_0040c4f0;
		}
		return 0;
	}
	if (*ch == 0) {
		fcn_004273d0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "TakeObjectScript(): Invalid character");
		return 1;
	}
	if (*dummy == 0) {
		fcn_004273d0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "TakeObjectScript(): Invalid dummy");
		return 1;
	}
	task = fcn_0040b400(*ch, fcn_0040c090, *level, 0x31, *kind);
	if (task != 0) {
		strcpy(task + 0xf0, *ani);
		if (*dummy != 0 && *(char**) (*dummy + 0x1ec) != 0 && *(char**) (*(char**) (*dummy + 0x1ec) + 0x104) != 0) {
			strcpy(task + 0x130, *(char**) (*(char**) (*dummy + 0x1ec) + 0x104));
		}
		strcpy(task + 0x90, *func);
		*(int*) (task + 0x17c) = g_6791c8;
	}
	if (*(int*) (g_6b7e98 + 0xc84) == 1) {
		*(int (__cdecl**)()) (g_6b7e98 + 0xc60) = (int (__cdecl*)()) fcn_0040c4f0;
	}
	return 0;
}
