void __cdecl main_SampleFrameCounter(void);
extern char g_7e2760[];
extern char g_9ba1c0[];


#include <string.h>

#include "client_timer.h"

void __cdecl fcn_00525eb0(void)
{
	tb_OpenFunction(main_SampleFrameCounter, 0x47);
	memset(g_7e2760, 0, 0x300);
	memset(g_9ba1c0, 0, 0x100);
}
