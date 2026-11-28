#include "Develop/DieGildeAddOn/game/client_data.h"
int __cdecl cm_GetCommandStatus(int a0); int __cdecl cm_GetCommandResult(int a0);
int __cdecl gm_GetEntityTableEntry(int a0);
int __cdecl cm_RequestTransferCurrencyNoKill(int a0, int a1, unsigned char a2, int a3);
void __cdecl he_AssignActionSlot(int a0, int a1, int a2, int a3);
int __cdecl gm_StartFilteredEntitySearch(int a0, int a1, int a2);
int __cdecl ch_StartMovement(int a0, int a1, int a2, int a3, int a4, int a5);
int __cdecl gm_LookupEntityRecordById(int a0);
void __cdecl gm_AddTime(int* p, int a1, int a2, int a3);
int __cdecl gm_CompareGameTime(int a0, int a1);
int __cdecl gm_EvalSkill3PrivilegeCheck(int a0, int a1, int a2);
int __cdecl gm_HasActiveSpecialObject(int a0, int a1);
void __cdecl gm_ModifyHealth(int a0, int a1);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
void __cdecl he_PostEntityMessage(int a0, int a1, char* buf, int a3, int a4, char* text);
int __cdecl gm_TryRecordCrime(int a0, int a1, int a2, int a3, int a4);
void __cdecl cm_RequestCopyEntityData(int a0, int a1, int a2, int a3);
int __cdecl he_DetectNearbyPatrolAction(int* a0);
int __cdecl he_StartHandlungSearch(int a0, int a1, int a2);
int __cdecl cm_RequestLinkEvidence(int a0, int a1);
void __cdecl cm_RequestKillSpieler(int a0, int a1);
void __cdecl he_FreeAction(int a0);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x00562ba0 */
/* ADDRESS: GOLDDE 0x00548d70 */
void __cdecl he_RunPruegel(int eventCursor)
{
	int eventBase;
	int v6;
	int v4;
	int v7;
	int state;
	char targetType;
	char buf[1024];
	int v10[4];
	char v11[4];
	char* pkt;
	char* ep;

	eventBase = eventCursor;
	state = *(int*) (eventCursor + 0x70);
	if (state > 0 && (*(int*) (eventCursor + 0xc8) == 0 || *(int*) (eventCursor + 0xc8) == -1)) {
		*(int*) (eventCursor + 0x70) = -2;
	}
	switch (*(int*) (eventCursor + 0x70)) {
	case 0:
		v6 = *(int*) (eventBase + 0xcc);
		if (v6 != -1 && cm_GetCommandStatus(v6) == 0) {
			return;
		}
		v7 = cm_GetCommandResult(*(int*) (eventBase + 0xcc));
		if (v7 != 0) {
			v4 = gm_GetEntityTableEntry(*(unsigned short*) (eventBase + 8) * 0x21c + (int) &gm_EntitySlotTable);
			if (v4 != 0) {
				*(int*) (v4 + 0x28) = *(int*) (v4 + 0x28) + *(int*) (eventBase + 0xd8);
			}
			*(int*) (eventBase + 0xc8) = *(int*) (v7 + 4);
			cm_RequestTransferCurrencyNoKill(-1, *(int*) (*(unsigned short*) (eventBase + 8) * 0x21c + (unsigned long)&gm_EntityIdField), *(unsigned char*) &gm_ActiveTownIndex, *(int*) (eventBase + 0xd8));
			he_AssignActionSlot(0, 0, *(unsigned short*) v7, eventBase);
			*(int*) (eventBase + 0x70) = *(int*) (eventBase + 0x70) + 1;
			*(int*) (eventBase + 0xcc) = -1;
			return;
		}
		*(int*) (eventBase + 0x70) = -1;
		*(int*) (eventBase + 0xcc) = -1;
		return;
	case 1:
		v6 = gm_StartFilteredEntitySearch(1, 1, *(int*) (eventBase + 0xd0));
		if (v6 != 0) {
			*(int*) (eventBase + 0xcc) = ch_StartMovement(*(int*) (eventBase + 0xc8), *(int*) (v6 + 1), -1, 0, 1, 0x6a659c);
			*(int*) (eventBase + 0x70) = *(int*) (eventBase + 0x70) + 1;
			return;
		}
		goto label_562e74;
	case 2:
		*(int*) (eventBase + 0xcc) = -1;
		v6 = gm_LookupEntityRecordById(*(int*) (eventBase + 0xc8));
		if (v6 == 0) {
			*(int*) (eventBase + 0x70) = -1;
			return;
		}
		if (*(int*) (*(int*) (v6 + 0x184) + 0x128) != 0) {
			pkt = (char*) (eventBase + 0x52);
			*(pos14_7f4c00*) pkt = *(pos14_7f4c00*) &gm_GameTime;
			gm_AddTime((int*) pkt, 0, 4, 0);
			*(int*) (eventBase + 0x70) = 2;
			return;
		}
		*(int*) (eventBase + 0x70) = 7;
		return;
	case 7:
		v6 = gm_StartFilteredEntitySearch(1, 1, *(int*) (eventBase + 0xd0));
		v4 = gm_LookupEntityRecordById(*(int*) (eventBase + 0xb4));
		if (v6 != 0 && v4 != 0) {
			v10[0] = v6;
			v10[1] = 0x457a0000;
			v10[2] = eventBase;
			v10[3] = 0;
			if (he_DetectNearbyPatrolAction(v10) != 0) {
				*(int*) (eventBase + 0xcc) = gm_TryRecordCrime(0x15, 1, *(int*) (*(unsigned short*) (eventBase + 8) * 0x21c + (unsigned long)&gm_EntityIdField), *(int*) (v4 + 4), *(int*) (v6 + 1));
				eventCursor += 0x52;
				*(int*) (eventCursor + 0x1e) = 8;
				*(int*) (eventCursor + 0x82) = *(int*) (v10[3] + 4);
				*(pos14_7f4c00*) eventCursor = *(pos14_7f4c00*) &gm_GameTime;
				return;
			}
		}
label_562e74:
		*(int*) (eventBase + 0x70) = 4;
		return;
	case 8:
		v6 = *(int*) (eventBase + 0xcc);
		if (v6 != -1 && cm_GetCommandStatus(v6) == 0) {
			return;
		}
		v6 = gm_StartFilteredEntitySearch(1, 1, *(int*) (eventBase + 0xac));
		v4 = he_StartHandlungSearch(1, 1, *(int*) (eventBase + 0xd4));
		if (v6 != 0 && v4 != 0 && *(int*) (v4 + 0xd4) == *(int*) (eventBase + 4) && *(int*) (eventBase + 0xcc) != -1) {
			v6 = gm_LookupEntityRecordById(*(int*) (eventBase + 0xd4));
			v7 = cm_GetCommandResult(*(int*) (eventBase + 0xcc));
			if (v7 != 0 && v6 != 0) {
				cm_RequestLinkEvidence(*(int*) v7, *(int*) (v6 + 4));
			}
			*(int*) (eventBase + 0x70) = 9;
			gm_AddTime((int*) (eventBase + 0x52), 0, 10, 0);
			return;
		}
		*(int*) (eventBase + 0x70) = -1;
		return;
	case 9:
		v6 = he_StartHandlungSearch(1, 1, *(int*) (eventBase + 0xd4));
		if (v6 == 0) {
			*(int*) (eventBase + 0x70) = -1;
			return;
		}
		if (*(int*) (v6 + 0xd4) == *(int*) (eventBase + 4)) {
			gm_AddTime((int*) (eventBase + 0x52), 0, 6, 0);
			return;
		}
		ch_StartMovement(*(int*) (eventBase + 0xc8), *(int*) (eventBase + 0x10), -1, 0, 1, 0x6a659c);
		*(pos14_7f4c00*) (eventBase + 0x52) = *(pos14_7f4c00*) &gm_GameTime;
		gm_AddTime((int*) (eventBase + 0x52), 0, 4, 0);
		*(int*) (eventBase + 0x70) = 5;
		return;
	case 3:
		ch_StartMovement(*(int*) (eventBase + 0xc8), *(int*) (eventBase + 0x10), -1, 0, 1, 0x6a659c);
		*(int*) (eventBase + 0x70) = *(int*) (eventBase + 0x70) + 1;
		return;
	case 4:
		if (0 <= gm_CompareGameTime((int*) (eventBase + 0x52), (int) &gm_GameTime)) {
			return;
		}
		ep = (char*) (*(unsigned short*) (eventBase + 8) * 0x21c + (unsigned long)&gm_EntitySlotTable);
		v7 = gm_LookupEntityRecordById(*(int*) (eventBase + 0xb4));
		if (v7 == 0) {
			*(int*) (eventBase + 0x70) = -1;
			return;
		}
		v4 = gm_EvalSkill3PrivilegeCheck((int*) ep, v7, (int) v11);
		if (gm_HasActiveSpecialObject(v7, 0x2c0)) {
			gm_ModifyHealth(*(int*) (ep + 4), -1);
			if (*(char*) (ep + 2) == 6 || *(char*) (ep + 2) == 7) {
				io_FormatTextBuffer(buf, 0x1012, *(unsigned short*) v7, 2);
				he_PostEntityMessage(*(int*) (ep + 4), -1, buf, 0, 0x5fa, 0);
			}
			if (*(char*) (v7 + 2) == 6 || *(char*) (v7 + 2) == 7) {
				io_FormatTextBuffer(buf, 0x1010);
				he_PostEntityMessage(*(int*) (v7 + 4), -1, buf, 0, 0x5fb, (char*) 0x6a6538);
			}
			*(int*) (eventBase + 0x70) = *(int*) (eventBase + 0x70) + 1;
			return;
		} else if (gm_HasActiveSpecialObject(v7, 0x17c) != 0) {
			if (*(char*) (ep + 2) == 6 || *(char*) (ep + 2) == 7) {
				io_FormatTextBuffer(buf, 0xff3);
				he_PostEntityMessage(*(int*) (ep + 4), -1, buf, 0, 0x5fa, 0);
			}
			*(int*) (eventBase + 0x70) = *(int*) (eventBase + 0x70) + 1;
			return;
		} else {
			targetType = *(char*) (v7 + 2);
			if (v4 != 0) {
				if (targetType == 6 || targetType == 7) {
					io_FormatTextBuffer(buf, 0x173b, 2);
					he_PostEntityMessage(*(int*) (v7 + 4), -1, buf, 0, 0x5fb, (char*) 0x6a6538);
				}
				if (*(char*) (ep + 2) == 6 || *(char*) (ep + 2) == 7) {
					io_FormatTextBuffer(buf, 0x173a, *(unsigned short*) v7);
					he_PostEntityMessage(*(int*) (ep + 4), -1, buf, 0, 0x5fa, 0);
				}
				if (gm_HasActiveSpecialObject(v7, 0x2b4)) {
					gm_ModifyHealth(*(int*) (eventBase + 0xb4), -1);
				} else {
					gm_ModifyHealth(*(int*) (eventBase + 0xb4), -2);
				}
			} else {
				if (targetType == 6 || targetType == 7) {
					io_FormatTextBuffer(buf, 0x173d);
					he_PostEntityMessage(*(int*) (v7 + 4), -1, buf, 0, 0x5fb, 0);
				}
				if (*(char*) (ep + 2) == 6 || *(char*) (ep + 2) == 7) {
					io_FormatTextBuffer(buf, 0x173c, *(unsigned short*) v7);
					he_PostEntityMessage(*(int*) (ep + 4), -1, buf, 0, 0x5fa, 0);
				}
			}
			gm_TryRecordCrime(0x15, 1, *(int*) (*(unsigned short*) (eventBase + 8) * 0x21c + (unsigned long)&gm_EntityIdField), *(int*) (eventBase + 0xb4), *(int*) (eventBase + 0xac));
			targetType = *(char*) (v7 + 2);
			if (targetType != 6 && targetType != 7) {
				cm_RequestCopyEntityData(*(int*) (ep + 4), *(int*) (v7 + 4), -0x19, 1);
			}
		}
		*(int*) (eventBase + 0x70) = *(int*) (eventBase + 0x70) + 1;
		return;
	case 5:
		v6 = gm_LookupEntityRecordById(*(int*) (eventBase + 0xc8));
		if (v6 == 0) {
			*(int*) (eventBase + 0x70) = -1;
			return;
		}
		if (*(int*) (*(int*) (v6 + 0x184) + 0x128) != 0) {
			*(pos14_7f4c00*) (eventBase + 0x52) = *(pos14_7f4c00*) &gm_GameTime;
			gm_AddTime((int*) (eventBase + 0x52), 0, 4, 0);
			return;
		}
		*(int*) (eventBase + 0x70) = -1;
		return;
	case -2:
	case -1:
		if (*(int*) (eventBase + 0xc8) != -1) {
			cm_RequestKillSpieler(*(int*) (eventBase + 0xc8), 1);
		}
		he_FreeAction(eventBase);
		return;
	}
}
