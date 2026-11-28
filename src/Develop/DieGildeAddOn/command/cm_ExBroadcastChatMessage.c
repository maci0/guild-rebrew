


#include <string.h>

extern char g_7e3a60[];
extern char g_68b300[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_EntityIdField[];
extern volatile int gm_GameTicks;
extern int d2_QuickChatLastTick;

/* ADDRESS: GOLDDE 0x004b9f30 */
int __cdecl cm_ExBroadcastChatMessage(char* cmd, char* result)
{
	char* p;
	int n;
	int found;
	int i;

	n = 0;
	found = 0;
	p = strstr(g_7e3a60, g_68b300);
	if (p != 0) {
		while (p != 0) {
			n++;
			p = strstr(p + 2, g_68b300);
		}
		if (n > 5)
			g_7e3a60[0] = 0;
	}
	for (i = 0; i < 8; i++) {
		if (*(int*) (cmd + 0x10 + i * 4) == *(int*) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c)) {
			found = 1;
			break;
		}
	}
	if (result != 0 || found != 0) {
		strcat(g_7e3a60, cmd + 0x30);
		d2_QuickChatLastTick = gm_GameTicks;
		if (result != 0) {
			result[0] = 1;
			result[1] = 0;
			*(int*) (result + 6) = 0;
		}
	}
	return 0;
}
