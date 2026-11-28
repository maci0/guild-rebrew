#include "Develop/client_types.h"

extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

void __cdecl gm_AddTime(void* clock, int arg2, int arg3, int arg4);
int __cdecl gm_RandomMod(int range);
int __cdecl cm_SendSetHE(char a1, unsigned char* e);

/* ADDRESS: GOLDTL 0x00549b90 */
void __cdecl he_StartElectionCampaign(char* p)
{
	if (*(unsigned char*) (p + 0x78) & 4) {
		return;
	}
	*(pos14_7f4c00*) (p + 0x52) = gm_GameTime;
	gm_AddTime(p + 0x52, 1, 0, 0);
	*(pos14_7f4c00*) (p + 0xb0) = gm_GameTime;
	gm_AddTime(p + 0xb0, 0x18, 0, 0);
	*(int*) (p + 0xb6) = 0;
	*(short*) (p + 0xb4) = (short) (gm_RandomMod(4) + 0x13);
	*(int*) (p + 0xc0) = 1;
	*(int*) (p + 0x84) = cm_SendSetHE(0, (unsigned char*) p);
}
