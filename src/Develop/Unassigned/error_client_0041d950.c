#include <stdio.h>
#include <windows.h>

extern int g_6b6f48;
extern unsigned int g_6b6f50;
extern char g_14cc600[];
extern HWND g_14ce600;
void __cdecl DispatchLogOutput(const char* text, int output_mask, int severity);
#include "Develop/Units/Error/error_message.h"

void __cdecl DispatchLogOutput(const char* text, int output_mask, int severity);
#include <mmsystem.h>

void __cdecl DispatchLogOutput(const char* text, int output_mask, int severity);

/* ADDRESS: GOLDTL 0x0041d950 */
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

/* ADDRESS: GOLDTL 0x0041d9e0 */
/* ADDRESS: GOLD 0x004222b0 */
void __cdecl ReportClientMessage(const char* msg)
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

/* ADDRESS: GOLD 0x00422330 */
/* ADDRESS: GOLDTL 0x0041da60 */
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
