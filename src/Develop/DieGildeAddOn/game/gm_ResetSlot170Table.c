


#include <string.h>

typedef struct
{
	int id;
	int flags;
	float s[3];
	char pad[0x15c];
} Slot170;
// SIZE 0x170

typedef struct
{
	char b[14];
} Blob14;
// SIZE 0xe

#include "client_types.h"
extern Slot170_7731b8 g_7731b8[8];
extern pos14_7f4c00 g_772fe8;
extern pos14_7f4c00 gm_GameTime;
extern int g_9a9200[8];

void __cdecl gm_ResetSlot170Table(void)
{
	int i;

	memset(((Slot170*)g_7731b8), 0, sizeof(Slot170[8]));
	for (i = 0; i < 8; i++) {
		((Slot170*)g_7731b8)[i].id = -1;
		((Slot170*)g_7731b8)[i].s[0] = 1.0f;
		((Slot170*)g_7731b8)[i].s[1] = 1.0f;
		((Slot170*)g_7731b8)[i].s[2] = 1.0f;
	}
	g_772fe8 = gm_GameTime;
	memset(g_9a9200, 0, sizeof(g_9a9200));
	g_9a9200[0] = -1;
}
