#include <string.h>
#include "Develop/DieGildeAddOn/game/client_actions.h"
#include "Develop/DieGildeAddOn/game/client_data.h"

int __cdecl atoi(const char*);
void __cdecl cm_SendCopyEntityData(void*);

/* ADDRESS: GOLDTL 0x004b1d10 */
/* ADDRESS: GOLDDE 0x004a0030 */
int __cdecl gm_ParsePlagueCommand(int a1, int a2, char* s)
{
	char buf[0xf8];
	int v;
	int w;

	if (*s != '-') {
		return 0;
	}
	v = atoi(s + 1);
	if (v <= 10) {
		if (v <= 1) {
			v = 1;
		}
	} else {
		v = 10;
	}
	memset(buf, 0, 0xf8);
	w = *(int*) (gm_CityEntity + 4);
	*(char*) (buf + 4) = 0x59;
	*(int*) (buf + 0x58) = v;
	*(int*) (buf + 0x2c) = gm_GameTimeHour;
	*(int*) (buf + 8) = w;
	*(int*) (buf + 0x28) = gm_GameTime.a;
	*(int*) (buf + 0x0c) = -1;
	*(unsigned char*) (buf + 0x36) = 2;
	*(int*) (buf + 0x30) = gm_GameTimeSliceDword;
	*(unsigned short*) (buf + 0x34) = (unsigned short) gm_GameTimeTailWord;
	*(unsigned short*) (buf + 0x2c) = 0xb;
	cm_SendCopyEntityData(buf);
	return 1;
}
