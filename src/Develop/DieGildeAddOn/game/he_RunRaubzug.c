#include "Develop/DieGildeAddOn/game/entity_record.h"
#include <string.h>
#pragma intrinsic(memcpy, memset, strcpy, strlen, strcat)

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char gm_EntitySlotTable[];
extern unsigned char gm_ActiveTownIndex;
extern char g_6a58ec[];
extern char g_6a6ddc[];
extern char g_6a6dcc[];
extern char g_6a6d78[];
extern char str_empty[];
extern char s_6a6dc4[];
extern char s_6a6a60[];
extern char s_6a6a40[];

extern char s_68be9c[];
extern char s_68bea4[];
#include "Develop/DieGildeAddOn/game/game_data.h"


char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl he_AssignActionSlot(int, int, int, int);
void __cdecl cm_SendCancelCharacterActions(int);
void __cdecl ch_StartMovement(int, int, int, int, int, char*);
int __cdecl gm_IsEntityAtBuilding(int, int);
void __cdecl gm_AddTime(void*, int, int, int);
int __cdecl he_DetectNearbyPatrolAction(int*);
int __cdecl gm_TryRecordCrime(int, int, int, int, int);
void __cdecl cm_RequestPlayAnimation(int, char*, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
char* __cdecl he_StartHandlungSearch(int, int, int);
int __cdecl cm_GetCommandStatus(int);
int* __cdecl cm_GetCommandResult(int);
void __cdecl cm_RequestLinkEvidence(int, int);
void __cdecl cm_BeginPacketFieldDelta(int, int);
void __cdecl cm_AppendPacketFieldValue(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl gm_ConvertUnitsToAmount(int, unsigned char);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
void __cdecl he_MessageBoxQuickjump(unsigned int, int, char*, int, int, int, int, int, char*);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
float __cdecl gm_ApplyEntityHealthDelta(int, int);
char* __cdecl gm_SetupEntityQuery(char*);
void __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
void __cdecl gm_GetScaledEntitySkill(char*, int);
void __cdecl gm_EvalEntityInventoryValue(char*, int*);
float __cdecl gm_GetSeasonPrice(int, unsigned char);
int __cdecl he_HasNoActiveAction0x62(char*);
int __cdecl _ftol(void);
int* __cdecl gm_QueryEntities(int, ...);
int* __cdecl gm_NextEntityQueryMatch(void);
char* __cdecl gm_GetEntityTableEntry(char*);
void __cdecl he_FreeAction(char*);
void __cdecl cm_RequestMoveCredits(int, int, unsigned char, int);
int __cdecl gm_GetMsgField(int, int*);
int __cdecl fcn_0064d41a(char*, char*, ...);

/* ADDRESS: GOLDTL 0x0056ee80 */
/* ADDRESS: GOLDDE 0x00554e40 */
void __cdecl he_RunRaubzug(char* actionRecord)
{
	char msg[0x400];
	char str[0x100];
	char buf[0x200];
	char gestik[3][0x40];
	int req[4];
	int count;
	int rec1;
	int q;
	int h;
	int row;
	int val;
	int ent;
	int i;
	int cnt;

	memcpy(gestik[0], g_6a58ec, 0x16);
	memset(gestik[0] + 0x16, 0, 0x2a);
	memcpy(gestik[1], g_6a6ddc, 0x15);
	memset(gestik[1] + 0x15, 0, 0x2b);
	memcpy(gestik[2], g_6a6dcc, 0x10);
	memset(gestik[2] + 0x10, 0, 0x30);
	i = 0;
	count = 0;
	switch (*(int*) (actionRecord + 0x70)) {
	case 0: {
		int e;

		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (actionRecord + 0xac));
		if (rec1 == 0) {
			goto tail;
		}
		for (cnt = 0; cnt < 8; cnt++) {
			if (*(int*) (actionRecord + 0x8c + cnt * 4) != -1) {
				e = (int) gm_LookupEntityRecordById(*(int*) (actionRecord + 0x8c + cnt * 4));
				if (e != 0) {
					he_AssignActionSlot(rec1, 0, *(unsigned short*) e, (int) actionRecord);
					cm_SendCancelCharacterActions(*(int*) (actionRecord + 0x8c + cnt * 4));
					ch_StartMovement(*(int*) (actionRecord + 0x8c + cnt * 4), *(int*) (rec1 + 1), -1, 0, 1, s_6a6dc4);
				}
			}
		}
		*(pos14_7f4c00*) (actionRecord + 0x52) = gm_GameTime;
		gm_AddTime(actionRecord + 0x52, 0, 4, 0);
		*(int*) (actionRecord + 0x70) = 1;
		return;
	}
	case 1: {
		int e;

		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (actionRecord + 0xac));
		i = 0;
		for (;;) {
			if (*(int*) (actionRecord + 0x8c + i * 4) != -1) {
				e = (int) gm_LookupEntityRecordById(*(int*) (actionRecord + 0x8c + i * 4));
				if (e != 0 && *(int*) (e + 0x184) != 0 && gm_IsEntityAtBuilding(e, rec1) == 0) {
					break;
				}
			}
			i++;
			if (i >= 8) {
				*(pos14_7f4c00*) (actionRecord + 0x52) = gm_GameTime;
				gm_AddTime(actionRecord + 0x52, 0, 0, 1);
				*(int*) (actionRecord + 0x70) = 2;
				return;
			}
		}
		*(pos14_7f4c00*) (actionRecord + 0x52) = gm_GameTime;
		gm_AddTime(actionRecord + 0x52, 0, 4, 0);
		return;
	}
	case 2:
		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (actionRecord + 0xac));
		if (rec1 == 0) {
			goto label_1bc;
		}
		row = (int) ((int)&((ENTITY_RECORD*)gm_EntitySlotTable)[(unsigned short) *(unsigned short*) (rec1 + 0x27)]);
		req[0] = rec1;
		req[1] = 0x451c4000;
		req[2] = (int) actionRecord;
		req[3] = 0;
		if (he_DetectNearbyPatrolAction(req) != 0) {
			h = req[3];
			*(int*) (actionRecord + 0xb4) = gm_TryRecordCrime(0x17, 1,
			    *(int*) ((char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[(unsigned short) *(unsigned short*) (actionRecord + 8)] + 4),
			    *(int*) (row + 4), *(int*) (rec1 + 1));
			*(int*) (actionRecord + 0xb8) = *(int*) (h + 4);
			*(int*) (actionRecord + 0xbc) = *(int*) (h + 0xb0);
			*(int*) (actionRecord + 0x70) = 3;
			*(pos14_7f4c00*) (actionRecord + 0x52) = gm_GameTime;
			return;
		}
label_1bc:
		{
		int e;

		for (cnt = 0; cnt < 8; cnt++) {
			if (*(int*) (actionRecord + 0x8c + cnt * 4) != -1) {
				e = (int) gm_LookupEntityRecordById(*(int*) (actionRecord + 0x8c + cnt * 4));
				if (e != 0) {
					he_AssignActionSlot(rec1, 0, *(unsigned short*) e, (int) actionRecord);
					cm_SendCancelCharacterActions(*(int*) (actionRecord + 0x8c + cnt * 4));
					ch_StartMovement(*(int*) (actionRecord + 0x8c + cnt * 4), *(int*) (rec1 + 1), -1, 0, 0, s_6a6dc4);
					cm_RequestPlayAnimation(*(int*) (actionRecord + 0x8c + cnt * 4), gestik[gm_RandomMod(3)], 1);
				}
			}
		}
		}
		*(int*) (actionRecord + 0x70) = 5;
		*(pos14_7f4c00*) (actionRecord + 0x52) = gm_GameTime;
		gm_AddTime(actionRecord + 0x52, 0, 0xf, 0);
		return;
	case 3: {
		int e;

		if (*(int*) (actionRecord + 0xb4) != -1 && cm_GetCommandStatus(*(int*) (actionRecord + 0xb4)) == 0) {
			return;
		}
		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (actionRecord + 0xac));
		q = (int) he_StartHandlungSearch(1, 1, *(int*) (actionRecord + 0xb8));
		if (rec1 != 0 && q != 0 && *(int*) (q + 0xd4) == *(int*) (actionRecord + 4) && *(int*) (actionRecord + 0xb4) != -1) {
			e = (int) gm_LookupEntityRecordById(*(int*) (actionRecord + 0xb8));
			h = (int) cm_GetCommandResult(*(int*) (actionRecord + 0xb4));
			if (e != 0 && h != 0) {
				cm_RequestLinkEvidence(*(int*) h, *(int*) (e + 4));
			}
			*(int*) (actionRecord + 0x70) = 4;
			gm_AddTime(actionRecord + 0x52, 0, 10, 0);
			return;
		}
		*(int*) (actionRecord + 0x70) = -1;
		return;
	}
	case 4:
		q = (int) he_StartHandlungSearch(1, 1, *(int*) (actionRecord + 0xb8));
		if (q == 0) {
			*(int*) (actionRecord + 0x70) = -1;
			return;
		}
		if (*(int*) (q + 0xd4) == *(int*) (actionRecord + 4)) {
			gm_AddTime(actionRecord + 0x52, 0, 6, 0);
			return;
		}
		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (actionRecord + 0xac));
		if (rec1 != 0) {
			val = (int) gm_LookupEntityRecordById(*(int*) ((char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[(unsigned short) *(unsigned short*) (actionRecord + 8)] + 4));
			row = (int) ((int)&((ENTITY_RECORD*)gm_EntitySlotTable)[(unsigned short) *(unsigned short*) (q + 8)]);
			if (row != 0 && val != 0) {
				ent = gm_ConvertUnitsToAmount(gm_RandomMod(200) + 0x226, gm_ActiveTownIndex);
				io_FormatTextBuffer(buf, 0x19ea, rec1, ent, *(unsigned short*) row);
				he_PostEntityMessage(*(int*) (val + 4), *(int*) (val + 4), buf, 1, 0x5f0, s_6a6a60);
				io_FormatTextBuffer(buf, 0x19eb, rec1, ent);
				he_PostEntityMessage(*(int*) (row + 4), *(int*) (row + 4), buf, 1, 0x5f0, (char*) 0x6a6a4c);
				cm_RequestTransferCurrencyNoKill(*(int*) (row + 4), *(int*) (val + 4), gm_ActiveTownIndex, ent);
			}
			q = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (actionRecord + 0xbc));
			if (q != 0) {
				cm_BeginPacketFieldDelta(q, *(int*) (q + 1));
				cm_AppendPacketFieldValue(4, 1, 0x65, &ent);
				cm_RequestChangeAttribute();
			}
		}
		for (cnt = 0; cnt < 8; cnt++) {
			if (*(int*) (actionRecord + 0x8c + cnt * 4) != -1) {
				val = (int) gm_LookupEntityRecordById(*(int*) (actionRecord + 0x8c + cnt * 4));
				if (val != 0) {
					gm_ApplyEntityHealthDelta(*(unsigned short*) val, 0xffffff9c - gm_RandomMod(100));
				}
			}
		}
		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (actionRecord + 0xb0));
		if (rec1 == 0) {
			goto tail;
		}
		q = (int) gm_SetupEntityQuery((char*) rec1);
		for (i = 0; i < 8; i++) {
			if (*(int*) (actionRecord + 0x8c + i * 4) != -1) {
				cm_SendCancelCharacterActions(*(int*) (actionRecord + 0x8c + i * 4));
				ch_StartMovement(*(int*) (actionRecord + 0x8c + i * 4), *(int*) (rec1 + 1), *(int*) (q + 2), 0, 0, s_6a6a40);
			}
		}
		he_FreeAction(actionRecord);
		return;
	case 5:
		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (actionRecord + 0xac));
		ent = (int) gm_LookupEntityRecordById(*(int*) ((char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[(unsigned short) *(unsigned short*) (actionRecord + 8)] + 4));
		if (rec1 == 0 || ent == 0) {
			*(int*) (actionRecord + 0x70) = 0xfffffffe;
			return;
		}
		row = (int) ((int)&((ENTITY_RECORD*)gm_EntitySlotTable)[(unsigned short) *(unsigned short*) (rec1 + 0x27)]);
		h = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (actionRecord + 0xb0));
		if (h != 0) {
			q = (int) gm_SetupEntityQuery((char*) h);
			i = (int) gm_QueryEntities(*(int*) (h + 0x5d), 2, 6, 0, 0x116);
			cnt = 8;
			do {
				if (*(int*) (actionRecord + 0x8c + (8 - cnt) * 4) != -1) {
					val = (int) gm_LookupEntityRecordById(*(int*) (actionRecord + 0x8c + (8 - cnt) * 4));
					if (val != 0) {
						cm_SendCancelCharacterActions(*(int*) (actionRecord + 0x8c + (8 - cnt) * 4));
						ch_StartMovement(*(int*) (actionRecord + 0x8c + (8 - cnt) * 4), *(int*) (h + 1), *(int*) (q + 2), 0, 0, s_6a6dc4);
						count++;
						gm_GetScaledEntitySkill((char*) val, 2);
						he_AssignActionSlot(h, 0, *(unsigned short*) val, 0);
					}
				}
				cnt--;
			} while (cnt != 0);
			val = 1;
			gm_TryRecordCrime(0x17, 1,
			    *(int*) ((char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[(unsigned short) *(unsigned short*) (actionRecord + 8)] + 4),
			    *(int*) (row + 4), *(int*) (h + 1));
		} else {
			val = 0;
		}
		if (he_HasNoActiveAction0x62((char*) row) == 0 || val == 0) {
			goto label_fa92;
		}
		msg[0] = str_empty[0];
		memset(msg + 1, 0, 0x3ff);
		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (actionRecord + 0xac));
		h = (int) gm_QueryEntities(*(int*) (rec1 + 0x5d), 2, 6, 0, 0x2a);
		gm_EvalEntityInventoryValue((char*) rec1, req);
		val = (int) (*(int*) req * 0.35);
		io_FormatTextBuffer(str, 0x68bea4, val);
		strcat(msg, str);
		cm_RequestMoveCredits(*(int*) (ent + 4), *(int*) (row + 4), gm_ActiveTownIndex, val);
		cm_BeginPacketFieldDelta(rec1, *(int*) (rec1 + 1));
		cm_AppendPacketFieldValue(4, 1, 0x69, &val);
		cm_RequestChangeAttribute();
		if (h != 0) {
			if (i != 0) {
				q = (int) gm_QueryEntities(*(int*) (h + 0x14), 1, 5);
				while (q != 0) {
					if (gm_RandomMod(100) > 0x32) {
						cnt = gm_GetMsgField(h, (int*) q);
						cnt = (int) ((double) cnt * ((double) count * 0.1));
						if (cnt <= 0) {
							cnt = 1;
						}
						fcn_0064d41a(str, s_68be9c, cnt, *(int*) (*(unsigned short*) q * 8 + 0x14a79c0));
						strcat(msg, str);
						cm_SendSellObjekt(*(int*) (i + 2), *(int*) (h + 2), *(unsigned short*) q, cnt, gm_ActiveTownIndex, 0);
						val = (int) ((double) gm_GetSeasonPrice(*(unsigned short*) q, gm_ActiveTownIndex) * cnt + val);
					}
					q = (int) gm_NextEntityQueryMatch();
				}
			} else {
				memcpy(msg, g_6a6d78, 0x4c);
			}
		}
		q = (int) gm_GetEntityTableEntry((char*) ent);
		if (q != 0) {
			*(int*) (q + 0x14) = *(int*) (q + 0x14) + val;
		}
		if (*(char*) (ent + 2) == 6 || *(char*) (ent + 2) == 7) {
			io_FormatTextBuffer(buf, 0x1a85, *(unsigned short*) row, rec1);
			strcat(msg, buf);
			he_MessageBoxQuickjump(*(int*) (ent + 4), *(int*) (ent + 4), msg, 1, 0x5f0, *(int*) (rec1 + 1), -1, 0, str_empty);
		}
		if (*(char*) (row + 2) == 6 || *(char*) (row + 2) == 7) {
			io_FormatTextBuffer(buf, 0x1a86, rec1, val);
			he_MessageBoxQuickjump(*(int*) (row + 4), *(int*) (row + 4), buf, 0, 0x5f0, *(int*) (rec1 + 1), -1, 0, str_empty);
			he_FreeAction(actionRecord);
			return;
		}
		goto tail;
label_fa92:
		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (actionRecord + 0xac));
		if (rec1 == 0) {
			goto tail;
		}
		if (*(char*) (ent + 2) == 6 || *(char*) (ent + 2) == 7) {
			io_FormatTextBuffer(buf, 0x19e7, *(unsigned short*) row, rec1, 0x19c1);
			he_MessageBoxQuickjump(*(int*) (ent + 4), *(int*) (ent + 4), buf, 1, 0x5f0, *(int*) (rec1 + 1), -1, 0, str_empty);
		}
		if (*(char*) (row + 2) == 6 || *(char*) (row + 2) == 7) {
			io_FormatTextBuffer(buf, 0x19e9, rec1);
			he_MessageBoxQuickjump(*(int*) (row + 4), *(int*) (row + 4), buf, 1, 0x5f0, *(int*) (rec1 + 1), -1, 0, 0);
			he_FreeAction(actionRecord);
			return;
		}
		goto tail;
	case -2:
	case -1:
		h = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (actionRecord + 0xb0));
		if (h != 0) {
			q = (int) gm_SetupEntityQuery((char*) h);
		}
		for (i = 0; i < 8; i++) {
			if (*(int*) (actionRecord + 0x8c + i * 4) != -1) {
				ent = (int) gm_LookupEntityRecordById(*(int*) (actionRecord + 0x8c + i * 4));
				if (ent != 0) {
					cm_SendCancelCharacterActions(*(int*) (actionRecord + 0x8c + i * 4));
					if (h != 0 && q != 0) {
						row = *(int*) (q + 2);
						val = *(int*) (h + 1);
					} else {
						row = -1;
						val = -1;
					}
					ch_StartMovement(*(int*) (actionRecord + 0x8c + i * 4), val, row, 0, 0, s_6a6dc4);
					he_AssignActionSlot(0, 0, *(unsigned short*) ent, 0);
				}
			}
		}
		break;
	default:
		return;
	}
tail:
	he_FreeAction(actionRecord);
}
