
// SIZE 0xc98
typedef struct {
	char used;
	char pad1[0xff];
	int owner;
	char pad2[0x20];
	unsigned char flags;
	char pad3[0xc98 - 0x125];
} EVT_SCRIPT_SLOT;

#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl evt_CountActiveScripts(void)
{
	int n;
	int i;
	EVT_SCRIPT_SLOT* e;

	n = 0;
	e = ((EVT_SCRIPT_SLOT*)g_6b7e94);
	for (i = 0; i < 0x80; i++) {
		if ((e[i].used != 0 && e[i].owner != -1) || (e[i].flags & 1)) {
			n++;
		}
	}
	return n;
}
