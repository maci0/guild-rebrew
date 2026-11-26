#include "client_data.h"
extern int __cdecl fcn_00500e20(char*); extern void __cdecl fcn_004c30a0(int, int, char*, int, int);
extern void __cdecl he_FreeAction(char*);
extern void __cdecl gm_AddTime(char*, int, int, int);
extern unsigned short __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/game_data.h"

/* Night-watchman clock action: starts the evening/morning announce sequence
 * when the game time enters the action's window. */
/* ADDRESS: GOLDTL 0x0056e980 */
void __cdecl he_RunNightWatchmanAnnouncements(char* action)
{
	int idx;
	int w;


	if (*(int*) &gm_GameTime != *(int*) (action + 0x44)) {
		he_FreeAction(action);
		return;
	}
	idx = fcn_00500e20((char*) &gm_GameTime);
	switch (*(int*) (action + 0x70)) {
	case 0:
		w = *(int*) &g_7f4c04 & 0xffff;

		if (!((float) w >= *(float*) (idx * 4 + 0x696540)) || !((float) w < *(float*) (idx * 4 + 0x696540) + 1.0f)) {
			*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
			goto sync_time;
		}
		if (*(char*) &g_774964)
			fcn_004c30a0(-7, 0, (char*) 0x6a6d50, -1, 0xfa);
		if (*(char*) 0x7766b9 != 0 && *(char*) &g_774964 != 0 &&
		    (gm_RandomMod(10) & 0xffff) > 7 && *(char*) &g_774964 != 0) {
			fcn_004c30a0(*(int*) (action + 0xac), 0, (char*) 0x6a6d30, -1, 0xfa);
			if (*(float*) (idx * 4 + 0x696540) == 7.0f) {
				fcn_004c30a0(*(int*) (action + 0xac), 0, (char*) 0x6a6d10, -1, 0xfa);
			} else if (*(float*) (idx * 4 + 0x696540) == 8.0f) {
				if (idx == 2)
					fcn_004c30a0(*(int*) (action + 0xac), 0, (char*) 0x6a6cec, -1, 0xfa);
				else
					fcn_004c30a0(*(int*) (action + 0xac), 0, (char*) 0x6a6ccc, -1, 0xfa);
			} else if (*(float*) (idx * 4 + 0x696540) == 9.0f) {
				fcn_004c30a0(*(int*) (action + 0xac), 0, (char*) 0x6a6cac, -1, 0x3e8);
			}
			if ((gm_RandomMod(10) & 0xffff) > 7)
				fcn_004c30a0(*(int*) (action + 0xac), 0, (char*) 0x6a6c8c, -1, 0x3e8);
		}
		*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
		*(unsigned short*) (action + 0x56) = (unsigned short) (int) *(float*) (idx * 4 + 0x696550);
		*(int*) (action + 0x58) = 0;
		*(int*) (action + 0x70) += 1;
		return;
	case 1:
		w = *(int*) &g_7f4c04 & 0xffff;

		if (!((float) w >= *(float*) (idx * 4 + 0x696550)) || !((float) w < *(float*) (idx * 4 + 0x696550) + 1.0f)) {
			*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
			goto sync_time;
		}
		if (*(char*) &g_774964)
			fcn_004c30a0(-7, 0, (char*) 0x6a6d50, -1, 0xfa);
		if (*(char*) 0x7766b9 != 0 && *(char*) &g_774964 != 0 &&
		    (gm_RandomMod(10) & 0xffff) > 7 && *(char*) &g_774964 != 0) {
			fcn_004c30a0(*(int*) (action + 0xac), 0, (char*) 0x6a6d30, -1, 0xfa);
			if (*(float*) (idx * 4 + 0x696550) == 19.0f) {
				fcn_004c30a0(*(int*) (action + 0xac), 0, (char*) 0x6a6c6c, -1, 0xfa);
			} else if (*(float*) (idx * 4 + 0x696550) == 20.0f) {
				if (idx == 2)
					fcn_004c30a0(*(int*) (action + 0xac), 0, (char*) 0x6a6c48, -1, 0xfa);
				else
					fcn_004c30a0(*(int*) (action + 0xac), 0, (char*) 0x6a6c28, -1, 0xfa);
			} else if (*(float*) (idx * 4 + 0x696550) == 21.0f) {
				fcn_004c30a0(*(int*) (action + 0xac), 0, (char*) 0x6a6c08, -1, 0xfa);
			}
			if ((gm_RandomMod(10) & 0xffff) > 7)
				fcn_004c30a0(*(int*) (action + 0xac), 0, (char*) 0x6a6be8, -1, 0x3e8);
		}
		*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
		*(unsigned short*) (action + 0x56) = 0x16;
		*(int*) (action + 0x58) = 0x1e;
		*(int*) (action + 0x70) += 1;
		return;
	case 2:
		if (*(unsigned short*) &g_7f4c04 < 0x16 || *(int*) 0x7f4c06 < 0x1e ||
		    *(int*) 0x7f4c06 >= 0x32) {
			*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
			goto sync_time;
		}
		if (*(char*) &g_774964) {
			fcn_004c30a0(-7, 0, (char*) 0x6a6d50, -1, 0xfa);
			if (*(char*) 0x7766b9 != 0 && (gm_RandomMod(10) & 0xffff) > 7)
				fcn_004c30a0(*(int*) (action + 0xac), 0, (char*) 0x6a6bcc, -1, 0xfa);
		}
		he_FreeAction(action);
		return;
	case -2:
	case -1:
		he_FreeAction(action);
		return;
	default:
		return;
	}
sync_time:
	gm_AddTime((char*) &gm_GameTime, 0, 0, 1);
}
