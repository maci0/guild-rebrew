// FUNCTION: GOLD 0x52e1f0
// SIZE: 368
// FUNCTION: GOLDTL 0x005338d0
// SIZE: 368

#include <stdio.h>
#include <string.h>

// SIZE 0xc8
typedef struct {
	char* obj;
	char name[0x40];
	int arg;
	char path[0x80];
} Cache;

extern Cache g_7e46c0[32];
extern char g_6a3110[];
extern char g_6a30e4[];

char* __cdecl fcn_00412eb0(char* name, int mode);

char* __cdecl fcn_005338d0(char* name, char* path, int arg)
{
	char buf[256];
	int i;

	for (i = 0; i < 32; i++) {
		if (g_7e46c0[i].obj != 0 && strcmp(g_7e46c0[i].name, name) == 0) {
			*(int*) (g_7e46c0[i].obj + 0x224) = 1;
			return g_7e46c0[i].obj;
		}
	}
	for (i = 0; i < 32; i++) {
		if (g_7e46c0[i].obj == 0) {
			break;
		}
	}
	if (i >= 32) {
		sprintf(buf, g_6a3110, name);
		return 0;
	}
	g_7e46c0[i].obj = fcn_00412eb0(name, 2);
	if (g_7e46c0[i].obj == 0) {
		sprintf(buf, g_6a30e4, name);
		return 0;
	}
	g_7e46c0[i].arg = arg;
	strncpy(g_7e46c0[i].path, path, 0x80);
	strncpy(g_7e46c0[i].name, name, 0x40);
	g_7e46c0[i].path[0x7f] = 0;
	g_7e46c0[i].name[0x3f] = 0;
	*(int*) (g_7e46c0[i].obj + 0x224) = 1;
	return g_7e46c0[i].obj;
}
