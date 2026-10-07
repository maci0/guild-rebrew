// FUNCTION: GOLDTL 0x0041d950

#include <stdio.h>
#include <windows.h>

extern int g_6b6f48;
extern unsigned int g_6b6f50;
extern char g_14cc600[];
extern HWND g_14ce600;
void __cdecl DispatchLogOutput(const char* text, int output_mask, int severity);

void __cdecl fcn_0041d950(char* module, unsigned int line, char* msg)
{
	if (g_6b6f48 == 0) {
		MessageBoxA(0, "ERROR-Handler has not been started...", "Error!", 0x10030);
		return;
	}
	if (g_6b6f50 == 0) {
		return;
	}
	if (g_6b6f50 & 0xf) {
		sprintf(g_14cc600, "ERROR (%s:%lu):\n%s\n", module, line, msg);
	}
	if (g_6b6f50 & 0xd) {
		DispatchLogOutput(g_14cc600, g_6b6f50, 1);
	}
	if (g_6b6f50 & 2) {
		MessageBoxA(g_14ce600, g_14cc600, "Error!", 0x10030);
	}
}
