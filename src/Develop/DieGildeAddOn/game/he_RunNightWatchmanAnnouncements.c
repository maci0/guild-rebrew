#include "Develop/DieGildeAddOn/game/client_data.h"
extern int __cdecl gm_GetSeason(char*); extern void __cdecl d3snd_QueueSound(int, int, char*, int, int);
extern void __cdecl he_FreeAction(char*);
extern void __cdecl gm_AddTime(char*, int, int, int);
extern unsigned short __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/game_data.h"

/* Night-watchman action 0x73 START: due and start are now, picks a random id offset and
 * the announce hour from the table. */
/* ADDRESS: GOLDTL 0x0056e8e0 */
void __cdecl fcn_0056e8e0(char* a0)
{
	*(pos14_7f4c00*) (a0 + 0x52) = gm_GameTime;
	*(pos14_7f4c00*) (a0 + 0x44) = gm_GameTime;
	*(int*) (a0 + 0xac) = (int) gm_RandomMod(5) - 5;
	*(unsigned short*) (a0 + 0x56) = (unsigned short) (int) *(float*) (gm_GetSeason((char*) &gm_GameTime) * 4 + 0x696540);
	*(int*) (a0 + 0x58) = 0;
}

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
	idx = gm_GetSeason((char*) &gm_GameTime);
	switch (*(int*) (action + 0x70)) {
	case 0:
		w = *(int*) &gm_GameTimeHour & 0xffff;

		if (!((float) w >= *(float*) (idx * 4 + 0x696540)) || !((float) w < *(float*) (idx * 4 + 0x696540) + 1.0f)) {
			*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
			goto sync_time;
		}
		if (*(char*) &gm_InWorldHud)
			d3snd_QueueSound(-7, 0, (char*) 0x6a6d50, -1, 0xfa);
		if (*(char*) 0x7766b9 != 0 && *(char*) &gm_InWorldHud != 0 &&
		    (gm_RandomMod(10) & 0xffff) > 7 && *(char*) &gm_InWorldHud != 0) {
			d3snd_QueueSound(*(int*) (action + 0xac), 0, (char*) 0x6a6d30, -1, 0xfa);
			if (*(float*) (idx * 4 + 0x696540) == 7.0f) {
				d3snd_QueueSound(*(int*) (action + 0xac), 0, (char*) 0x6a6d10, -1, 0xfa);
			} else if (*(float*) (idx * 4 + 0x696540) == 8.0f) {
				if (idx == 2)
					d3snd_QueueSound(*(int*) (action + 0xac), 0, (char*) 0x6a6cec, -1, 0xfa);
				else
					d3snd_QueueSound(*(int*) (action + 0xac), 0, (char*) 0x6a6ccc, -1, 0xfa);
			} else if (*(float*) (idx * 4 + 0x696540) == 9.0f) {
				d3snd_QueueSound(*(int*) (action + 0xac), 0, (char*) 0x6a6cac, -1, 0x3e8);
			}
			if ((gm_RandomMod(10) & 0xffff) > 7)
				d3snd_QueueSound(*(int*) (action + 0xac), 0, (char*) 0x6a6c8c, -1, 0x3e8);
		}
		*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
		*(unsigned short*) (action + 0x56) = (unsigned short) (int) *(float*) (idx * 4 + 0x696550);
		*(int*) (action + 0x58) = 0;
		*(int*) (action + 0x70) += 1;
		return;
	case 1:
		w = *(int*) &gm_GameTimeHour & 0xffff;

		if (!((float) w >= *(float*) (idx * 4 + 0x696550)) || !((float) w < *(float*) (idx * 4 + 0x696550) + 1.0f)) {
			*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
			goto sync_time;
		}
		if (*(char*) &gm_InWorldHud)
			d3snd_QueueSound(-7, 0, (char*) 0x6a6d50, -1, 0xfa);
		if (*(char*) 0x7766b9 != 0 && *(char*) &gm_InWorldHud != 0 &&
		    (gm_RandomMod(10) & 0xffff) > 7 && *(char*) &gm_InWorldHud != 0) {
			d3snd_QueueSound(*(int*) (action + 0xac), 0, (char*) 0x6a6d30, -1, 0xfa);
			if (*(float*) (idx * 4 + 0x696550) == 19.0f) {
				d3snd_QueueSound(*(int*) (action + 0xac), 0, (char*) 0x6a6c6c, -1, 0xfa);
			} else if (*(float*) (idx * 4 + 0x696550) == 20.0f) {
				if (idx == 2)
					d3snd_QueueSound(*(int*) (action + 0xac), 0, (char*) 0x6a6c48, -1, 0xfa);
				else
					d3snd_QueueSound(*(int*) (action + 0xac), 0, (char*) 0x6a6c28, -1, 0xfa);
			} else if (*(float*) (idx * 4 + 0x696550) == 21.0f) {
				d3snd_QueueSound(*(int*) (action + 0xac), 0, (char*) 0x6a6c08, -1, 0xfa);
			}
			if ((gm_RandomMod(10) & 0xffff) > 7)
				d3snd_QueueSound(*(int*) (action + 0xac), 0, (char*) 0x6a6be8, -1, 0x3e8);
		}
		*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
		*(unsigned short*) (action + 0x56) = 0x16;
		*(int*) (action + 0x58) = 0x1e;
		*(int*) (action + 0x70) += 1;
		return;
	case 2:
		if (*(unsigned short*) &gm_GameTimeHour < 0x16 || *(int*) 0x7f4c06 < 0x1e ||
		    *(int*) 0x7f4c06 >= 0x32) {
			*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
			goto sync_time;
		}
		if (*(char*) &gm_InWorldHud) {
			d3snd_QueueSound(-7, 0, (char*) 0x6a6d50, -1, 0xfa);
			if (*(char*) 0x7766b9 != 0 && (gm_RandomMod(10) & 0xffff) > 7)
				d3snd_QueueSound(*(int*) (action + 0xac), 0, (char*) 0x6a6bcc, -1, 0xfa);
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
