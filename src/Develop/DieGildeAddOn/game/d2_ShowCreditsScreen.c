#include "Develop/Units/d2.v1/gold_window.h"
#include "Develop/Units/d2.v1/d2_win.h"
#include "client_types.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

extern char s_67d67c[];
extern char* g_77255c;
extern char g_14cf950;
extern float g_6a24e4;

unsigned char* __cdecl d2_StartScreenFade(int, int, int, int, char*, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_ReleaseOverlaySprite(unsigned char*);
void __cdecl d2_ClearScreen(void);
void __cdecl d2_SetBackdropResource(int);
int __cdecl d2_CreateWindow(int, int, int, int, int);
void __cdecl d2_CenterWindow(int, unsigned char);
void __cdecl io_AppendText(int, ...);
void __cdecl d2_CloseWindow(int);

#if defined(REBREW_GOLD)

extern short g_fb9070;
extern short g_fb9072;

/* ADDRESS: GOLD 0x005d7cf0 */
void __cdecl d2_ShowCreditsScreen(void)
{
	unsigned char* fade;
	int speed;
	int win;
	int i;

	speed = 4;
	fade = d2_StartScreenFade(0, 0, g_fb9072, g_fb9070, s_67d67c, 0x3c, 1);
	while ((*fade & 4) == 0) {
		main_RunFrameLoop(0, 0x24087);
	}
	d2_ReleaseOverlaySprite(fade);
	d2_StartScreenFade(0, 0, g_fb9072, g_fb9070, s_67d67c, 0x3c, 10);
	d2_ClearScreen();
	d2_SetBackdropResource(0x7ad);
	win = d2_CreateWindow(100, 0, 0x258, g_fb9070, 0x10);
	d2_CenterWindow(win, 1);
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
	fade = d2_StartScreenFade(0, 0, g_fb9072, g_fb9070, s_67d67c, 0x3c, 1);
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
	d2_CloseWindow(win);
	d2_SetBackdropResource(0x797);
	d2_ReleaseOverlaySprite(fade);
	d2_StartScreenFade(0, 0, g_fb9072, g_fb9070, s_67d67c, 0x3c, 10);
	d2_SuppressOverlay = 0;
}

#else

extern int d2_ScreenHeight;
extern int g_1040494;
extern Win_1015f40 g_1015f40[0x60];

/* ADDRESS: GOLDTL 0x005e4970 */
void __cdecl d2_ShowCreditsScreen(void)
{
	unsigned char* fade;
	int speed;
	int win;
	int i;

	speed = 4;
	fade = d2_StartScreenFade(0, 0, g_1040494, d2_ScreenHeight, s_67d67c, 0x3c, 1);
	while ((*fade & 4) == 0) {
		main_RunFrameLoop(0, 0x24087);
	}
	d2_ReleaseOverlaySprite(fade);
	d2_StartScreenFade(0, 0, g_1040494, d2_ScreenHeight, s_67d67c, 0x3c, 10);
	d2_ClearScreen();
	d2_SetBackdropResource(0x7ad);
	win = d2_CreateWindow(100, 0, 0x258, d2_ScreenHeight, 0x10);
	d2_CenterWindow(win, 1);
	io_AppendText(0x2004);
	*(int*) &(*(D2_WIN**)&g_77255c)->pad3c[0x21c] = -d2_ScreenHeight;
	i = 0;
	d2_SuppressOverlay = 1;
	while (main_RunFrameLoop(d2_ShowCreditsScreen, 0x24087)) {
		if (g_14ce8e0 || g_14cf950) {
			g_774654 = 1;
		}
		(*(D2_WIN**)&g_77255c) = &((D2_WIN*)g_1015f40)[win];
		if (i % speed == 0) {
			(*(int*) &(*(D2_WIN**)&g_77255c)->pad3c[0x21c])++;
		}
		i++;
		if ((*(D2_WIN**)&g_77255c)->height * 1.5
		    + *(int*) &(*(D2_WIN**)&g_77255c)->pad3c[0x21c] > *(int*) &(*(D2_WIN**)&g_77255c)->pad3c[0x218]) {
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
	fade = d2_StartScreenFade(0, 0, g_1040494, d2_ScreenHeight, s_67d67c, 0x3c, 1);
	while ((*fade & 4) == 0) {
		main_RunFrameLoop(0, 0x24087);
		(*(D2_WIN**)&g_77255c) = &((D2_WIN*)g_1015f40)[win];
		if (i % speed == 0) {
			(*(int*) &(*(D2_WIN**)&g_77255c)->pad3c[0x21c])++;
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
	d2_CloseWindow(win);
	d2_SetBackdropResource(0x797);
	d2_ReleaseOverlaySprite(fade);
	d2_StartScreenFade(0, 0, g_1040494, d2_ScreenHeight, s_67d67c, 0x3c, 10);
	d2_SuppressOverlay = 0;
}

#endif
