

// SIZE 0x3cc
typedef struct {
	char pad0[0xc];
	int width;
	int height;
	char pad14[0x3cc - 0x14];
} Slot;

// SIZE 0x2bc
typedef struct {
	int owner;
	char pad4[0x2bc - 4];
} Item;

// SIZE 0x34
typedef struct {
	int key;
	int a;
	int b;
	int padc;
	char* from;
	char* to;
	char pad18[0x34 - 0x18];
} Edge;

extern int g_7f4c10;
extern int g_6b7fac;
extern int g_7f3ee8;
extern Item g_1038150[];
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char g_699a9c[];
extern int g_85ab60;
extern Rec34_7f3f00 g_7f3f00[];

int __cdecl fcn_00470820(int a, int b, int c);
void __cdecl fcn_00471b60(int h);
void __cdecl d2_SetForm(int h, int mode);
void __cdecl fcn_00519190(char* fmt, int a, int b);
int __cdecl fcn_0050e830(unsigned char* a, unsigned short* b, int w, int h);
void __cdecl fcn_00471e30(int h);
void __cdecl fcn_0050ee80(unsigned char* a, unsigned short* b);
void __cdecl fcn_0050f750(char* a, char* b, char* c, char* d);

int __cdecl fcn_0050f780(int arg, unsigned char* a, unsigned short* b)
{
	Slot* s;
	int i;
	int j;

	g_7f4c10 = fcn_00470820(0, 0, arg);
	fcn_00471b60(g_7f4c10);
	g_7f3ee8 = g_6b7fac;
	s = &((Slot*)g_1015f40)[g_1038150[g_7f4c10].owner];
	d2_SetForm(0, 1);
	if (*b == 0xfd) {
		fcn_00519190(g_699a9c, 0x19, *a * 14 + 0x48e);
	} else {
		fcn_00519190(g_699a9c, 0x19, *b * 2 + 0x9a8);
	}
	d2_SetForm(0, 3);
	if (fcn_0050e830(a, b, s->width, s->height)) {
		fcn_00471e30(g_7f4c10);
		return -1;
	}
	fcn_0050ee80(a, b);
	for (i = 0; i < g_85ab60; i++) {
		for (j = 0; j < i; j++) {
			if (((Edge*)g_7f3f00)[j].key == ((Edge*)g_7f3f00)[i].a) {
				fcn_0050f750(((Edge*)g_7f3f00)[j].from + 0x18, ((Edge*)g_7f3f00)[j].to + 0x30, ((Edge*)g_7f3f00)[i].from + 0x18,
					     ((Edge*)g_7f3f00)[i].to + 0x18);
			} else if (((Edge*)g_7f3f00)[j].key == ((Edge*)g_7f3f00)[i].b) {
				fcn_0050f750(((Edge*)g_7f3f00)[j].from + 0x18, ((Edge*)g_7f3f00)[j].to + 0x30, ((Edge*)g_7f3f00)[i].from + 0x18,
					     ((Edge*)g_7f3f00)[i].to + 0x18);
			}
		}
	}
	return g_7f4c10;
}
