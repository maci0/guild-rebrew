

typedef struct DD_LINE_VB DD_LINE_VB;
// SIZE 0x4
struct DD_LINE_VB {
	int (__stdcall** vt)(DD_LINE_VB*, int, int, void*, int);
};

extern int g_6777ac;
extern void* g_6b5df4;
extern char g_6b5df0[];
#include "Develop/Units/Error/error_message.h"

/* ADDRESS: GOLDDE 0x00419250 */
void __cdecl dd_BeginLines(void)
{
	if (g_6777ac != -1) {
		ReportClientMessage("Missing dd_EndLines!");
	}
	g_6777ac = 0;
	((DD_LINE_VB*)g_6b5df4)->vt[0x2c / 4](((DD_LINE_VB*)g_6b5df4), 0, 0, g_6b5df0, 0x2000);
}
