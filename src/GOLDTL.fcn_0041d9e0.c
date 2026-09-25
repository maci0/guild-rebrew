// FUNCTION: GOLDTL 0x0041d9e0
// SIZE: 128

#include <stdio.h>
#include <windows.h>

extern int g_6b6f48;
extern unsigned int g_6b6f50;
extern char g_14cc600[];
void __cdecl DispatchLogOutput(const char* text, int output_mask, int severity);

void __cdecl fcn_0041d9e0(char* msg)
{
	if (g_6b6f48 == 0) {
		MessageBoxA(0, "ERROR-Handler has not been started...", "Error!", 0x10030);
		return;
	}
	if (g_6b6f50 == 0) {
		return;
	}
	if (g_6b6f50 & 0xd) {
		sprintf(g_14cc600, "MESSAGE: %s\n", msg);
		DispatchLogOutput(g_14cc600, g_6b6f50, 1);
	}
	if (g_6b6f50 & 2) {
		MessageBoxA(0, msg, "Message:", 0x1030);
	}
}
