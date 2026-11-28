/* Drive the merchant trade page: validate the sell request, place the item
 * and report the trade result. */

typedef struct {
	unsigned short id;
	char kind;
	char pad3;
	int h;
	char pad8[0x21c - 8];
} PredigtEntityRecord;

typedef struct {
	int a;
	int b;
	char* who;
} PredigtCollectionResult;

extern PredigtEntityRecord gm_EntitySlotTable[];
extern unsigned char gm_ActiveTownIndex;

void __cdecl he_FreeAction(int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl gm_ResolveEntityById(int*, int, int, int);
int __cdecl cm_SendSetHE(int, int);
void __cdecl gm_AddTime(int, int, int, int);
int __cdecl fcn_00502cd0(int, int, ...);
int __cdecl gm_RandomMod(int);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl he_NotifyThemaPredigt(PredigtEntityRecord*, int, int);
void __cdecl cm_BeginPacketFieldDelta(int, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl gm_ApplyPredigtCollection(int, PredigtCollectionResult*);
int __cdecl io_FormatTextBuffer(char*, int, int, int);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
void __cdecl cm_RequestMoveCredits(int, int, unsigned char, int);
int __cdecl ai_SelectThemaPredigt(PredigtEntityRecord*, int);

/* ADDRESS: GOLDTL 0x0054a6a0 */
void __cdecl he_RunPredigt(int action)
{
	int v2;
	int v3;
	int v4;
	int entity;
	PredigtCollectionResult pair;
	char message[256];
	char v1;

	v2 = action;
	entity = 0;
	if (*(int*) (action + 0x70) == -1 || *(int*) (action + 0x70) == -2) {
		he_FreeAction(action);
		return;
	}
	if (*(unsigned char*) (action + 0x78) & 4) {
		return;
	}
	v4 = *(int*) (action + 0x84);
	if (v4 != -1 && !cm_GetCommandStatus(v4)) {
		return;
	}
	*(int*) (v2 + 0x84) = 0xffffffff;
	gm_ResolveEntityById(&entity, 0, 0, *(int*) (v2 + 0x10));
	if (!entity) {
		cm_SendSetHE(0xffffffff, v2);
		return;
	}
	if (*(unsigned short*) (entity + 0x27) == 0xffff) {
		gm_AddTime(v2 + 0x52, 0x18, 0, 0);
		*(unsigned short*) (v2 + 0x56) = 7;
		cm_SendSetHE(0, v2);
		return;
	}
	v3 = fcn_00502cd0(*(int*) (entity + 0x5d), 1, 0, 0x1b5);
	switch (*(int*) (v2 + 0x70)) {
	case 2: {
		char v8;
		char v9;
		unsigned int v10;
		if (v3 && *(char*) (v3 + 0x22)) {
			v8 = 0;
			v9 = (char) 0xff;
			v10 = 0xffffffff;
			pair.who = 0;
			v4 = gm_LookupEntityRecordById(*(int*) (v3 + 0x1e));
			if (v4) {
				pair.who = (char*) v4;
				he_NotifyThemaPredigt(&gm_EntitySlotTable[*(unsigned short*) (entity + 0x27)], v4, entity);
			}
			cm_BeginPacketFieldDelta(v3, *(int*) (v3 + 2));
			cm_AppendPacketFieldDelta(1, 1, 0x22, (int*) &v8);
			cm_AppendPacketFieldDelta(1, 1, 0x1c, (int*) &v9);
			cm_AppendPacketFieldDelta(1, 1, 0x1d, (int*) &v9);
			cm_AppendPacketFieldDelta(4, 1, 0x1e, (int*) &v10);
			cm_RequestChangeAttribute();
			v4 = gm_ApplyPredigtCollection(entity, &pair);
			if (v4) {
				v1 = gm_EntitySlotTable[*(unsigned short*) (entity + 0x27)].kind;
				if (v1 == 6 || v1 == 7) {
					io_FormatTextBuffer(message, 0x19a7, pair.a, pair.b);
					he_PostEntityMessage(gm_EntitySlotTable[*(unsigned short*) (entity + 0x27)].h,
					             0xffffffff, message, 0, 0x5ff, (char*) 0x6b5c60);
				}
				cm_RequestMoveCredits(gm_EntitySlotTable[*(unsigned short*) (entity + 0x27)].h,
				             0xffffffff, gm_ActiveTownIndex, pair.b);
				cm_BeginPacketFieldDelta(entity, *(int*) (entity + 1));
				cm_AppendPacketFieldDelta(4, 1, 0x69, &pair.b);
				cm_RequestChangeAttribute();
			}
		}
		gm_AddTime(v2 + 0x52, 0x18, 0, 0);
		*(unsigned short*) (v2 + 0x56) = 7;
		*(int*) (v2 + 0x84) = cm_SendSetHE(0, v2);
		break;
	}
	case 1:
		gm_AddTime(v2 + 0x52,
		              (int) ((gm_RandomMod(2) & 0xffff) + 1), 0, 0);
		*(int*) (v2 + 0x84) = cm_SendSetHE(2, v2);
		break;
	case 0:
		v1 = gm_EntitySlotTable[*(unsigned short*) (entity + 0x27)].kind;
		if (v1 != 6 && v1 != 7) {
			if (!v3) {
				gm_AddTime(v2 + 0x52, 0x18, 0, 0);
				*(unsigned short*) (v2 + 0x56) = 7;
				*(int*) (v2 + 0x84) = cm_SendSetHE(0, v2);
				return;
			}
			if (!ai_SelectThemaPredigt(&gm_EntitySlotTable[*(unsigned short*) (entity + 0x27)], v3)) {
				gm_AddTime(v2 + 0x52, 0x18, 0, 0);
				*(unsigned short*) (v2 + 0x56) = 7;
				*(int*) (v2 + 0x84) = cm_SendSetHE(0, v2);
				return;
			}
			gm_AddTime(v2 + 0x52, 1, 0, 0);
			*(int*) (v2 + 0x84) = cm_SendSetHE(1, v2);
		} else if (v3 && *(char*) (v3 + 0x22)) {
			gm_AddTime(v2 + 0x52, 1, 0, 0);
			*(int*) (v2 + 0x84) = cm_SendSetHE(1, v2);
		} else {
			gm_AddTime(v2 + 0x52, 0x18, 0, 0);
			*(unsigned short*) (v2 + 0x56) = 7;
			*(int*) (v2 + 0x84) = cm_SendSetHE(0, v2);
		}
		break;
	}
}
