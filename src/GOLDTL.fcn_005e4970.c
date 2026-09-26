// FUNCTION: GOLDTL 0x005e4970
// SIZE: 722

typedef struct Player {
	char pad0[0x10];
	int lines;
	char pad14[0x254 - 0x14];
	int limit;
	int scroll;
	char pad25c[0x3cc - 0x25c];
} Player;
// SIZE 0x3cc

extern int g_1040490;
extern int g_1040494;
extern char s_67d67c[];
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_77255c;
extern int g_7725c8;
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_774654;
extern float g_6a24e4;

unsigned char* __cdecl fcn_004730c0(int, int, int, int, char*, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00473150(unsigned char*);
void __cdecl fcn_0046b4f0(void);
void __cdecl fcn_00469e30(int);
int __cdecl fcn_0046e940(int, int, int, int, int);
void __cdecl fcn_00471c80(int, int);
void __cdecl fcn_00519190(int, ...);
void __cdecl fcn_0046f280(int);

void __cdecl fcn_005e4970(void)
{
	unsigned char* fade;
	int speed;
	int win;
	int i;

	speed = 4;
	fade = fcn_004730c0(0, 0, g_1040494, g_1040490, s_67d67c, 0x3c, 1);
	while ((*fade & 4) == 0) {
		fcn_005373e0(0, 0x24087);
	}
	fcn_00473150(fade);
	fcn_004730c0(0, 0, g_1040494, g_1040490, s_67d67c, 0x3c, 10);
	fcn_0046b4f0();
	fcn_00469e30(0x7ad);
	win = fcn_0046e940(100, 0, 0x258, g_1040490, 0x10);
	fcn_00471c80(win, 1);
	fcn_00519190(0x2004);
	(*(Player**)&g_77255c)->scroll = -g_1040490;
	i = 0;
	g_7725c8 = 1;
	while (fcn_005373e0(fcn_005e4970, 0x24087)) {
		if (g_14ce8e0 || g_14cf950) {
			g_774654 = 1;
		}
		(*(Player**)&g_77255c) = &((Player*)g_1015f40)[win];
		if (i % speed == 0) {
			(*(Player**)&g_77255c)->scroll++;
		}
		i++;
		if ((*(Player**)&g_77255c)->lines * 1.5 + (*(Player**)&g_77255c)->scroll > (*(Player**)&g_77255c)->limit) {
			g_774654 = 1;
		}
		if (g_6a24e4 >= 80.0f) {
			speed = 4;
		} else if (g_6a24e4 >= 30.0f) {
			speed = 2;
		} else if (g_6a24e4 < 30.0f) {
			speed = 1;
		}
	}
	fade = fcn_004730c0(0, 0, g_1040494, g_1040490, s_67d67c, 0x3c, 1);
	while ((*fade & 4) == 0) {
		fcn_005373e0(0, 0x24087);
		(*(Player**)&g_77255c) = &((Player*)g_1015f40)[win];
		if (i % speed == 0) {
			(*(Player**)&g_77255c)->scroll++;
		}
		if (g_6a24e4 >= 80.0f) {
			speed = 4;
		} else if (g_6a24e4 >= 30.0f) {
			speed = 2;
		} else if (g_6a24e4 < 30.0f) {
			speed = 1;
		}
		i++;
	}
	fcn_0046f280(win);
	fcn_00469e30(0x797);
	fcn_00473150(fade);
	fcn_004730c0(0, 0, g_1040494, g_1040490, s_67d67c, 0x3c, 10);
	g_7725c8 = 0;
}
