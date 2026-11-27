#include "Develop/DieGildeAddOn/game/game_data.h"


/* Twin of GOLDTL 0x514e80; GOLD keeps the flag byte at 0x212 and uses bits 2/3, not 0/1. */

#include <string.h>

char __cdecl d3_MarkGebaeudeGateFlagsCb(char* sceneObj)
{
	unsigned char* proto;

	if (strncmp(sceneObj, "gb_", 3) == 0) {
		proto = 0;
		if (sceneObj[0x4b] == 2) {
			proto = g_7e3f30 + (*(int*) (sceneObj + 0x48) & 0xffffff) * 0x24d;
		}
		if (proto == 0) {
			if (strstr(sceneObj, "_TOR_") == 0) {
				sceneObj[0x212] = (sceneObj[0x212] & 0xf7) | 4;
				return 1;
			}
		} else if (*proto != 0x1f) {
			sceneObj[0x212] = (sceneObj[0x212] & 0xf7) | 4;
			return 1;
		} else {
			sceneObj[0x212] |= 0xc;
		}
	}
	return 1;
}
