extern char gm_EntityIdField[];
extern char g_6a68b0[];
extern int cm_PacketDeltaBase;

int __cdecl gm_LookupEntityRecordById(int a0);
void __cdecl cm_BeginPacketFieldDelta(char* a0, int a1);
void __cdecl cm_AppendCommandSyncField(int a0, int a1, int a2, int* a3);
void __cdecl cm_SendSetAttribute(void);
int __cdecl gm_GetEntityRelation(int a0, int a1);
void __cdecl cm_RequestCopyEntityData(int a0, int a1, int a2, int a3);
void __cdecl cm_RequestChangePlayerHe(int a0, int a1, int a2);
void __cdecl cm_RequestCancelEntityEvent(int a0);
int __cdecl gm_FindFallbackPublicBuilding(char* a0, int* a1, int* a2);
void __cdecl ch_StartMovement(int a0, int a1, int a2, int a3, int a4, char* a5);
void __cdecl he_FreeAction(int a0);

/* ADDRESS: GOLDTL 0x00566110 */
/* ADDRESS: GOLDDE 0x0054c220 */
void __cdecl he_HandleEntlassen(int event)
{
	char* ent;
	int v6;
	int v7;
	int v5;
	int v8;
	unsigned short v2;

	v6 = 0;
	switch (*(int*) (event + 0x70)) {
	case 0:
		ent = (char*) gm_LookupEntityRecordById(*(int*) (event + 0xac));
		if (ent == 0 || *(char*) (ent + 8) == 0) {
			*(int*) (event + 0x70) = -1;
			return;
		}
		v6 = 0;
		if (*(int*) (ent + 0x16c) != 0) {
			cm_BeginPacketFieldDelta(ent, *(int*) (ent + 4));
			cm_AppendCommandSyncField(4, 1, (int) ent - cm_PacketDeltaBase + 0x16c, &v6);
			cm_SendSetAttribute();
			if (gm_GetEntityRelation(*(unsigned short*) (*(int*) (ent + 0x16c) + 0x27), *(unsigned short*) ent) > -0x1e) {
				v6 = -0x1e - gm_GetEntityRelation(*(unsigned short*) (*(int*) (ent + 0x16c) + 0x27), *(unsigned short*) ent);
			}
			v2 = *(unsigned short*) (*(int*) (ent + 0x16c) + 0x27);
			v5 = v6;
			cm_RequestCopyEntityData(*(int*) (v2 * 0x21c + (int) &gm_EntityIdField), *(int*) (ent + 4), v5, 1);
		}
		cm_RequestChangePlayerHe(*(int*) (ent + 4), 0, 0);
		cm_RequestCancelEntityEvent(*(int*) (ent + 4));
		if (gm_FindFallbackPublicBuilding(ent, &v8, &v7) != 0) {
			if (v7 != -1) {
				ch_StartMovement(*(int*) (ent + 4), v8, v7, 0, 0, (char*) &g_6a68b0);
			} else {
				ch_StartMovement(*(int*) (ent + 4), v8, -1, 0, 1, (char*) &g_6a68b0);
			}
		}
		he_FreeAction(event);
		break;
	case -2:
	case -1:
		he_FreeAction(event);
		break;
	}
}
