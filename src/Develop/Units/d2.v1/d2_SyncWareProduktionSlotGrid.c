extern int d2_SelectedEntityUiFlags;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern char* lpObjektePROT;
extern char* cm_PacketDeltaBase;

char* __cdecl gm_QueryEntities(int, int, int, ...);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_GetBuildingTypeCategory(int);
int __cdecl gm_GetStorageSlotCapacity(char*, int);
int __cdecl gm_GetMsgField(char*, void*);
int __cdecl cm_BeginPacketFieldDelta(int, int);
int __cdecl cm_AppendCommandSyncField(int, int, int, int*);
void __cdecl cm_SendSetAttribute(void);
int __cdecl d2_GetControlValue(int);
int __cdecl CountDisplayCounters(void);

/* ADDRESS: GOLDTL 0x00595e20 */
/* ADDRESS: GOLDDE 0x0057b8e0 */
int __cdecl d2_SyncWareProduktionSlotGrid(char* building, char* a1)
{
	unsigned int tbl1[36];
	unsigned int tbl2[18];
	int cat;
	register int found;
	int i;
	unsigned int* p;
	unsigned short* ent;
	char* q;

	tbl1[2] = 0;
	tbl1[0x12] = 0;
	tbl1[3] = 0;
	tbl1[0xa] = 0;
	tbl1[0x13] = 0;
	tbl1[0x16] = 0;
	tbl1[0xb] = 0;
	tbl1[0x17] = 0;
	tbl1[6] = 0;
	tbl1[0x1a] = 0;
	tbl1[0xc] = 3;
	tbl1[0x14] = 3;
	tbl1[0x1d] = 3;
	tbl2[7] = 3;
	tbl2[0xb] = 3;
	tbl2[0xe] = 3;
	tbl1[0] = 2;
	tbl1[4] = 2;
	tbl1[7] = 0;
	tbl1[8] = 2;
	tbl1[0x15] = 2;
	tbl1[0x19] = 2;
	tbl1[0x1b] = 0;
	tbl2[1] = 2;
	tbl2[3] = 2;
	tbl2[5] = 2;
	tbl2[0xa] = 2;
	tbl2[0xc] = 2;
	tbl1[0xe] = 0;
	tbl1[0x1e] = 0;
	tbl1[0xf] = 0;
	tbl1[0x1f] = 0;
	tbl1[0x22] = 0;
	tbl1[1] = 0;
	tbl1[5] = 0;
	tbl1[9] = 0;
	tbl1[0xd] = 0;
	tbl1[0x10] = 4;
	tbl1[0x11] = 0;
	tbl1[0x18] = 4;
	tbl1[0x1c] = 4;
	tbl1[0x20] = 4;
	tbl1[0x21] = 4;
	tbl1[0x23] = 0;
	tbl2[0] = 0;
	tbl2[2] = 0;
	tbl2[4] = 0;
	tbl2[6] = 0;
	tbl2[8] = 0;
	tbl2[9] = 4;
	tbl2[0xd] = 4;
	tbl2[0xf] = 4;
	tbl2[0x10] = 4;
	tbl2[0x11] = 4;

	cat = gm_GetBuildingTypeCategory(*(unsigned char*) building);

	i = 0;
	for (p = (unsigned int*) 0x778d4c; (int) p < 0x778d9c; p += 5) {
		*p = tbl1[*(unsigned char*) (a1 + 0x1c) * 4 + i];
		i++;
	}
	i = 0;
	for (p = (unsigned int*) 0x77912c; (int) p < 0x779154; p += 5) {
		*p = tbl2[*(unsigned char*) (a1 + 0x1d) * 2 + i];
		i++;
	}

	ent = (unsigned short*) gm_QueryEntities(*(int*) (a1 + 0x14), 1, 5);
	while (ent != 0) {
		if (cat != 2) {
			q = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*ent]);
			if (*q == 0x17 || *q == 0x25)
				goto add16;
		} else {
			if (*(char*) (((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*ent])) == 0x17)
				goto add16;
		}

		for (i = 0, p = (unsigned int*) 0x7796e0; (int) p < 0x7798a0; p += 0xe) {
			if (*p == *ent)
				break;
			i++;
		}
		if (i < 8) {
			*(int*) (i * 0x38 + 0x77970c) =
			    (unsigned int) (gm_GetStorageSlotCapacity(a1, *ent) * *(int*) (ent + 0xe)) >> 2;
			*(int*) (i * 0x38 + 0x779710) = gm_GetMsgField(a1, ent);
			*(int*) (i * 0x38 + 0x779714) = gm_GetStorageSlotCapacity(a1, *ent);
			goto next;
		}
		for (i = 0, p = (unsigned int*) 0x7796e0; (int) p < 0x7798a0; p += 0xe) {
			if (*p == 0)
				break;
			i++;
		}
		if (i < 8) {
			*(int*) (i * 0x38 + 0x7796e0) = *ent;
			*(int*) (i * 0x38 + 0x77970c) =
			    (unsigned int) (gm_GetStorageSlotCapacity(a1, *ent) * *(int*) (ent + 0xe)) >> 2;
			*(int*) (i * 0x38 + 0x779710) = gm_GetMsgField(a1, ent);
			*(int*) (i * 0x38 + 0x779714) = gm_GetStorageSlotCapacity(a1, *ent);
		}
		goto next;

	add16:
		for (i = 0, p = (unsigned int*) 0x778da0; (int) p < 0x779120; p += 0xe) {
			if (*p == *ent)
				break;
			i++;
		}
		if (i < 16) {
			*(int*) (i * 0x38 + 0x778dcc) =
			    (unsigned int) (gm_GetStorageSlotCapacity(a1, *ent) * *(int*) (ent + 0xe)) >> 2;
			*(int*) (i * 0x38 + 0x778dd0) = gm_GetMsgField(a1, ent);
			*(int*) (i * 0x38 + 0x778dd4) = gm_GetStorageSlotCapacity(a1, *ent);
			goto next;
		}
		for (i = 0, p = (unsigned int*) 0x778da0; (int) p < 0x779120; p += 0xe) {
			if (*p == 0)
				break;
			i++;
		}
		if (i < 16) {
			*(int*) (i * 0x38 + 0x778da0) = *ent;
			*(int*) (i * 0x38 + 0x778dcc) =
			    (unsigned int) (gm_GetStorageSlotCapacity(a1, *ent) * *(int*) (ent + 0xe)) >> 2;
			*(int*) (i * 0x38 + 0x778dd0) = gm_GetMsgField(a1, ent);
			*(int*) (i * 0x38 + 0x778dd4) = gm_GetStorageSlotCapacity(a1, *ent);
		}

	next:
		ent = (unsigned short*) gm_NextEntityQueryMatch();
	}

	for (p = (unsigned int*) 0x778da0; (int) p < 0x779120; p += 0xe) {
		if (!gm_QueryEntities(*(int*) (a1 + 0x14), 1, 0, *p))
			*p = 0;
	}
	for (p = (unsigned int*) 0x7796e0; (int) p < 0x7798a0; p += 0xe) {
		if (!gm_QueryEntities(*(int*) (a1 + 0x14), 1, 0, *p))
			*p = 0;
	}

	found = 0;
	for (p = (unsigned int*) 0x778db0; !found && (int) p < 0x779130; p += 0xe) {
		if (*p != (unsigned int) -1
		    && *(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[*p].kind)) == 0x41
		    && d2_GetControlValue(*p))
			found = 1;
	}
	if (!found) {
		for (p = (unsigned int*) 0x7796f0; !found && (int) p < 0x7798b0; p += 0xe) {
			if (*p != (unsigned int) -1
			    && *(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[*p].kind)) == 0x41
			    && d2_GetControlValue(*p))
				found = 1;
		}
	}

	if ((d2_SelectedEntityUiFlags & 0x200) != 0 && g_14ce8d8 != 0 && !CountDisplayCounters()) {
		for (p = (unsigned int*) 0x778dc0; (int) p < 0x779140; p += 0xe) {
			if (*p == (unsigned int) -1 || *p != *(unsigned int*) 0x67d370)
				continue;
			ent = (unsigned short*) gm_QueryEntities(*(int*) (a1 + 0x14), 1, 0, p[-8]);
			if (ent == 0)
				break;
			if (*(unsigned int*) (ent + 0xe) >= 4)
				cat = 0;
			else
				cat = *(unsigned int*) (ent + 0xe) + 1;
			cm_BeginPacketFieldDelta((int) ent, *(int*) (ent + 1));
			cm_AppendCommandSyncField(4, 1, (int) ((char*) ent - cm_PacketDeltaBase) + 0x1c, &cat);
			cm_SendSetAttribute();
			*(int*) (ent + 0xe) = cat;
		}
		for (p = (unsigned int*) 0x779700; (int) p < 0x7798c0; p += 0xe) {
			if (*p == (unsigned int) -1 || *p != *(unsigned int*) 0x67d370)
				continue;
			ent = (unsigned short*) gm_QueryEntities(*(int*) (a1 + 0x14), 1, 0, p[-8]);
			if (ent == 0)
				break;
			if (*(unsigned int*) (ent + 0xe) >= 4)
				cat = 0;
			else
				cat = *(unsigned int*) (ent + 0xe) + 1;
			cm_BeginPacketFieldDelta((int) ent, *(int*) (ent + 1));
			cm_AppendCommandSyncField(4, 1, (int) ((char*) ent - cm_PacketDeltaBase) + 0x1c, &cat);
			cm_SendSetAttribute();
			*(int*) (ent + 0xe) = cat;
		}
	}
	return found;
}
