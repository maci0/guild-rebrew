// FUNCTION: GOLDTL 0x00487970
// SIZE: 649

#include <string.h>

// SIZE 0x21c
typedef struct Ent {
	int id;
	int handle;
	char pad8[0x21c - 8];
} Ent;

// SIZE 0x24d
typedef struct Race {
	char pad0[0x240];
	unsigned char cap_x;
	unsigned char cap_y;
	char pad242[0x24d - 0x242];
} Race;

extern char g_7f4ca0[];
extern unsigned char* g_868050;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_773d75;
extern char g_67e33c[];

unsigned short __cdecl fcn_0042e410(int n);
char* __cdecl fcn_005463a0(int a, int b, int c, int d, int e);
char* __cdecl fcn_005462a0(void);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c5150(int a, int b, char c, int n);
int __cdecl fcn_0051e070(void);
void __cdecl fcn_0051af00(void* out, int id, ...);
void __cdecl fcn_00545e80(int a, int b, char* text, int c, int d, int e, int f, int g, int h);

void __cdecl fcn_00487970(char* src, char* e, int chance)
{
	char msg[0xf8];
	char buf[0x400];
	char* h;
	char* it;
	Race* r;
	int x;
	int y;
	int dx;
	int dy;
	int n;

	if (src == 0) {
		return;
	}
	if (*(int*) (e + 0x1c8) & 8) {
		return;
	}
	if (fcn_0042e410(100) < chance) {
		return;
	}
	x = *(unsigned char*) (src + 0x1c);
	y = *(unsigned char*) (src + 0x1d);
	for (it = fcn_005463a0(2, 0, 0x12, 3, *(int*) (*(char**) (e + 0x16c) + 1)); it != 0; it = fcn_005462a0()) {
		x += *(int*) (it + 0xb0);
		y += *(int*) (it + 0xb4);
	}
	h = *(char**) (e + 0x16c);
	r = &((Race*)g_868050)[*(unsigned char*) h];
	dy = r->cap_y - y;
	dx = r->cap_x - x;
	if (dx <= 0 && dy <= 0) {
		return;
	}
	if (*(int*) (e + 0x1b8) < 24000) {
		return;
	}
	memset(msg, 0, sizeof(msg));
	msg[4] = 0x12;
	*(int*) (msg + 8) = ((Ent*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].handle;
	*(int*) (msg + 0xc) = *(int*) (h + 1);
	*(int*) (msg + 0x28) = (*(int*)&g_7f4c00);
	*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x30) = g_7f4c08;
	*(short*) (msg + 0x34) = g_7f4c0c;
	msg[0x36] = 1;
	*(int*) (msg + 0x64) = 1;
	*(int*) (msg + 0x58) = *(int*) (src + 2);
	*(int*) (msg + 0x5c) = dx != 0;
	*(int*) (msg + 0x60) = dy != 0;
	n = *(int*) (msg + 0x5c) + *(int*) (msg + 0x60);
	fcn_004c4eb0(g_67e33c);
	fcn_004c5530(msg);
	fcn_004c5150(-1, ((Ent*)g_7f4ca0)[*(unsigned short*) (*(char**) (e + 0x16c) + 0x27)].handle, (*(char*)&g_773d75), 0x1f40);
	switch (fcn_0051e070()) {
	case 0:
		if (n == 1) {
			fcn_0051af00(buf, 0x1bbc, *(unsigned short*) e, *(char**) (e + 0x16c));
		}
		else {
			fcn_0051af00(buf, 0x1bbd, *(unsigned short*) e, *(char**) (e + 0x16c), n);
		}
		break;
	case 1:
		if (n == 1) {
			fcn_0051af00(buf, 0x1bbc, *(unsigned short*) e, *(char**) (e + 0x16c));
		}
		else {
			fcn_0051af00(buf, 0x1bbd, *(unsigned short*) e, *(char**) (e + 0x16c), n);
		}
		break;
	}
	h = *(char**) (e + 0x16c);
	fcn_00545e80(((Ent*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].handle, ((Ent*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].handle, buf, 0, 0x60b, *(int*) (h + 1), -1, 0, 0);
	*(int*) (e + 0x1b8) -= n * 8000;
	fcn_004c4ef0(g_67e33c);
	*(int*) (e + 0x1c8) |= 8;
}
