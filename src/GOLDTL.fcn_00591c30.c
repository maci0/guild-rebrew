#include <string.h>
#pragma intrinsic(memset)

/* ADDRESS: GOLDTL 0x00591c30 */

void __cdecl fcn_00591c30(char* p)
{
	*(int*) (p + 4) = -1;
	*(int*) (p + 8) = -1;
}

typedef struct {
	char c;
	char pad[3];
	int a;
	int b;
} Ent591c;
// SIZE 0xc

#include "client_types.h"
extern Slot_779d00 g_779d00[];

/* ADDRESS: GOLD 0x005896e0 */
/* ADDRESS: GOLDTL 0x00591c40 */

void __cdecl fcn_00591c40(void)
{
	int i;

	memset(((Ent591c*)g_779d00), 0, sizeof(Ent591c[11]));
	for (i = 0; i < 11; i++) {
		((Ent591c*)g_779d00)[i].c = (char) (i + 0x3b);
		if (i == 10) {
			((Ent591c*)g_779d00)[10].c = 0x57;
		}
		fcn_00591c30((char*) &((Ent591c*)g_779d00)[i]);
	}
}
