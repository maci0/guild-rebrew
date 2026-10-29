


#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>

extern int g_6b6f48;
extern unsigned int g_6b6f50;
extern char g_14cc600[];
void __cdecl DispatchLogOutput(const char* text, int output_mask, int severity);

void __cdecl fcn_0041da60(char* module, unsigned int line, char* msg, int severity)
{
	unsigned char flags;

	if (g_6b6f48 == 0) {
		MessageBoxA(0, "ERROR-Handler has not been started...", "Error!", 0x10030);
		return;
	}
	flags = (unsigned char) g_6b6f50;
	if (flags & 1) {
		if (flags & 0x20) {
			sprintf(g_14cc600, "Time:%8lu\tModule '%s':\tLine:%lu:\t%s", timeGetTime(), module, line, msg);
		} else {
			sprintf(g_14cc600, "tModule '%s':\tLine:%lu:\t%s", module, line, msg);
		}
		DispatchLogOutput(g_14cc600, g_6b6f50, severity);
	}
}
