#include <string.h>

#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl nt_CloseClientConnection(void);
unsigned short __cdecl fcn_004c3a50(char* n);

/* ADDRESS: GOLDTL 0x004c49f0 */
int __cdecl fcn_004c49f0(char* src)
{
	char* p;
	char* q;
	char** pn;

	p = g_aed200;
	if (p == 0) {
		if (g_14cbca0 != -1) {
			nt_CloseClientConnection();
		}
		return 1;
	}
	pn = (char**) (g_aed200 + 0x95);
	g_aed200 = *pn;
	memcpy(p, src, 0x99);
	*(unsigned short*) (p + 1) = fcn_004c3a50(p);
	q = cm_CommandQueueHead;
	if (q != 0) {
		while (*(char**) (q + 0x95) != 0) {
			q = *(char**) (q + 0x95);
		}
		*(char**) (p + 0x91) = q;
		*pn = 0;
		*(char**) (q + 0x95) = p;
	} else {
		*(char**) (p + 0x91) = 0;
		*pn = 0;
		cm_CommandQueueHead = p;
	}
	return 0;
}
