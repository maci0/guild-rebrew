#include <string.h>

#include "client_types.h"

extern void __cdecl he_FreeAction(char*);
extern char* __cdecl gm_LookupEntityRecordById(int);
extern void __cdecl he_AssignActionSlot(int, int, int, char*);
extern void __cdecl cm_SendCancelCharacterActions(int);
extern int __cdecl ch_StartMovement(int, int, int, char*, int, char*);
extern int __cdecl cm_SendSetHE(int, char*);
extern char* __cdecl he_StartHandlungSearch(int, int, int);
extern char* __cdecl he_fn_Handlung(void);
extern unsigned short __cdecl gm_RandomMod(unsigned short);
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int __cdecl cm_GetCommandStatus(int);
extern char* __cdecl cm_GetCommandResult(int);
extern int __cdecl cut_FindCutsceneById(int);
extern char* __cdecl fcn_00445600(int, int, int, char*);
extern void __cdecl d3_TransformPoint(char*, char*, float*);
extern void __cdecl he_CharacterBehavior(char*, int);
extern void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
extern int __cdecl gm_CompareGameTime(pos14_7f4c00*, pos14_7f4c00*);
extern pos14_7f4c00 gm_GameTime;

/* ADDRESS: GOLDTL 0x00554170 */
void __cdecl he_RunMultiActorAction(char* obj)
{
	unsigned char msg[0x114];
	pos14_7f4c00 stamp;
	pos14_7f4c00* time;
	char* rec;
	char* found;
	char* iter;
	int count = 0;
	int idx;
	int i;
	int added;

	found = 0;
	added = 0;

	if (*(int*) (obj + 0x70) == -2) {
		if (*(unsigned char*) (obj + 0x78) & 4) {
			he_FreeAction(obj);
			return;
		}
		*(int*) (obj + 0x70) = 5;
		added = 1;
	}
	if (*(int*) (obj + 0x70) == -1) {
		he_FreeAction(obj);
		return;
	}
	if (*(unsigned char*) (obj + 0x78) & 4)
		return;
	time = (pos14_7f4c00*) (obj + 0x52);
	*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
	switch (*(int*) (obj + 0x70)) {
	case 0:
		iter = obj + 0x8c;
		for (count = 6; count != 0; count--) {
			rec = gm_LookupEntityRecordById(*(int*) iter);
			if (rec != 0 && *(int*) (rec + 0x184) != 0) {
				he_AssignActionSlot(0, 0, *(unsigned short*) rec, obj);
				cm_SendCancelCharacterActions(*(int*) (rec + 4));
				ch_StartMovement(*(int*) (rec + 4), -1, -1, obj + 0xac, 1, (char*) 0x6a5c7c);
			}
			iter += 4;
		}
		gm_AddTime(time, 0, 5, 0);
		*(int*) (obj + 0x84) = cm_SendSetHE(1, obj);
		return;
	case 1:
		iter = obj + 0x8c;
		while (count < 6) {
			rec = gm_LookupEntityRecordById(*(int*) iter);
			if (rec != 0 && *(int*) (rec + 0x184) != 0 && *(int*) (*(char**) (rec + 0x184) + 0x128) != 0) {
				gm_AddTime(time, 0, 4, 0);
				*(int*) (obj + 0x84) = cm_SendSetHE(1, obj);
				return;
			}
			count++;
			iter += 4;
		}
		*(pos14_7f4c00*) (obj + 0x44) = gm_GameTime;
		gm_AddTime(time, 0, 0xa, 0);
		*(int*) (obj + 0x84) = cm_SendSetHE(2, obj);
		return;
	case 2:
		stamp = *(pos14_7f4c00*) (obj + 0x44);
		gm_AddTime(&stamp, 0x18, 0, 0);
		if (gm_CompareGameTime((pos14_7f4c00*) 0x7f4c00, &stamp) > 0) {
			gm_AddTime(time, 0, 2, 0);
			*(int*) (obj + 0x84) = cm_SendSetHE(5, obj);
			return;
		}
		found = he_StartHandlungSearch(1, 0, 0x48);
		if (found != 0) {
			for (;;) {
				if (strcmp(obj + 0xac, found + 0xac) == 0 &&
				    *(unsigned short*) (obj + 8) != *(unsigned short*) (found + 8))
					break;
				found = he_fn_Handlung();
				if (found == 0)
					goto not_found;
			}
			if (gm_RandomMod(2) != 0 &&
			    *(unsigned short*) (obj + 8) != *(unsigned short*) (found + 8)) {
				memset(msg, 0, sizeof(msg));
				msg[8] = 3;
				msg[0x26] = 0xa2;
				*(int*) (msg + 0xc) = *(int*) ((unsigned int) *(unsigned short*) 0x774970 * 0x21c + 0x7f4ca4);
				*(int*) (msg + 0x14) = -1;
				msg[0x30] = 2;
				msg[0x7c] = 4;
				*(int*) (msg + 0x34) = *(int*) ((unsigned int) *(unsigned short*) (obj + 8) * 0x21c + 0x7f4ca4);
				*(int*) (msg + 0x38) = *(int*) ((unsigned int) *(unsigned short*) (found + 8) * 0x21c + 0x7f4ca4);
				for (i = 0; i < 0x10; i++) {
					*(int*) (msg + 0x80 + i * 4) = -1;
					*(int*) (msg + 0xc0 + i * 4) = -1;
				}
				for (i = 0, idx = 0; i < 8; i++) {
					if (idx >= 6)
						break;
					if (*(int*) (found + 0x8c + i * 4) != -1) {
						*(int*) (msg + 0x80 + idx * 4) = *(int*) (found + 0x8c + i * 4);
						idx++;
					}
				}
				for (i = 0, idx = 0; i < 6; i++) {
					if (idx >= 6)
						break;
					if (*(int*) (obj + 0x8c + i * 4) != -1) {
						*(int*) (msg + 0xc0 + idx * 4) = *(int*) (obj + 0x8c + i * 4);
						idx++;
					}
				}
				*(pos14_7f4c00*) (msg + 0x18) = gm_GameTime;
				*(int*) (msg + 0x100) = -1;
				*(int*) (msg + 0x104) = -1;
				*(int*) (msg + 0x108) = -1;
				*(int*) (msg + 0x10c) = *(int*) (obj + 0xcc);
				gm_AddTime((pos14_7f4c00*) (msg + 0x18), 0x1e, 0, 0);
				*(int*) (obj + 0xd8) = fcn_004c5980(msg);
				*(int*) (obj + 0x70) = 3;
				gm_AddTime(time, 0, 0xa, 0);
				*(int*) (obj + 0x84) = cm_SendSetHE(3, obj);
				return;
			}
		}
	not_found:
		gm_AddTime(time, 0, 0xa, 0);
		if (d3_CurrentContextIndex == 0) {
			rec = fcn_00445600(0, 0x140, 0, obj + 0xac);
			if (rec != 0) {
				float pos[4];

				d3_TransformPoint(rec, rec + 0x4c, pos);
				he_CharacterBehavior(obj, (int) pos);
			}
		}
		*(int*) (obj + 0x84) = cm_SendSetHE(2, obj);
		return;
	case 3:
		gm_AddTime(time, 0, 1, 0);
		if (cm_GetCommandStatus(*(int*) (obj + 0xd8)) != 0) {
			rec = cm_GetCommandResult(*(int*) (obj + 0xd8));
			if (rec != 0) {
				*(int*) (obj + 0xd4) = *(int*) rec;
				*(int*) (obj + 0x84) = cm_SendSetHE(4, obj);
				return;
			}
			*(int*) (obj + 0x84) = cm_SendSetHE(5, obj);
			return;
		}
		*(int*) (obj + 0x84) = cm_SendSetHE(3, obj);
		return;
	case 4:
		gm_AddTime(time, 0, 5, 0);
		if (cut_FindCutsceneById(*(int*) (obj + 0xd4)) != 0) {
			*(int*) (obj + 0x84) = cm_SendSetHE(4, obj);
			return;
		}
		*(int*) (obj + 0x84) = cm_SendSetHE(5, obj);
		return;
	case 5:
		iter = obj + 0x8c;
		for (count = 6; count != 0; count--) {
			rec = gm_LookupEntityRecordById(*(int*) iter);
			if (rec != 0 && *(int*) (rec + 0x184) != 0) {
				he_AssignActionSlot(0, 0, *(unsigned short*) rec, 0);
				cm_SendCancelCharacterActions(*(int*) (rec + 4));
				ch_StartMovement(*(int*) (rec + 4), *(int*) (obj + 0xcc), *(int*) (obj + 0xd0), 0, 0,
					     (char*) 0x6a5c7c);
			}
			iter += 4;
		}
		gm_AddTime(time, 0, 2, 0);
		if (added) {
			he_FreeAction(obj);
			return;
		}
		*(int*) (obj + 0x84) = cm_SendSetHE(-1, obj);
		return;
	default:
		return;
	}
}
