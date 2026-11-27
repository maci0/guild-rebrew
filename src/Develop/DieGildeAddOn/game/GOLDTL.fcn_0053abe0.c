extern unsigned char g_773d75;
extern char g_6a3bb4[];
/* SIZE 0x10: record copied from g_6a3bb4 */
typedef struct {
	int w[4];
} CIVIC_BLK16;

char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int id);
char* __cdecl fcn_00502cd0(int a, int b, int c, int d, ...);
void __cdecl gm_AssignBuildingOwner(char* e, int a, int b);
void __cdecl d3_UpdateEntityStageMeshes(char* e, char* q, int a);
int __cdecl cm_SendSellObjekt(int a, int b, int c, int d, unsigned char k, int n);
void __cdecl fcn_004c6090(char* e, int a, int b, int c);
void __cdecl cm_BeginCommandSync(void);
void __cdecl cm_EndCommandSync(void);
char* __cdecl cm_AreQueuedCommandsDone(void);
void __cdecl cm_StepCommandQueue(void);

/* ADDRESS: GOLDTL 0x0053abe0 */
void __cdecl gm_InitCivicBuildings(unsigned int ownerSlot)
{
	char* bld;
	char* slot;
	int n;

	bld = gm_StartFilteredEntitySearch(1, 0, 6);
	if (bld != 0) {
		*(CIVIC_BLK16*) (bld + 5) = *(CIVIC_BLK16*) g_6a3bb4;
		gm_AssignBuildingOwner(bld, ownerSlot, ownerSlot);
		slot = fcn_00502cd0(*(int*) (bld + 0x5d), 1, 0, 0x13);
		if (slot != 0) {
			d3_UpdateEntityStageMeshes(bld, slot, ownerSlot);
		}
		cm_SendSellObjekt(*(int*) (bld + 1), -1, 0x15, 1, g_773d75, 0);
		cm_SendSellObjekt(*(int*) (bld + 1), -1, 0x17, 1, g_773d75, 0);
		cm_SendSellObjekt(*(int*) (bld + 1), -1, 0x18, 1, g_773d75, 0);
		cm_SendSellObjekt(*(int*) (bld + 1), -1, 0x14, 1, g_773d75, 0);
	}
	bld = gm_StartFilteredEntitySearch(1, 0, 0x20);
	if (bld != 0) {
		*(short*) (bld + 0x25) = (short) ownerSlot;
		*(short*) (bld + 0x27) = (short) ownerSlot;
		n = 3;
		do {
			fcn_004c6090(bld, 0, 10, 0);
			n--;
		} while (n);
		slot = fcn_00502cd0(*(int*) (bld + 0x5d), 2, 6, 0, 0x2a);
		if (slot != 0) {
			cm_BeginCommandSync();
			cm_SendSellObjekt(*(int*) (slot + 2), -1, 0x1d0, 0x19, g_773d75, 0);
			cm_EndCommandSync();
			while (!cm_AreQueuedCommandsDone()) {
				cm_StepCommandQueue();
			}
		}
	}
	bld = gm_StartFilteredEntitySearch(1, 0, 0x2a);
	if (bld != 0) {
		gm_AssignBuildingOwner(bld, ownerSlot, ownerSlot);
		slot = fcn_00502cd0(*(int*) (bld + 0x5d), 2, 6, 0, 0x2a);
		if (slot != 0) {
			cm_BeginCommandSync();
			cm_SendSellObjekt(*(int*) (slot + 2), -1, 0x1d0, 0x14, g_773d75, 0);
			cm_SendSellObjekt(*(int*) (slot + 2), -1, 0x1d7, 0x0f, g_773d75, 0);
			cm_SendSellObjekt(*(int*) (slot + 2), -1, 0x1d6, 0x0f, g_773d75, 0);
			cm_SendSellObjekt(*(int*) (slot + 2), -1, 0x158, 10, g_773d75, 0);
			cm_EndCommandSync();
			while (!cm_AreQueuedCommandsDone()) {
				cm_StepCommandQueue();
			}
		}
	}
	bld = gm_StartFilteredEntitySearch(1, 0, 0x1e);
	if (bld != 0) {
		gm_AssignBuildingOwner(bld, ownerSlot, ownerSlot);
	}
	bld = gm_StartFilteredEntitySearch(1, 0, 0x1f);
	if (bld != 0) {
		gm_AssignBuildingOwner(bld, ownerSlot, ownerSlot);
	}
	bld = gm_StartFilteredEntitySearch(1, 0, 0x12);
	if (bld != 0) {
		gm_AssignBuildingOwner(bld, ownerSlot, ownerSlot);
	}
	bld = gm_StartFilteredEntitySearch(1, 0, 0x14);
	if (bld != 0) {
		gm_AssignBuildingOwner(bld, ownerSlot, ownerSlot);
		cm_SendSellObjekt(*(int*) (bld + 1), -1, 0xf7, 1, g_773d75, 0);
	}
	bld = gm_StartFilteredEntitySearch(1, 0, 0x32);
	if (bld != 0) {
		gm_AssignBuildingOwner(bld, ownerSlot, ownerSlot);
		slot = fcn_00502cd0(*(int*) (bld + 0x5d), 2, 6, 0, 0x2a);
		if (slot != 0) {
			cm_BeginCommandSync();
			cm_SendSellObjekt(*(int*) (slot + 2), -1, 0x1cb, 10, g_773d75, 0);
			cm_SendSellObjekt(*(int*) (slot + 2), -1, 0x1cc, 10, g_773d75, 0);
			cm_SendSellObjekt(*(int*) (slot + 2), -1, 0x1d0, 10, g_773d75, 0);
			cm_EndCommandSync();
			while (!cm_AreQueuedCommandsDone()) {
				cm_StepCommandQueue();
			}
		}
	}
	bld = gm_StartFilteredEntitySearch(1, 0, 0x21);
	if (bld != 0) {
		gm_AssignBuildingOwner(bld, ownerSlot, ownerSlot);
		fcn_00502cd0(*(int*) (bld + 0x5d), 2, 6, 0, 0x2a);
	}
	bld = gm_StartFilteredEntitySearch(1, 0, 0x19);
	if (bld != 0) {
		gm_AssignBuildingOwner(bld, ownerSlot, ownerSlot);
		fcn_00502cd0(*(int*) (bld + 0x5d), 2, 6, 0, 0x2a);
	}
	bld = gm_StartFilteredEntitySearch(1, 0, 0x34);
	if (bld != 0) {
		gm_AssignBuildingOwner(bld, ownerSlot, ownerSlot);
		slot = fcn_00502cd0(*(int*) (bld + 0x5d), 2, 6, 0, 0x2a);
		if (slot != 0) {
			cm_BeginCommandSync();
			cm_SendSellObjekt(*(int*) (slot + 2), -1, 0x1cb, 10, g_773d75, 0);
			cm_SendSellObjekt(*(int*) (slot + 2), -1, 0x1cc, 10, g_773d75, 0);
			cm_SendSellObjekt(*(int*) (slot + 2), -1, 0x1d0, 10, g_773d75, 0);
			cm_EndCommandSync();
			while (!cm_AreQueuedCommandsDone()) {
				cm_StepCommandQueue();
			}
		}
	}
	bld = gm_StartFilteredEntitySearch(1, 0, 0x36);
	if (bld == 0) {
		return;
	}
	gm_AssignBuildingOwner(bld, ownerSlot, ownerSlot);
	fcn_00502cd0(*(int*) (bld + 0x5d), 2, 6, 0, 0x2a);
}
