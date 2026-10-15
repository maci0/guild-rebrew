#include "Develop/DieGildeAddOn/game/event_callbacks.h"
/* ADDRESS: GOLD 0x004e5730 */
/* ADDRESS: GOLDTL 0x004e7160 */

void __cdecl fcn_004e7160(int idx, EVENT_RUN a2, void* a3, void* a4, EVENT_CHECK a5, unsigned char a6)
{
	int o;

	o = idx * 20;
	*(EVENT_RUN*) (g_9b0840 + o) = a2;
	*(void**) (g_9b0840 + 4 + o) = a3;
	*(void**) (g_9b0840 + 8 + o) = a4;
	*(EVENT_CHECK*) (g_9b0840 + 0x10 + o) = a5;
	*(unsigned char*) (g_9b0840 + 0xc + o) = a6;
}
