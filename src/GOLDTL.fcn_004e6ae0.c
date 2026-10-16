/* ADDRESS: GOLDTL 0x00699368 */
extern int g_699368;
/* ADDRESS: GOLD 0x0061a638 */
extern int g_699368;



#include <string.h>

#pragma intrinsic(memcpy, memset)

char* __cdecl fcn_004e6ab0(void);

#include "client_packet_queue.h"

char* __cdecl fcn_004e6ae0(void* src)
{
	char* p;

	p = fcn_004e6ab0();
	if (p != 0) {
		memcpy(p, src, 0x114);
		*(int*) p = g_699368;
		if (*(char*) (p + 0x31) == 0) {
			*(char*) (p + 0x31) = 8;
		}
	}
	return p;
}
