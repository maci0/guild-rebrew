#include <string.h>

typedef struct TexDesc {
	int pad0;
	int w;
	int h;
	int rest[0x14];
} TexDesc;
// SIZE 0x5c

typedef struct TexSlot {
	int a;
	int b;
	void* tex;
} TexSlot;
// SIZE 0xc

typedef struct Tag {
	int id;
	int val;
	int pad;
} Tag;
// SIZE 0xc

extern char* g_7725c0;
extern short g_7725c4;
extern void* g_100f8a0;
extern TexSlot g_100f860[3];
extern TexSlot g_100f840;
#include "client_types.h"
extern Pair0c_1011980 g_1011980[6];

void* __cdecl fcn_004770a0(TexDesc* d, int fmt);

// FUNCTION: GOLDTL 0x473df0
// SIZE: 222
void __cdecl fcn_00473df0(void)
{
	TexDesc d;
	int i;

	(*(void**)&g_7725c0) = 0;
	g_7725c4 = 0;
	memset(&d, 0, sizeof(d));
	d.w = 0x40;
	d.h = 0x40;
	g_100f8a0 = fcn_004770a0(&d, 1);
	for (i = 0; i < 3; i++) {
		memset(&d, 0, sizeof(d));
		g_100f860[i].a = -1;
		g_100f860[i].b = -1;
		d.w = 0x80;
		d.h = 0x80;
		g_100f860[i].tex = fcn_004770a0(&d, 3);
	}
	memset(&d, 0, sizeof(d));
	g_100f840.a = -1;
	g_100f840.b = -1;
	d.w = 0x100;
	d.h = 0x100;
	g_100f840.tex = fcn_004770a0(&d, 3);
	for (i = 0; i < 6; i++) {
		((Tag*)g_1011980)[i].id = -1;
		((Tag*)g_1011980)[i].val = 0;
	}
}
