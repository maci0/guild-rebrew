// FUNCTION: GOLDTL 0x00544750
// SIZE: 390

#include <stdio.h>
#include <windows.h>

extern char g_6a3658[];
extern int g_7e1f80;
extern int g_7747d4;

void __cdecl fcn_0041e620(void);
int __cdecl fcn_0041e680(char*, int, int, int, int, int, int, int);
void __cdecl fcn_0041f350(int);
void __cdecl fcn_005356e0(void);

void __cdecl fcn_00544750(void)
{
	char path[0x104];

	Sleep(400);
	fcn_0041e620();
	sprintf(path, "%sjowood.mpg", g_6a3658);
	g_7747d4 = fcn_0041e680(path, 0, g_7e1f80, 10, 10, 0xdc, 0xdc, 0x8a);
	Sleep(100);
	fcn_0041f350(g_7747d4);
	Sleep(400);
	sprintf(path, "%s4head.mpg", g_6a3658);
	g_7747d4 = fcn_0041e680(path, 0, g_7e1f80, 10, 10, 0xdc, 0xdc, 0x8a);
	fcn_005356e0();
	Sleep(100);
	fcn_0041f350(g_7747d4);
	Sleep(400);
	sprintf(path, "%sintro.mpg", g_6a3658);
	g_7747d4 = fcn_0041e680(path, 0, g_7e1f80, 10, 10, 0xdc, 0xdc, 0x8a);
	Sleep(100);
	fcn_0041f350(g_7747d4);
	sprintf(path, "%sintro_addon.mpg", g_6a3658);
	g_7747d4 = fcn_0041e680(path, 0, g_7e1f80, 10, 10, 0xdc, 0xdc, 0x8a);
	Sleep(100);
	fcn_0041f350(g_7747d4);
	fcn_005356e0();
}
