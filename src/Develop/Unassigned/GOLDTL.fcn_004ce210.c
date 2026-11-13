extern int g_9badd0;

#include <string.h>

typedef struct {
	int g;
	int a;
} info8;

typedef struct {
	char kind;
	char pad1[0xf];
	int f10;
	info8 info;
	char pad1c[0x80];
} msg9c;

int __cdecl fcn_004c4330(msg9c*);

/* ADDRESS: GOLDTL 0x004ce210 */
int __cdecl fcn_004ce210(int a1)
{
	info8 info;
	msg9c m;

	memset(&m.f10, 0, 0x80);
	info.g = g_9badd0;
	m.kind = 0x5f;
	m.f10 = 1;
	info.a = a1;
	m.info = info;
	return fcn_004c4330(&m);
}
