#include <string.h>
#include "Develop/client_types.h"
extern Rec24_99f5a0 gm_DisasterState;
extern char* gm_CityEntity;

#pragma pack(push, 2)
typedef struct Time14 {
	int day;
	unsigned short hour;
	int min;
	int sec;
} Time14;
#pragma pack(pop)

unsigned short __cdecl gm_RandomMod(int);
double __cdecl gm_RandomFloat01(void);
int __cdecl he_StartHandlungSearch(int, int, int);
void __cdecl gm_AddTime(Time14* t, int hours, int minutes, int seconds);
void __cdecl cm_SendCopyEntityData(void* msg);
int __cdecl cm_SendRandomEventState(void* msg);

extern int gm_GameTime;
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x004fb7a0 */
void __cdecl gm_UpdateDisasterState(void)
{
	int st[9];
	int sel[16];
	unsigned char ev[0xf8];
	int msg[10];
	int phase;
	int nextPhase;
	float f;

	if (gm_DisasterState.head != 1) {
		return;
	}
	memcpy(st, (void*) 0x99f5a0, sizeof(st));
	phase = *(int*) 0x99f5bc;
	if (phase > 0) {
		if (phase == 1) {
			if (he_StartHandlungSearch(1, 0, 0x59)) {
				return;
			}
		} else if (phase == 2) {
			if (he_StartHandlungSearch(1, 0, 0x4e)) {
				return;
			}
		} else if (phase == 3) {
			if (he_StartHandlungSearch(1, 0, 0x50)) {
				return;
			}
		}
		st[7] = 0;
		*(float*) (st + 5) = 0.0f;
		goto send_state;
	}
	f = gm_RandomFloat01() * *(float*) (st + 4) + *(float*) (st + 3) + *(float*) (st + 5);
	*(float*) (st + 5) = f;
	if (!(f > *(float*) (st + 6))) {
		goto send_state;
	}
	memset(ev, 0, sizeof(ev));
	st[1] += 1;
	st[2] = *(int*) 0x7f4c00;
	if (st[8] >= 4) {
		st[8] = 0;
		st[7] = 3;
		goto state3;
	}
	if (st[8] == 0) {
		st[7] = 3;
		goto state3;
	}
	sel[15] = 2;
	sel[14] = 2;
	sel[8] = 1;
	sel[7] = 1;
	sel[1] = 0;
	sel[0] = 0;
	if (st[8] == 1) {
		sel[2] = 1;
		sel[3] = 1;
		sel[4] = 1;
		sel[5] = 1;
		sel[6] = 1;
		sel[9] = 2;
		sel[10] = 2;
		sel[11] = 2;
		sel[12] = 2;
		sel[13] = 2;
		nextPhase = sel[gm_RandomMod(0x10) & 0xffff] + 1;
	} else if (st[8] == 2) {
		sel[6] = 0;
		sel[5] = 0;
		sel[4] = 0;
		sel[3] = 0;
		sel[2] = 0;
		sel[9] = 2;
		sel[10] = 2;
		sel[11] = 2;
		sel[12] = 2;
		sel[13] = 2;
		nextPhase = sel[gm_RandomMod(0x10) & 0xffff] + 1;
	} else {
		sel[6] = 0;
		sel[5] = 0;
		sel[4] = 0;
		sel[3] = 0;
		sel[2] = 0;
		sel[9] = 1;
		sel[10] = 1;
		sel[11] = 1;
		sel[12] = 1;
		sel[13] = 1;
		nextPhase = sel[gm_RandomMod(0x10) & 0xffff] + 1;
	}
	st[7] = nextPhase;
	if (nextPhase == 1) {
		ev[4] = 'Y';
		*(int*) (ev + 8) = *(int*) (gm_CityEntity + 4);
		*(int*) (ev + 0xc) = -1;
		*(int*) (ev + 0x28) = gm_GameTime;
		*(int*) (ev + 0x2c) = gm_GameTimeHour;
		*(int*) (ev + 0x30) = gm_GameTimeSliceDword;
		*(unsigned short*) (ev + 0x34) = gm_GameTimeTailWord;
		ev[0x36] = 2;
		*(int*) (ev + 0x58) = (gm_RandomMod(3) & 0xffff) * 3;
		*(int*) (ev + 0x28) = gm_GameTime;
		*(int*) (ev + 0x2c) = gm_GameTimeHour;
		*(int*) (ev + 0x30) = gm_GameTimeSliceDword;
		*(unsigned short*) (ev + 0x34) = gm_GameTimeTailWord;
		((Time14*) (ev + 0x28))->min = 0;
		if ((unsigned short) gm_GameTimeHour < 0x17 && (unsigned short) gm_GameTimeHour >= 7) {
			gm_AddTime((Time14*) (ev + 0x28), gm_RandomMod(4) & 0xffff, (gm_RandomMod(2) & 0xffff) * 30, 0);
		} else {
			gm_AddTime((Time14*) (ev + 0x28), (gm_RandomMod(4) & 0xffff) + 7, (gm_RandomMod(2) & 0xffff) * 30, 0);
		}
	} else if (nextPhase == 2) {
		ev[4] = 'N';
		*(int*) (ev + 8) = *(int*) (gm_CityEntity + 4);
		*(int*) (ev + 0xc) = -1;
		*(int*) (ev + 0x58) = -1;
		*(int*) (ev + 0x28) = gm_GameTime;
		*(int*) (ev + 0x2c) = gm_GameTimeHour;
		*(int*) (ev + 0x30) = gm_GameTimeSliceDword;
		*(unsigned short*) (ev + 0x34) = gm_GameTimeTailWord;
		ev[0x36] = 1;
		*(int*) (ev + 0x74) = 1000;
		((Time14*) (ev + 0x28))->min = 0;
		if ((unsigned short) gm_GameTimeHour >= 0x17) {
			gm_AddTime((Time14*) (ev + 0x28), (gm_RandomMod(4) & 0xffff) + 7, (gm_RandomMod(2) & 0xffff) * 30, 0);
		} else {
			gm_AddTime((Time14*) (ev + 0x28), gm_RandomMod(4) & 0xffff, (gm_RandomMod(2) & 0xffff) * 30, 0);
		}
	} else if (nextPhase == 3) {
state3:
		ev[4] = 'P';
		*(int*) (ev + 8) = *(int*) (gm_CityEntity + 4);
		*(int*) (ev + 0x28) = gm_GameTime;
		*(int*) (ev + 0xc) = -1;
		*(int*) (ev + 0x2c) = gm_GameTimeHour;
		*(int*) (ev + 0x30) = gm_GameTimeSliceDword;
		*(unsigned short*) (ev + 0x34) = gm_GameTimeTailWord;
		ev[0x36] = 2;
		*(int*) (ev + 0x58) = -1;
		*(int*) (ev + 0x74) = 1000;
		if ((unsigned short) gm_GameTimeHour >= 0x17) {
			gm_AddTime((Time14*) (ev + 0x28), (gm_RandomMod(4) & 0xffff) + 7, (gm_RandomMod(2) & 0xffff) * 30, 0);
		} else {
			gm_AddTime((Time14*) (ev + 0x28), gm_RandomMod(4) & 0xffff, (gm_RandomMod(2) & 0xffff) * 30, 0);
		}
	} else {
		st[8] = nextPhase;
		goto send_state;
	}
	cm_SendCopyEntityData(ev);
	st[8] = st[7];
send_state:
	memcpy(msg, st, sizeof(st));
	msg[9] = 0x73657420;
	cm_SendRandomEventState(msg);
}
