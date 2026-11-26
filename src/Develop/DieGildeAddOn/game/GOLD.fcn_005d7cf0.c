

#include "Develop/Units/d2.v1/gold_window.h"







// SIZE 0x3c4

extern short g_fb9070;
extern short g_fb9072;
extern char s_67d67c[];
#include "client_types.h"
extern char* g_77255c;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_14cf950;
#include "client_dialog_state.h"
extern float g_6a24e4;

unsigned char* __cdecl fcn_004730c0(int, int, int, int, char*, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00473150(unsigned char*);
void __cdecl d2_ClearScreen(void);
void __cdecl fcn_00469e30(int);
int __cdecl fcn_0046e940(int, int, int, int, int);
void __cdecl fcn_00471c80(int, int);
void __cdecl io_AppendText(int, ...);
void __cdecl fcn_0046f280(int);

void __cdecl d2_ShowCreditsScreen(void)
{
	unsigned char* fade;
	int speed;
	int win;
	int i;

	speed = 4;
	fade = fcn_004730c0(0, 0, g_fb9072, g_fb9070, s_67d67c, 0x3c, 1);
	while ((*fade & 4) == 0) {
		main_RunFrameLoop(0, 0x24087);
	}
	fcn_00473150(fade);
	fcn_004730c0(0, 0, g_fb9072, g_fb9070, s_67d67c, 0x3c, 10);
	d2_ClearScreen();
	fcn_00469e30(0x7ad);
	win = fcn_0046e940(100, 0, 0x258, g_fb9070, 0x10);
	fcn_00471c80(win, 1);
	io_AppendText(0x2004);
	(*(GOLD_GUI_WINDOW**)&g_77255c)->scroll = -g_fb9070;
	i = 0;
	d2_SuppressOverlay = 1;
	while (main_RunFrameLoop(d2_ShowCreditsScreen, 0x24087)) {
		if (g_14ce8e0 || g_14cf950) {
			g_774654 = 1;
		}
		(*(GOLD_GUI_WINDOW**)&g_77255c) = &g_f8f120[win];
		if (i % speed == 0) {
			(*(GOLD_GUI_WINDOW**)&g_77255c)->scroll++;
		}
		i++;
		if ((*(GOLD_GUI_WINDOW**)&g_77255c)->height * 1.5 + (*(GOLD_GUI_WINDOW**)&g_77255c)->scroll > (*(GOLD_GUI_WINDOW**)&g_77255c)->limit) {
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
	fade = fcn_004730c0(0, 0, g_fb9072, g_fb9070, s_67d67c, 0x3c, 1);
	while ((*fade & 4) == 0) {
		main_RunFrameLoop(0, 0x24087);
		(*(GOLD_GUI_WINDOW**)&g_77255c) = &g_f8f120[win];
		if (i % speed == 0) {
			(*(GOLD_GUI_WINDOW**)&g_77255c)->scroll++;
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
	fcn_004730c0(0, 0, g_fb9072, g_fb9070, s_67d67c, 0x3c, 10);
	d2_SuppressOverlay = 0;
}
