#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/game_data.h"

void* __cdecl he_StartHandlungSearch(int a1, int a2, int a3, int a4, int a5);
void* __cdecl he_fn_Handlung(void);
void __cdecl he_FreeAction(char* obj);
void __cdecl gm_AddTime(void* clock, int arg2, int arg3, int arg4);

/* ADDRESS: GOLDTL 0x00551c20 */
void __cdecl he_AllocTalentBoost(char* obj)
{
	char* otherAction;
	unsigned int idx;
	unsigned char type;
	unsigned char shade;
	unsigned char tilt;
	int t;

	idx = *(unsigned short*) (obj + 8);
	type = *(unsigned char*) (obj + 0xae);
	shade = *(unsigned char*) (type + idx * 0x21c + 0x7f4d20);
	if (*(float*) 0x66413c <= (float) shade) {
		he_FreeAction(obj);
		return;
	}
	{
		otherAction = (char*) he_StartHandlungSearch(2, 2, idx, 0, 0x60);
		while (otherAction != 0) {
			if (otherAction != obj) {
				he_FreeAction(obj);
				return;
			}
			otherAction = (char*) he_fn_Handlung();
		}
		idx = *(unsigned short*) (obj + 8);
		type = *(unsigned char*) (obj + 0xae);
		shade = *(unsigned char*) (type + idx * 0x21c + 0x7f4d20);
		t = (int) ((float) shade * *(float*) 0x664168 + *(float*) 0x6628a0);
		tilt = (unsigned char) t;
		tilt = (unsigned char) (tilt + 2);
		tilt = (unsigned char) (tilt * 2);
		*(unsigned char*) (obj + 0xac) = 0x15;
		*(int*) (obj + 0x70) = 0;
		*(unsigned char*) (obj + 0xad) = tilt;
		*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
		if (g_774800 != 0) {
			gm_AddTime(obj + 0x52, 0, 0, 1);
		} else {
			gm_AddTime(obj + 0x52, 5, 0, 0);
		}
		*(pos14_7f4c00*) (obj + 0x44) = gm_GameTime;
	}
}
