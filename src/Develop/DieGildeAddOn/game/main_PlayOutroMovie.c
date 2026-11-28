extern char g_6b5c90[];
extern char g_67d67c[];
extern char g_6a3658[];
#include <stdio.h>

int __cdecl fcn_0041e620(void);
void __cdecl ShutdownVideo(void);
void __cdecl fcn_004c2d90(float, int);
unsigned char* __cdecl d2_StartScreenFade(int, int, int, int, char*, int, int);
void __cdecl main_RunFrameLoop(int, int);
void __cdecl main_PumpWindowMessages(void);
void __cdecl io_PollKeyboardInput(void);
void __cdecl io_AcquireKeyboard(int);
void __cdecl io_AcquireMouse(int);
int __cdecl OpenMovieWindow(char*, void*, void*, int, int, int, int, int);
int __cdecl PlayVideo(int);
void __cdecl d2_ReleaseOverlaySprite(unsigned char*);


__declspec(dllimport) void __stdcall Sleep(unsigned long);
extern void (__stdcall* g_662264)(int);
extern int g_7747d4, main_LoopFlags, g_1040494, d2_ScreenHeight, main_Instance;
typedef void* HWND;
extern HWND g_774940;
extern float msx_MasterFadeTarget;
extern unsigned char d3snd_AmbientEnabled;
extern char io_LastKeyScancode;

/* ADDRESS: GOLDTL 0x005448e0 */
/* ADDRESS: GOLDDE 0x0052b170 */
void __cdecl main_PlayOutroMovie(void)
{
	char buf[0x104];
	unsigned char* h;
	char* b;
	int saved;
	float vol;

	if (*(int*) ((int) &g_7747d4 + 0x158) == 0) {
		fcn_0041e620();
	}
	fcn_004c2d90(0.0f, 0x3e8);
	h = d2_StartScreenFade(0, 0, g_1040494, d2_ScreenHeight, (char*) &g_67d67c, 0x5a, 1);
	for (;;) {
		if ((*h & 4) && !(msx_MasterFadeTarget >= 0.0f)) {
			break;
		}
		main_RunFrameLoop(0, main_LoopFlags);
	}
	b = buf;
	saved = d3snd_AmbientEnabled;
	d3snd_AmbientEnabled = 0;
	sprintf(b, "%soutro.mpg", (char*) &g_6a3658);
	*(int*) &g_6b5c90 = 1;
	io_PollKeyboardInput();
	*(int*) &g_6b5c90 = 0;
	io_AcquireKeyboard(0);
	io_AcquireMouse(0);
	main_PumpWindowMessages();
	Sleep(0x1f4);
	g_7747d4 = OpenMovieWindow(b, 0, (void*) main_Instance, 0, 0, 0, 0, 0x8a);
	Sleep(0xc8);
	PlayVideo(g_7747d4);
	d2_ReleaseOverlaySprite(h);
	main_PumpWindowMessages();
	g_662264((int) g_774940);
	io_AcquireKeyboard(1);
	io_AcquireMouse(1);
	*(int*) &g_6b5c90 = 1;
	io_PollKeyboardInput();
	vol = (float) *(unsigned char*) ((int) &g_774940 + 0x1d62);
	*(int*) &g_6b5c90 = 0;
	io_LastKeyScancode = 0;
	fcn_004c2d90(vol * (1.0f / 127.0f), 0x3e8);
	if (*(int*) ((int) &g_7747d4 + 0x158) == 0) {
		d3snd_AmbientEnabled = (unsigned char) saved;
		ShutdownVideo();
	} else {
		d3snd_AmbientEnabled = (unsigned char) saved;
	}
}
