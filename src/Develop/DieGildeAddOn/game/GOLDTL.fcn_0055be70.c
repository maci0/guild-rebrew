


#include <math.h>

// SIZE 0x10
struct search {
	char* who;
	float range;
	char* house;
	char* found;
};

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl cm_SendCancelCharacterActions(int);
void __cdecl cm_RequestPlayAnimation(int, char*, int);
void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5620(int, char*);

int __cdecl he_DetectNearbyPatrolAction(struct search* query)
{
	char* found;
	char* guard;
	char* patrol;
	char* who_pos;
	char* guard_pos;
	float dx;
	float dy;
	float dz;
	int j;

	found = 0;
	guard = 0;
	if (query->who == 0 || *(char**) (query->who + 0x61) == 0) {
		return 0;
	}
	for (patrol = he_StartHandlungSearch(1, 0, 0x43); patrol != 0; patrol = he_fn_Handlung()) {
		if (found != 0) {
			break;
		}
		if (*(int*) (patrol + 0xd4) != -1 || *(int*) (patrol + 0xc) == *(int*) (query->house + 0xc)) {
			continue;
		}
		for (j = 0; j < 4; j++) {
			if (((int*) (patrol + 0xc4))[j] != -1 && (guard = gm_LookupEntityRecordById(((int*) (patrol + 0xc4))[j])) != 0) {
				who_pos = *(char**) (query->who + 0x61);
				guard_pos = *(char**) (*(char**) (guard + 0x184) + 0x34);
				dx = *(float*) (who_pos + 0x4c) - *(float*) (guard_pos + 0x4c);
				dy = *(float*) (who_pos + 0x50) - *(float*) (guard_pos + 0x50);
				dz = *(float*) (who_pos + 0x54) - *(float*) (guard_pos + 0x54);
				if ((float) sqrt(dz * dz + dy * dy + dx * dx) < query->range) {
					found = patrol;
					break;
				}
			}
		}
	}
	if (found == 0) {
		return 0;
	}
	query->found = found;
	for (j = 0; j < 4; j++) {
		if (((int*) (found + 0xc4))[j] != -1 && gm_LookupEntityRecordById(((int*) (found + 0xc4))[j]) != 0) {
			cm_SendCancelCharacterActions(((int*) (found + 0xc4))[j]);
			if (*(int*) (guard + 4) == ((int*) (found + 0xc4))[j]) {
				cm_RequestPlayAnimation(((int*) (found + 0xc4))[j], "gestik/herranwinken", 2);
			}
			fcn_004c5da0(((int*) (found + 0xc4))[j], *(int*) (query->who + 1), -1, 0, 1, "Detected");
			cm_RequestPlayAnimation(((int*) (found + 0xc4))[j], "gestik/abfaellig", gm_RandomMod(2) + 1);
		}
	}
	*(int*) (found + 0xd4) = *(int*) (query->house + 4);
	*(pos14_7f4c00*) (found + 0x52) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (found + 0x52), 0, 8, 0);
	fcn_004c5620(0x400, found);
	return 1;
}
