


#include <string.h>
#pragma intrinsic(memset)

// SIZE 0x21c
typedef struct {
	char f0[4];
	int f4;
	char pad[0x214];
} Slot5c0a;

extern char g_7f4ca0[];
extern unsigned short g_774970;
extern __int64 g_666018;
extern int g_66601c;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;
extern char g_6ac494[];

int __cdecl fcn_00525f60(void*, int);
void __cdecl fcn_0051af00(void*, int, ...);
unsigned short* __cdecl fcn_005cd440(int*, char*, int, int);
int __cdecl cm_ChkCutsceneReady(int, unsigned short);
void __cdecl fcn_00526120(char*, int);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_00470820(int, int, void*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c6ae0(int id, int k);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005c0a90(int arg)
{
	int h2;
	int h1;
	int msg[0x14];
	char buf[0x40];
	char text[0x200];
	unsigned short* a;
	unsigned short* b;
	int r;
	int d;
	int t;
	int v;

	if (fcn_00525f60(&((Slot5c0a*)g_7f4ca0)[g_774970], 2) == 0) {
		return;
	}
	if (arg == 0) {
		return;
	}
	memset(msg, 0, sizeof(msg));
	msg[1] = 0x400;
	msg[4] = 6;
	msg[2] = (*(int*)&g_666018);
	msg[3] = g_66601c;
	fcn_0051af00(buf, 0x175f);
	a = fcn_005cd440(msg, buf, 0, 0);
	if (a == 0) {
		return;
	}
	fcn_0051af00(buf, 0x1760, *a);
	b = fcn_005cd440(msg, buf, 0, 0);
	if (b == 0) {
		return;
	}
	r = cm_ChkCutsceneReady(*(int*) (a + 2), g_774970);
	if (r <= 0) {
		fcn_0051af00(text, 0x1756, *a);
		fcn_00526120(text, 0);
		fcn_00532ef0();
		return;
	}
	if (fcn_00525f60(&((Slot5c0a*)g_7f4ca0)[g_774970], 3) == 0) {
		fcn_00532ef0();
		return;
	}
	d = fcn_00470820(0, 0, g_6ac494);
	fcn_00471b60(d);
	fcn_00473a90(0, 0);
	fcn_004727a0(d, 1);
	t = fcn_00519190(0x1761, r, (r != 1) + 0x1752, *b, *a);
	h1 = fcn_00472250(d, 1, t);
	h2 = fcn_00472250(d, 1, t + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == h1) {
				char ev[0xf8];

				v = *(int*) (b + 2);
				*(int*) (ev + 8) = v;
				*(int*) (ev + 0xc) = v;
				*(int*) (ev + 0x5c) = ((Slot5c0a*)g_7f4ca0)[g_774970].f4;
				*(int*) (ev + 0x60) = v;
				*(int*) (ev + 0x58) = *(int*) (a + 2);
				ev[4] = 0x2f;
				ev[0x36] = 9;
				fcn_004c5530(ev);
				fcn_004c6ae0(((Slot5c0a*)g_7f4ca0)[g_774970].f4, -3);
				fcn_0051af00(text, 0x1762, *b);
				fcn_00526120(text, 0);
				g_774654 = 1;
			}
			else if (g_67d370 == h2) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005c0a90, 0x677c7) != 0);
	fcn_00471e30(d);
	fcn_00532ef0();
}
