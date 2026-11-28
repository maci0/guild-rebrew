


#include <stdio.h>
#include <windows.h>

extern char g_6a3658[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_7747d4;

void __cdecl main_InitComMovieState(void);
int __cdecl OpenMovieWindow(char*, int, int, int, int, int, int, int);
void __cdecl PlayVideo(int);
void __cdecl main_PumpWindowMessages(void);

/* ADDRESS: GOLDDE 0x0052afe0 */
void __cdecl main_PlayIntroMovies(void)
{
	char path[0x104];

	Sleep(400);
	main_InitComMovieState();
	sprintf(path, "%sjowood.mpg", g_6a3658);
	g_7747d4 = OpenMovieWindow(path, 0, main_Instance, 10, 10, 0xdc, 0xdc, 0x8a);
	Sleep(100);
	PlayVideo(g_7747d4);
	Sleep(400);
	sprintf(path, "%s4head.mpg", g_6a3658);
	g_7747d4 = OpenMovieWindow(path, 0, main_Instance, 10, 10, 0xdc, 0xdc, 0x8a);
	main_PumpWindowMessages();
	Sleep(100);
	PlayVideo(g_7747d4);
	Sleep(400);
	sprintf(path, "%sintro.mpg", g_6a3658);
	g_7747d4 = OpenMovieWindow(path, 0, main_Instance, 10, 10, 0xdc, 0xdc, 0x8a);
	Sleep(100);
	PlayVideo(g_7747d4);
	sprintf(path, "%sintro_addon.mpg", g_6a3658);
	g_7747d4 = OpenMovieWindow(path, 0, main_Instance, 10, 10, 0xdc, 0xdc, 0x8a);
	Sleep(100);
	PlayVideo(g_7747d4);
	main_PumpWindowMessages();
}
