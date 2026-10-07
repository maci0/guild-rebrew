// FUNCTION: GOLD 0x004cd6e0
// FUNCTION: GOLDTL 0x4ce2a0

#include <string.h>

typedef struct {
	int g;
	int a;
	char name[0x40];
} info48;
// SIZE 0x48

typedef struct {
	char kind;
	char pad1[0xf];
	int f10;
	info48 info;
	char pad5c[0x40];
} msg9c;
// SIZE 0x9c

extern int g_9badd0;

int __cdecl fcn_004c4330(msg9c*);
char* __cdecl fcn_0064d530(char*, char*, int);

int __cdecl fcn_004ce2a0(int a, char* s)
{
	info48 info;
	msg9c m;

	memset(&m.f10, 0, 0x80);
	info.g = g_9badd0;
	m.kind = 0x5f;
	info.a = a;
	fcn_0064d530(info.name, s, 0x3f);
	info.name[0x3f] = 0;
	m.f10 = 6;
	m.info = info;
	return fcn_004c4330(&m);
}
