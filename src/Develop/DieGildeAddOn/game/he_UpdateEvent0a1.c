#include <string.h>
#include "Develop/client_types.h"

extern pos14_7f4c00 gm_GameTime;

char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl he_AssignActionSlot(int, int, int, char*);
int __cdecl gm_IsEntityAtBuilding(char*, char*);
void __cdecl he_FreeAction(char* unit);
int __cdecl gm_ResolveEntityById(void**, void**, void**, int);
unsigned short* __cdecl gm_SetupEntityQuery(unsigned char*);
void __cdecl cm_SendCancelCharacterActions(int);
int __cdecl ch_StartMovement(int, int, int, char*, int, char*);
void __cdecl cm_RequestPlayAnimation(int, char*, int);
void __cdecl gm_AddTime(void*, int, int, int);
void __cdecl he_AwardEvent0a1Yield(char* entity);
int __cdecl he_FindNextTargetBuilding0a1(char* e);
void __cdecl he_AccumulateEvent0a1Yield(char* u, int count);
int __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x0057d0d0 */
void __cdecl he_UpdateEvent0a1(char* entity)
{
	int found;
	int mode;
	int flag;
	int i;
	int n;
	int k;
	int v;
	char* o;
	char* q;

	int* ids;

	n = 0;
	found = 0;
	mode = 0;
	{
	int objs[4];
	ids = (int*) (entity + 0x8c);
	memset(objs, 0, sizeof(objs));
	i = 4;
	do {
		v = *ids;
		if (v != -1) {
			o = gm_LookupEntityRecordById(v);
			if (o != 0) {
				objs[n] = (int) o;
				n++;
			}
		}
		ids++;
		i--;
	} while (i != 0);
	v = *(int*) (entity + 0x70);
	if (v == -1 || v == -2 || n == 0) {
		for (i = 0; i < n; i++) {
			he_AssignActionSlot(0, 0, *(unsigned short*) objs[i], 0);
		}
		he_FreeAction(entity);
		return;
	}
	if (v == 0) {
	mode = -1;
	if (*(int*) (entity + 0xb0) > 0) {
		found = he_FindNextTargetBuilding0a1(entity);
		flag = 1;
		*(int*) (entity + 0xbc) = *(int*) (entity + 0xbc) + 1;
	}
	else {
		gm_ResolveEntityById((void**) &found, 0, 0, *(int*) (entity + 0x10));
		flag = 0;
		if (found != 0) {
			q = (char*) gm_SetupEntityQuery((unsigned char*) found);
			if (q != 0) {
				mode = *(int*) (q + 2);
			}
		}
	}
	if (found == 0) {
		*(int*) (entity + 0x70) = -1;
		*(pos14_7f4c00*) (entity + 0x52) = gm_GameTime;
		return;
	}
	*(int*) (entity + 0xd0) = *(int*) (found + 1);
	for (i = 0; i < n; i++) {
		o = (char*) objs[i];
		he_AssignActionSlot(0, 0, *(unsigned short*) o, entity);
		cm_SendCancelCharacterActions(*(int*) (o + 4));
		ch_StartMovement(*(int*) (o + 4), *(int*) (found + 1), mode, 0, flag, "Bettler");
	}
	*(int*) (entity + 0x70) = 1;
	*(pos14_7f4c00*) (entity + 0x52) = gm_GameTime;
	gm_AddTime(entity + 0x52, 0, 10, 0);
		return;
	}
		gm_ResolveEntityById((void**) &found, 0, 0, *(int*) (entity + 0xd0));
		if (found == 0) {
			*(int*) (entity + 0x70) = -1;
			*(pos14_7f4c00*) (entity + 0x52) = gm_GameTime;
			return;
		}
		if (*(int*) (entity + 0x70) == 1) {
			char anim[10][64] = {
				"zirkus/anfeuern",
				"zirkus/handstand",
				"zirkus/handstand2",
				"zirkus/lachen",
				"zirkus/lang_winken",
				"zirkus/posieren",
				"zirkus/ruecksalto",
				"zirkus/ruecksalto2",
				"zirkus/stehend_beschwoeren",
				"zirkus/tief_verbeugen"
			};

			for (i = 0; i < n; i++) {
				if (gm_IsEntityAtBuilding((char*) objs[i], (char*) found) == 0) {
					*(int*) (entity + 0x70) = 1;
					*(pos14_7f4c00*) (entity + 0x52) = gm_GameTime;
					gm_AddTime(entity + 0x52, 0, 5, 0);
					return;
				}
			}
			if (*(int*) (entity + 0xb0) <= 0) {
				for (i = 0; i < n; i++) {
					he_AssignActionSlot(0, 0, *(unsigned short*) objs[i], 0);
				}
				he_AwardEvent0a1Yield(entity);
				*(int*) (entity + 0x70) = -1;
				*(pos14_7f4c00*) (entity + 0x52) = gm_GameTime;
				return;
			}
			*(pos14_7f4c00*) (entity + 0x52) = gm_GameTime;
			gm_AddTime(entity + 0x52, 2, 0, 0);
			*(int*) (entity + 0x70) = 2;
			for (i = 0; i < n; i++) {
				o = (char*) objs[i];
				if (*(int*) (o + 0x184) != 0) {
					k = 8;
					do {
						cm_RequestPlayAnimation(*(int*) (o + 4),
						    anim[gm_RandomMod(10) & 0xffff],
						    (gm_RandomMod(2) & 0xffff) + 1);
						k--;
					} while (k != 0);
				}
			}
			return;
		}
		if (*(int*) (entity + 0x70) == 2) {
			for (i = 0; i < n; i++) {
				cm_SendCancelCharacterActions(*(int*) (objs[i] + 4));
			}
			he_AccumulateEvent0a1Yield(entity, n);
			*(int*) (entity + 0xb0) = *(int*) (entity + 0xb0) - 0x78;
			*(pos14_7f4c00*) (entity + 0x52) = gm_GameTime;
			*(int*) (entity + 0x70) = 0;
		}
	}
}
