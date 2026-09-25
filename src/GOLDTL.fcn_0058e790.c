// FUNCTION: GOLDTL 0x0058e790
// SIZE: 717

#include <string.h>
#pragma intrinsic(memset)

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x214];
};

extern struct house g_7f4ca0[];
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_6a96d8[];
extern char g_6a9828[];
extern char g_6a9814[];
extern float g_6628d8;
extern float g_6628a0;
extern float g_6628bc;

int __cdecl fcn_004c2db0(int, int);
char* __cdecl fcn_0058e220(char*, char*);
float __cdecl fcn_004f4770(char*);
float __cdecl gm_RandomFloat01(void);
int __cdecl fcn_0050dac0(unsigned short id);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_005782f0(struct house*, int);
int __cdecl fcn_00519190();
unsigned short __cdecl fcn_0042e410(int);
int __cdecl fcn_004c30a0(int, int, char*, int, int);
void __cdecl fcn_004c5150(int, int, unsigned char, int);
void __cdecl fcn_004c5530(char* msg);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00428720(char*);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void __cdecl fcn_0058e790(char* e, char* res)
{
	float f;
	int t;
	char* m;
	int mode;
	int amt;
	int h;

	amt = 0;
	mode = 0;
	t = fcn_004c2db0(*(int*) (res + 0x14), *(int*) (res + 0x4c));
	m = fcn_0058e220(e, res);
	f = fcn_004f4770(e);
	if (gm_RandomFloat01() + f - g_6628d8 < g_6628a0) {
		mode = 2;
	}
	else {
		char ev[0xf8];

		amt = MIN(MAX((int) (fcn_0050dac0(g_774970) * g_6628bc), 0x27100), 0xc3500);
		fcn_004c5150(g_7f4ca0[g_774970].handle, -1, g_773d75, amt);
		memset(ev, 0, sizeof(ev));
		ev[4] = (char) 0x8e;
		*(int*) (ev + 8) = g_7f4ca0[g_774970].handle;
		*(int*) (ev + 0xc) = *(int*) (e + 1);
		*(int*) (ev + 0x28) = g_7f4c00;
		*(int*) (ev + 0x2c) = g_7f4c04;
		*(int*) (ev + 0x30) = g_7f4c08;
		*(short*) (ev + 0x34) = g_7f4c0c;
		ev[0x36] = 1;
		*(int*) (ev + 0x58) = amt;
		fcn_004c5530(ev);
		fcn_005782f0(&g_7f4ca0[g_774970], 3);
	}
	h = fcn_00470820(0, 0, g_6a96d8);
	fcn_00473a90(0, 0);
	fcn_00471b60(h);
	fcn_004727a0(h, 0);
	fcn_005340f0(g_772514);
	g_100f1dc = -1;
	fcn_004727a0(h, 1);
	if (mode == 0) {
		fcn_004c30a0(t, 0, g_6a9828, fcn_0042e410(8), 0xfa);
		fcn_00519190(0x40f1, 0x40cc, amt);
	}
	else {
		char ev[0xf8];

		fcn_004c30a0(t, 0, g_6a9814, fcn_0042e410(8), 0xfa);
		fcn_00519190(0x40d3, 0x40cc);
	}
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_0058e790, 0x777c7) != 0);
	fcn_00471e30(h);
	if (m != 0) {
		fcn_00428720(m);
	}
}
