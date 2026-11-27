#include "client_data.h"
#include "game_data.h"
extern unsigned char g_773dd4;
extern int g_773dd8;
extern char* g_7747b8;
#pragma pack(push, 1)
typedef struct { unsigned char unknown00[0x243]; unsigned int period; unsigned char unknown247[6]; } Building5744c0;
#pragma pack(pop)
extern char* gm_CityEntity;
char __cdecl d3_ComputeObjectBoundingSphere(int, int, void*, void*);
int __cdecl fcn_00415300(int);
int __cdecl sb_PlayVoice(int, int, int, int, int, int, int);
int __cdecl evt_FindScriptById(int);
int __cdecl evt_LoadGfxScript(char*);
void __cdecl evt_CallScriptFunction(int, int, ...);
int __cdecl evt_RequestScriptExit(int);
void __cdecl evt_RunGfxScript(int);
void __cdecl d3_VisitSceneObjects(int, int, int, int, void*);
char __cdecl d3_DestroyObject(int);
void __cdecl d3_SetSubtreeVisible(int, int);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_RemoveSubTreeFromCellTree(int, int);
void __cdecl fcn_004550e0(int, int);
void __cdecl d3_TransformPoint(char*, char*, float*);
void __cdecl rd_ConnectBuildingToSupermap(int, int);
int __cdecl cm_GetCommandStatus(int);
int __cdecl cm_GetCommandResult(int);
void __cdecl cm_BeginPacketFieldDelta(void*, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
int __cdecl cm_RequestAllocRaum(unsigned char, int, int, int);
int __cdecl cm_RequestMoveCredits(int, int, char, int);
void __cdecl cm_RequestChangeAttribute();
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
int __cdecl cm_SendSetHE(int, char*);
void __cdecl cm_RequestSysMessage(int, void*);
void __cdecl cm_RequestDestroyBuilding(int);
void __cdecl fcn_005001e0(void*, int);
void __cdecl gm_AddTime(void*, int, int, int);
int __cdecl gm_CompareGameTime(int*, int*);
int __cdecl gm_GetSeason(int);
void __cdecl fcn_005015e0(void*, int, int, int);
int __cdecl fcn_00509570(int);
int __cdecl gm_CalcWorkMinutesBetween(int*, int*);
int __cdecl gm_CreditCityTreasury(int);
int __cdecl d3_BindEntitySceneObject(int, void*, int);
void __cdecl d3_ApplySeasonTextureSet(int);
void __cdecl fcn_0052d9d0(void*);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, int, char*);
void __cdecl he_FreeAction(int);
void __cdecl fcn_00573e10(int);
int __cdecl d3_CountBuildStageMeshes();
int __cdecl he_CreateGebaeudeSceneModel(void*, void*, void*, void*, void*);
void __cdecl d3_ReleaseUnusedSceneObjects();
int __cdecl fcn_005985f0(void*, int);
int __cdecl fcn_00508e40(int);
int __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_0064d228();
int __cdecl fcn_0064d41a(char*, char*, ...);
#include "Develop/DieGildeAddOn/game/entity_record.h"
double __cdecl sqrt(double);

/* ADDRESS: GOLDTL 0x005744c0 */
void __cdecl gm_HandleHausbau(int a0)
{
	int buildAction;
	int v8;
	unsigned char v9;
	int v11;
	int v13;
	int v24;
	int v31;
	int v27;
	unsigned char* v14;
	int savedContext;
	float v29;
	float v21;
	unsigned char* v15;
	float v17[4];
	char v20[14];
	int v36;
	char v16[0x54];
	int v18[33];
	char v19[128];
	char messageText[0x200];

	buildAction = a0;
	savedContext = d3_CurrentContextIndex;
	v15 = 0;
	if (*(int*) (buildAction + 0x84) != -1 && !cm_GetCommandStatus(*(int*) (buildAction + 0x84))) {
		return;
	}
	*(int*) (buildAction + 0x84) = -1;
	v8 = *(int*) (buildAction + 0x70) + 2;
	switch (v8) {
	case 2:
		if (gm_CompareGameTime((void*) (buildAction + 0x52), (void*) &gm_GameTime) > 0
			|| !(*(unsigned char*) (buildAction + 0x78) & 2)) {
			break;
		}
		if (*(int*) (buildAction + 0xac) != *(int*) ((int) gm_CityEntity + 4)) {
			v8 = fcn_00508e40(*(int*) (buildAction + 0xac));
			if (v8) {
				*(int*) (buildAction + 0xcc) = cm_RequestMoveCredits(-1, *(int*) (buildAction + 0xac),
					(v8 & 0xffffff00) | g_773d75, *(int*) (buildAction + 0xb4));
				v8 = fcn_00509570(v8);
				if (v8) {
					*(int*) (v8 + 0x54) = *(int*) (v8 + 0x54) + *(int*) (buildAction + 0xb4);
				}
			}
			else {
LfailB:
				*(int*) (buildAction + 0x84) = cm_SendSetHE(-1, (void*) buildAction);
				return;
			}
		}
		else {
			*(int*) (buildAction + 0xcc) = gm_CreditCityTreasury(*(int*) (buildAction + 0xb4));
		}
		*(int*) (buildAction + 0x84) = cm_SendSetHE(*(int*) (buildAction + 0x70) + 1, (void*) buildAction);
		return;

	case 3:
		*(int*) (buildAction + 0x84) = -1;
		if (*(unsigned char*) (buildAction + 0x78) & 4) {
			break;
		}
		if (!cm_GetCommandStatus(*(int*) (buildAction + 0xcc))) {
			break;
		}
		if (cm_GetCommandStatus(*(int*) (buildAction + 0xcc)) == 2) {
			*(int*) (buildAction + 0x84) = cm_SendSetHE(-1, (void*) buildAction);
			return;
		}
		*(int*) (buildAction + 0x84) = cm_SendSetHE(*(int*) (buildAction + 0x70) + 1, (void*) buildAction);
		return;

	case 4:
		if (!(*(unsigned char*) (buildAction + 0x78) & 2)) {
			break;
		}
		v13 = cm_RequestAllocRaum((v8 & 0xffffff00) | *(unsigned char*) (buildAction + 0xb0),
			*(int*) (buildAction + 0xac), 0, 1);
		*(int*) (buildAction + 0xcc) = v13;
		*(int*) (buildAction + 0x84) = cm_SendSetHE(*(int*) (buildAction + 0x70) + 1, (void*) buildAction);
		return;

	case 5:
		*(int*) (buildAction + 0x84) = -1;
		if (*(unsigned char*) (buildAction + 0x78) & 4) {
			break;
		}
		if (!cm_GetCommandStatus(*(int*) (buildAction + 0xcc))) {
			break;
		}
		if (cm_GetCommandStatus(*(int*) (buildAction + 0xcc)) == 2) {
			goto LfailB;
		}
		v15 = (unsigned char*) cm_GetCommandResult(*(int*) (buildAction + 0xcc));
		if (v15) {
			*(int*) (buildAction + 0xb8) = *(int*) (v15 + 1);
			*(int*) (buildAction + 0x10) = *(int*) (v15 + 1);
		}
		else {
			*(int*) (buildAction + 0x84) = cm_SendSetHE(-1, (void*) buildAction);
			return;
		}
		*(int*) (buildAction + 0x84) = cm_SendSetHE(*(int*) (buildAction + 0x70) + 1, (void*) buildAction);
		return;

	case 6:
		*(int*) (buildAction + 0x84) = -1;
		fcn_005015e0(&v15, 0, 0, *(int*) (buildAction + 0xb8));
		if (!v15) {
			*(int*) (buildAction + 0x70) = -1;
			return;
		}
		v8 = he_CreateGebaeudeSceneModel((void*) (buildAction + 0xe4), (void*) (buildAction + 0xd4), (void*) v15,
			(void*) (buildAction + 0xf0), (void*) buildAction);
		if (!v8) {
			*(int*) (buildAction + 0x84) = cm_SendSetHE(-1, (void*) buildAction);
			d3_SelectSceneContext(savedContext, 1);
			return;
		}
		d3_BindEntitySceneObject(*(int*) (v15 + 0x61), v15, 2);
		v8 = *(unsigned char*) v15;
		v27 = (int) &((Building5744c0*) lpGebaeudePROT)[v8];
		if (g_774800) {
			*(int*) (buildAction + 0xc4) = d3_CountBuildStageMeshes(buildAction);
			*(int*) (buildAction + 0xc0) = 10;
		}
		else {
			v11 = d3_CountBuildStageMeshes(buildAction);
			*(int*) (buildAction + 0xc4) = v11;
			*(int*) (buildAction + 0xc0) = ((Building5744c0*) v27)->period * 0x3fc / v11;
		}
		*(int*) (buildAction + 0xc8) = 0;
		gm_AddTime((void*) (buildAction + 0x52), 0, 1, 0);
		*(int*) (buildAction + 0x70) = *(int*) (buildAction + 0x70) + 1;
		return;

	case 7:
		*(int*) (buildAction + 0x84) = -1;
		d3_SelectSceneContext(0, 1);
		fcn_005015e0(&v15, 0, 0, *(int*) (buildAction + 0xb8));
		if (!v15 || !fcn_005985f0(v16, (int) v15)) {
			*(int*) (buildAction + 0x84) = cm_SendSetHE(-1, (void*) buildAction);
			d3_SelectSceneContext(savedContext, 1);
			return;
		}
		v13 = 0;
		v21 = 1e+35f;
		v29 = 0.0f;
		v11 = 0;
		do {
			v14 = (unsigned char*) (v11 + (int) lpGebaeudeINST);
			if (v14 != v15 && *v14 && (v24 = *(int*) (v14 + 0x61)) != 0) {
				d3_TransformPoint((char*) v24, (char*) (v24 + 0x4c), v17);
				v17[0] = v17[0] - *(float*) (v16 + 0x40);
				v17[1] = v17[1] - *(float*) (v16 + 0x44);
				v17[2] = v17[2] - *(float*) (v16 + 0x48);
				v29 = (float) sqrt(v17[2] * v17[2] + v17[1] * v17[1] + v17[0] * v17[0]);
				if (v29 < v21
					&& d3_FindSceneObject(*(int*) (v11 + (int) lpGebaeudeINST + 0x61),
						0x100, 0, 0x68149c)) {
					v13 = v11 + (int) lpGebaeudeINST;
					v21 = v29;
				}
			}
			v11 += 0xa9;
		} while (v11 < 0xa900);
		if (!v13) {
			*(int*) (buildAction + 0x84) = cm_SendSetHE(-1, (void*) buildAction);
			d3_SelectSceneContext(savedContext, 1);
			return;
		}
		for (v11 = 0; v11 < 33; v11++) {
			v18[v11] = 0;
		}
		d3_VisitSceneObjects(g_67a370, *(int*) (v16 + 0x50), 0x2c0, 0x5982d0, v18);
		*(unsigned char*) (buildAction + 0xd0) = 0;
		v21 = 0.0f;
		if (v18[32] > 0) {
			v11 = 0;
			do {
				v8 = v18[v11];
				v14 = (unsigned char*) d3_FindSceneObject(*(int*) (v13 + 0x61), 0x100, 0, 0x68149c);
				if (v8 && *(int*) (v8 + 0x218) != 1 && v14) {
					v24 = evt_LoadGfxScript((char*) 0x6a7dd4);
					if (v24) {
						evt_CallScriptFunction(v24, 4, v14, v8, 0x573d90, buildAction);
						*(int*) (v24 + 0x104) = 0;
						*(int*) (v24 + 0xc8c) = 1;
						evt_RunGfxScript(v24);
					}
					*(unsigned char*) (buildAction + 0xd0) = *(unsigned char*) (buildAction + 0xd0) + 1;
				}
				v11 += 1;
			} while (v11 < v18[32]);
		}
		*(pos14_7f4c00*) (buildAction + 0x52) = gm_GameTime;
		gm_AddTime((void*) (buildAction + 0x52), 0, 10, 0);
		*(int*) (buildAction + 0x70) = *(int*) (buildAction + 0x70) + 1;
		d3_SelectSceneContext(savedContext, 1);
		return;

	case 8:
		*(int*) (buildAction + 0x84) = -1;
		gm_AddTime((void*) (buildAction + 0x52), 0, 0x14, 0);
		if (*(unsigned char*) (buildAction + 0xd0)) {
			break;
		}
		d3_SelectSceneContext(0, 1);
		fcn_005015e0(&v15, 0, 0, *(int*) (buildAction + 0xb8));
		if (!fcn_005985f0(v16, (int) v15)) {
			*(int*) (buildAction + 0x84) = cm_SendSetHE(-1, (void*) buildAction);
			d3_SelectSceneContext(savedContext, 1);
			return;
		}
		for (v11 = 0; v11 < 33; v11++) {
			v18[v11] = 0;
		}
		d3_VisitSceneObjects(g_67a370, *(int*) (v16 + 0x50), 0x2c0, 0x5982d0, v18);
		for (v11 = 0; v11 < v18[32]; v11++) {
			if (g_773dd8) {
				d3_RemoveSubTreeFromCellTree(v18[v11], g_773dd8);
			}
			d3_DestroyObject(v18[v11]);
		}
		*(int*) (buildAction + 0x60) = gm_GameTime.a;
		*(int*) (buildAction + 0x64) = gm_GameTime.b;
		*(int*) (buildAction + 0x68) = gm_GameTime.c;
		*(unsigned short*) (buildAction + 0x6c) = (unsigned short) gm_GameTime.d;
		*(int*) (buildAction + 0x52) = gm_GameTime.a;
		*(int*) (buildAction + 0x56) = gm_GameTime.b;
		*(int*) (buildAction + 0x5a) = gm_GameTime.c;
		*(unsigned short*) (buildAction + 0x5e) = (unsigned short) gm_GameTime.d;
		gm_AddTime((void*) (buildAction + 0x52), 0, 10, 0);
		*(int*) (buildAction + 0x70) = *(int*) (buildAction + 0x70) + 1;
		*(int*) (buildAction + 0xb4) = 0;
		d3_SelectSceneContext(savedContext, 1);
		return;

	case 9:
		v8 = gm_CalcWorkMinutesBetween((void*) (buildAction + 0x60), (void*) &gm_GameTime);
		v36 = v8 + *(int*) (buildAction + 0xb4);
		if (v36 < *(int*) (buildAction + 0xc0)) {
			gm_AddTime((void*) (buildAction + 0x52), 0, 0x1e, 0);
			return;
		}
		*(int*) (buildAction + 0x60) = *(int*) (buildAction + 0x52);
		*(int*) (buildAction + 0x64) = *(int*) (buildAction + 0x56);
		*(int*) (buildAction + 0x68) = *(int*) (buildAction + 0x5a);
		*(unsigned short*) (buildAction + 0x6c) = *(unsigned short*) (buildAction + 0x5e);
		if (!v15) {
			fcn_005015e0(&v15, 0, 0, *(int*) (buildAction + 0xb8));
		}
		if (*(int*) (buildAction + 0xbc) == -1 && *(int*) (buildAction + 0xc8) >= 2) {
			d3_SelectSceneContext(0, 1);
			fcn_0064d41a(v19, (char*) 0x6a7d60, *(int*) (buildAction + 4));
			v8 = d3_FindSceneObject(0, 0x1c0, 0, v19);
			d3_TransformPoint((char*) v8, (char*) (v8 + 0x4c), (float*) v20);
			v21 = 1e+35f;
			v13 = 0;
			v11 = 0;
			do {
				v14 = (unsigned char*) (v11 + (int) lpGebaeudeINST);
				if (v14 != v15 && *v14 && (v24 = *(int*) (v14 + 0x61)) != 0) {
					d3_TransformPoint((char*) v24, (char*) (v24 + 0x4c), v17);
					v17[0] = v17[0] - *(float*) (v20 + 0);
					v17[1] = v17[1] - *(float*) (v20 + 4);
					v17[2] = v17[2] - *(float*) (v20 + 8);
					v29 = (float) sqrt(v17[2] * v17[2] + v17[1] * v17[1] + v17[0] * v17[0]);
					if (v29 < v21
						&& (v24 = d3_FindSceneObject(*(int*) (v11 + (int) lpGebaeudeINST + 0x61),
							0x100, 0, 0x68149c)) != 0) {
						v21 = v29;
						v13 = v24;
					}
				}
				v11 += 0xa9;
			} while (v11 < 0xa900);
			if (v13 && v8 && (v24 = evt_LoadGfxScript((char*) 0x6a7db8)) != 0) {
				evt_CallScriptFunction(v24, 3, v8, v13, 2);
				*(int*) (v24 + 0xc8c) = 1;
				*(int*) (v24 + 0x104) = 0;
				*(int*) (buildAction + 0xbc) = *(int*) (v24 + 0x100);
				evt_RunGfxScript(v24);
			}
			d3_SelectSceneContext(savedContext, 1);
		}
		v11 = *(int*) (buildAction + 0xc0);
		*(int*) (buildAction + 0xc8) = *(int*) (buildAction + 0xc8) + v36 / v11;
		*(int*) (buildAction + 0xb4) = v36 % v11;
		gm_AddTime((void*) (buildAction + 0x52), 0, v11, 0);
		if (d3_CurrentContextIndex == 0) {
			if (*(int*) (buildAction + 0xc8) <= *(int*) (buildAction + 0xc4)) {
				fcn_00573e10(buildAction);
			}
			if (*(int*) (buildAction + 0xc8) == 2 && (*(unsigned char*) (buildAction + 0x78) & 2)) {
				for (v11 = 0; v11 < 31; v11++) {
					((int*) v19)[v11] = 0;
				}
				cm_RequestSysMessage(0xc, v19);
			}
		}
		if (*(int*) (buildAction + 0xc8) > *(int*) (buildAction + 0xc4)) {
			d3_SelectSceneContext(0, 1);
			if (*(int*) (buildAction + 0xbc) != -1) {
				v8 = evt_FindScriptById(*(int*) (buildAction + 0xbc));
				if (v8) {
					evt_RequestScriptExit(v8);
				}
				*(int*) (buildAction + 0xbc) = -1;
			}
			if (savedContext) {
				fcn_00415300(*(int*) (v15 + 0x61));
				*(unsigned char*) (*(int*) (v15 + 0x61) + 0x217) |= 1;
			}
			fcn_00573e10(buildAction);
			if (*(int*) (v15 + 0x61)) {
				v8 = gm_GetSeason((int) &gm_GameTime);
				if (v8 == 1) {
					g_773dd4 = (char) v8;
				}
				else if (v8 == 0) {
					g_773dd4 = 0;
				}
				else if (v8 == 2) {
					g_773dd4 = (char) v8;
				}
				else if (v8 == 3) {
					g_773dd4 = (char) v8;
				}
				d3_ApplySeasonTextureSet(*(int*) (v15 + 0x61));
			}
			if (g_773dd8) {
				fcn_004550e0(*(int*) (v15 + 0x61), g_773dd8);
			}
			v8 = *(int*) (v15 + 0x61);
			if (v8 && *(int*) (v8 + 0x218) == 1) {
				d3_SetSubtreeVisible(v8, 1);
			}
			v9 = g_7f4ca2[*(unsigned short*) (v15 + 0x27)].kind;
			if (v9 == 6 || v9 == 5 || v9 == 7) {
				fcn_0052d9d0((void*) v15);
			}
			d3_ReleaseUnusedSceneObjects();
			if (*(int*) (*(int*) (v15 + 0x61) + 0x1ec)) {
				if (d3_ComputeObjectBoundingSphere(*(int*) (v15 + 0x61), (int) d3_ActiveCamera, v17, &v21)) {
					v31 = (int) (v21 * 1.8);
					v8 = evt_LoadGfxScript((char*) 0x6a7da0);
					if (v8) {
						evt_CallScriptFunction(v8, 6, (int) v17[0], (int) v17[1], (int) v17[2],
							(int) v21, v31, *(int*) (v15 + 0x61));
						*(int*) (v8 + 0x104) = 0;
					}
				}
			}
			rd_ConnectBuildingToSupermap(*(int*) (v15 + 0x61), *(unsigned char*) v15);
			if (*(unsigned char*) (buildAction + 0x78) & 2) {
				cm_RequestChangeBits(*(int*) (v15 + 1), 0x5a, 2, 0, 1);
				if (*(unsigned char*) v15 >= 4 && *(unsigned char*) v15 <= 7) {
					*(int*) v20 = gm_GameTime.a;
					*(int*) (v20 + 4) = gm_GameTime.b;
					*(int*) (v20 + 8) = gm_GameTime.c;
					*(unsigned short*) (v20 + 12) = (unsigned short) gm_GameTime.d;
					cm_BeginPacketFieldDelta(v15, *(int*) (v15 + 1));
					cm_AppendPacketFieldDelta(1, 0xe, 0x69, v20);
					cm_RequestChangeAttribute();
				}
				if (g_7f4ca2[*(unsigned short*) (v15 + 0x27)].kind == 6) {
					if (*(unsigned char*) v15 >= 4 && *(unsigned char*) v15 <= 7) {
						fcn_0051af00(messageText, 0x1c2f, v15);
						fcn_00545e80(((ENTITY_RECORD*) g_7f4ca0)[*(unsigned short*) (v15 + 0x27)].entity_id,
							*(int*) (buildAction + 0x10), messageText, 1, 0x5f6, *(int*) (v15 + 1), -1, 0,
							(char*) 0x6a7d8c);
					}
					else {
						fcn_0051af00(messageText, 0x1c27, v15);
						fcn_00545e80(((ENTITY_RECORD*) g_7f4ca0)[*(unsigned short*) (v15 + 0x27)].entity_id,
							*(int*) (buildAction + 0x10), messageText, 0, 0x5f6, *(int*) (v15 + 1), -1, 0,
							(char*) 0x6a7d8c);
					}
					sb_PlayVoice((int) g_7747b8, 0x6a7d7c, 1, 0x3f, 0x7f, 0, 0);
				}
				v9 = g_7f4ca2[*(unsigned short*) (v15 + 0x27)].kind;
				if (v9 == 6 || v9 == 5) {
					v27 = (int) (g_7f4ca0 + 4);
					do {
						if ((*(char*) (v27 - 2) == 6 || *(char*) (v27 - 2) == 7)
							&& *(int*) v27 != ((ENTITY_RECORD*) g_7f4ca0)[*(unsigned short*) (v15 + 0x27)].entity_id) {
							fcn_0051af00(messageText, 0x1c30, *(unsigned short*) (v15 + 0x27),
								(void*) (*(unsigned char*) v15 * 0xe + 0x48e));
							fcn_00545e80(*(int*) v27, -1, messageText, 0, 0x607, *(int*) (v15 + 1), -1, 0,
								(char*) 0x6a7d68);
						}
						v27 += sizeof(ENTITY_RECORD);
					} while (v27 < (int) (g_7f4ca0 + 0x65404));
				}
				for (v11 = 0; v11 < 31; v11++) {
					((int*) v19)[v11] = 0;
				}
				cm_RequestSysMessage(0xc, v19);
			}
			v9 = *(unsigned char*) v15;
			if (v9 >= 4 && v9 <= 7) {
				v27 = (int) &((ENTITY_RECORD*) g_7f4ca0)[*(unsigned short*) (v15 + 0x27)].unk_170;
				v8 = *(int*) v27;
				if (!v8 || *(unsigned char*) v8 > (unsigned char) v9) {
					*(int*) v27 = (int) v15;
				}
			}
			fcn_005001e0((void*) ((int) &((ENTITY_RECORD*) g_7f4ca0)[*(unsigned short*) (v15 + 0x27)]),
				(int) v15);
			d3_SelectSceneContext(savedContext, 1);
			*(int*) (buildAction + 0x7c) = 0;
			he_FreeAction(buildAction);
			return;
		}
		break;

	case 0:
	case 1:
		fcn_005015e0(&v15, 0, 0, *(int*) (buildAction + 0xb8));
		d3_SelectSceneContext(0, 1);
		if (*(int*) (buildAction + 0xbc) != -1) {
			v8 = evt_FindScriptById(*(int*) (buildAction + 0xbc));
			if (v8) {
				evt_RequestScriptExit(v8);
			}
			*(int*) (buildAction + 0xbc) = -1;
		}
		*(int*) (buildAction + 0xc8) = *(int*) (buildAction + 0xc4) + 1;
		fcn_00573e10(buildAction);
		if ((*(unsigned char*) (buildAction + 0x78) & 2) && v15) {
			cm_RequestDestroyBuilding(*(int*) (v15 + 1));
			for (v11 = 0; v11 < 31; v11++) {
				((int*) v19)[v11] = 0;
			}
			cm_RequestSysMessage(0xc, v19);
		}
		d3_SelectSceneContext(savedContext, 1);
		he_FreeAction(buildAction);
		return;
	}
	return;
}
