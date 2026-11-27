extern unsigned char g_773d75;
extern int d3_CurrentContextIndex;
extern int gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern float g_6628a0;
extern float g_664154;



extern int lpGebaeudePROT;
extern char g_6a6560[];
extern char g_6a654c[];
extern char g_6a6538[];
extern char g_68bef4[];
extern char g_677640[];
#include "Develop/DieGildeAddOn/game/building_prototype.h"
int __cdecl cm_GetCommandStatus(int);
int __cdecl cm_GetCommandResult(int);
void *__cdecl gm_GetEntityTableEntry(void *);
void __cdecl he_AssignActionSlot(int, int, int, void *);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void *__cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl ch_StartMovement(int, int, int, int, int, char *);
void *__cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_AddTime(void *, int, int, int);
int __cdecl he_DetectNearbyPatrolAction(void *);
void __cdecl cm_RequestPlayAnimation(int, char *, int);
int __cdecl gm_TryRecordCrime(int, int, int, int, int);
int __cdecl gm_CompareGameTime(void *, int *);
float __cdecl gm_CalcSkillDuelScore(void *, void *, int);
float __cdecl gm_RandomFloat01(void);
int __cdecl gm_HasActiveSpecialObject(void *, int);
void __cdecl io_FormatTextBuffer(char *, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char *, int, int, int, int, int, char *);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl gm_ModifyHealth(int, int);
void __cdecl he_PostEntityMessage(int, int, char *, int, int, char *);
void *__cdecl he_StartHandlungSearch(int, int, int);
void __cdecl cm_RequestLinkEvidence(int, int);
void __cdecl cm_RequestKillSpieler(int, int);
void __cdecl he_FreeAction(void *);
void __cdecl d3_SelectSceneContext(int, int);
int __cdecl sb_PrepareVoice(int, char *);
void __cdecl d3snd_PlayObjectSound(int, int, int, int);
void *__cdecl d3_FindSceneObject(void *, int, int, char *);
void __cdecl d3_TransformPoint(char *, char *, float *);
void __cdecl cm_SendCopyEntityData(void *);
void __cdecl fcn_00418000(int, float *, int, float, float, float, float, float, float, float *, int, int, int);
void __cdecl d3_SpawnRockDebrisEffect(int, float *, int, float, float, float, float, float, float, float, float, int);
void __cdecl fcn_00417d00(int, float *, int, float, float, float, float, int);
int __cdecl gm_RandomMod(unsigned short);
#include "Develop/DieGildeAddOn/game/entity_record.h"
#pragma pack(push, 1)
typedef struct {
	int field_00;
	int field_04;
	int field_08;
	unsigned short field_0c;
} MSGCOLOR;
#pragma pack(pop)

/* ADDRESS: GOLDTL 0x00561380 */
void __cdecl he_RunSabotage(void *action)
{
	unsigned char *p;
	char text[0x400];
	unsigned char msg[0xf8];
	float pos[8];

	p = (unsigned char *)action;
	if (*(int *)(p + 0xc8) != -1 && !cm_GetCommandStatus(*(int *)(p + 0xc8)))
		return;
	switch (*(int *)(p + 0x70)) {
	case 0:
		{
			unsigned char *hand;
			unsigned char *e;

			if (*(int *)(p + 0xc8) != -1 && !cm_GetCommandStatus(*(int *)(p + 0xc8)))
				return;
			hand = (unsigned char *)cm_GetCommandResult(*(int *)(p + 0xc8));
			if (hand != 0) {
				e = (unsigned char *)gm_GetEntityTableEntry((unsigned char*)&((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*)(p + 8)]);
				if (e != 0)
					*(int *)(e + 0x28) = *(int *)(e + 0x28) + *(int *)(p + 0xd0);
				*(int *)(p + 0xc4) = *(int *)(hand + 4);
				he_AssignActionSlot(0, 0, *(unsigned short *)hand, p);
				cm_RequestTransferCurrencyNoKill(-1, *(int *)((unsigned char*)&((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*)(p + 8)] + 4), g_773d75, *(int *)(p + 0xd0));
				*(int *)(p + 0xc8) = -1;
				*(int *)(p + 0x70) = *(int *)(p + 0x70) + 1;
				return;
			}
			*(int *)(p + 0xc4) = -1;
		}
	label_56148f:
		*(int *)(p + 0x70) = -1;
		return;
	case 1:
		{
			unsigned char *r;

			r = (unsigned char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(p + 0xac));
			if (r == 0) {
				*(int *)(p + 0x70) = -1;
				return;
			}
			*(int *)(p + 0xc8) = ch_StartMovement(*(int *)(p + 0xc4), *(int *)(r + 1), -1, 0, 1, g_6a6560);
			*(int *)(p + 0x70) = *(int *)(p + 0x70) + 1;
			return;
		}
	case 2:
		{
			unsigned char *r;

			*(int *)(p + 0xc8) = -1;
			r = (unsigned char *)gm_LookupEntityRecordById(*(int *)(p + 0xc4));
			if (r == 0) {
				*(int *)(p + 0x70) = -1;
				return;
			}
			if (*(int *)(*(int *)(r + 0x184) + 0x128) == 0)
				goto label_561b4d;
			*(MSGCOLOR *)(p + 0x52) = *(MSGCOLOR *)&gm_GameTime;
			gm_AddTime((void *)(p + 0x52), 0, 4, 0);
			*(int *)(p + 0x70) = 2;
			return;
		}
	case 3:
		{
			unsigned char *r;
			unsigned char *q;

			r = (unsigned char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(p + 0xac));
			if (r == 0 || *(unsigned short *)(r + 0x27) == 0xffff)
				goto label_56148f;
			*(void **)pos = r;
			pos[1] = 4000.0f;
			*(void **)(pos + 2) = p;
			pos[3] = 0.0f;
			if (he_DetectNearbyPatrolAction(pos) != 0) {
				q = (unsigned char *)(p + 0x52);
				*(int *)(p + 0xc8) = gm_TryRecordCrime(0x18, 1,
					*(int *)((unsigned char*)&((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*)(p + 8)] + 4),
					*(int *)((unsigned char*)&((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*)(r + 0x27)] + 4),
					*(int *)(p + 0xac));
				*(int *)(q + 0x7a) = *(int *)(*(unsigned char **)(pos + 3) + 4);
				*(int *)(q + 0x1e) = 7;
				*(MSGCOLOR *)q = *(MSGCOLOR *)&gm_GameTime;
				return;
			}
			cm_RequestPlayAnimation(*(int *)(p + 0xc4), g_68bef4, 1);
			ch_StartMovement(*(int *)(p + 0xc4), *(int *)(p + 0x10), -1, 0, 1, g_6a6560);
			*(int *)(p + 0x70) = *(int *)(p + 0x70) + 1;
			return;
		}
	case 7:
		{
			unsigned char *r;
			unsigned char *e;
			unsigned char *hand;
			unsigned char *query;

			if (*(int *)(p + 0xc8) != -1 && !cm_GetCommandStatus(*(int *)(p + 0xc8)))
				return;
			r = (unsigned char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(p + 0xac));
			e = (unsigned char *)he_StartHandlungSearch(1, 1, *(int *)(p + 0xcc));
			if (r == 0 || e == 0 || *(int *)(e + 0xd4) != *(int *)(p + 4) || *(int *)(p + 0xc8) == -1)
				goto label_56148f;
			query = (unsigned char *)gm_LookupEntityRecordById(*(int *)(p + 0xcc));
			hand = (unsigned char *)cm_GetCommandResult(*(int *)(p + 0xc8));
			if (hand != 0 && query != 0)
				cm_RequestLinkEvidence(*(int *)hand, *(int *)(query + 4));
			*(int *)(p + 0x70) = 8;
			gm_AddTime((void *)(p + 0x52), 0, 10, 0);
			return;
		}
	case 8:
		{
			unsigned char *r;

			r = (unsigned char *)he_StartHandlungSearch(1, 1, *(int *)(p + 0xcc));
			if (r == 0) {
				*(int *)(p + 0x70) = -1;
				return;
			}
			if (*(int *)(r + 0xd4) == *(int *)(p + 4)) {
				gm_AddTime((void *)(p + 0x52), 0, 6, 0);
				return;
			}
			ch_StartMovement(*(int *)(p + 0xc4), *(int *)(p + 0x10), -1, 0, 1, g_6a6560);
			*(MSGCOLOR *)(p + 0x52) = *(MSGCOLOR *)&gm_GameTime;
			gm_AddTime((void *)(p + 0x52), 0, 4, 0);
			*(int *)(p + 0x70) = 6;
			return;
		}
	case 4:
		{
			unsigned char *q;
			float dist;
			unsigned char *recB;
			unsigned char *recA;
			unsigned char *r;
			unsigned char *v22;

			q = (unsigned char *)(p + 0x52);
			if (gm_CompareGameTime(q, &gm_GameTime) >= 0)
				return;
			*(unsigned char *)(p + 0xc2) = 0;
			r = (unsigned char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(p + 0xac));
			if (r == 0 || *(unsigned short *)(r + 0x27) == 0xffff)
				goto label_56148f;
			recA = (unsigned char*)&((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*)(r + 0x27)];
			recB = (unsigned char*)&((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*)(p + 8)];
			dist = gm_CalcSkillDuelScore(recB, recA, 2);
			if (!(gm_RandomFloat01() + dist >= 1.0f))
				goto label_561a7a;
			if (gm_HasActiveSpecialObject(recA, 0x2c0) == 0) {
			io_FormatTextBuffer(text, 0x1735, *(unsigned short *)recA, r);
			he_MessageBoxQuickjump(*(int *)(recB + 4), -1, text, 0, 0x5f0, *(int *)(r + 1), -1, 0, 0);
			if (*(unsigned short *)(r + 0x27) != 0xffff) {
				if (*(unsigned char *)(recA + 2) != 6 && *(unsigned char *)(recA + 2) != 7)
					cm_RequestCopyEntityData(*(int *)(recB + 4), *(int *)(recA + 4), -0x19, 1);
				else {
					io_FormatTextBuffer(text, 0x1736, r);
					he_MessageBoxQuickjump(*(int *)(recA + 4), -1, text, 0, 0x5f0, *(int *)(r + 1), -1, 0, g_6a654c);
				}
				gm_TryRecordCrime(0x18, 1,
					*(int *)((unsigned char*)&((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*)(p + 8)] + 4),
					*(int *)((unsigned char*)&((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*)(r + 0x27)] + 4),
					*(int *)(r + 1));
			}
			v22 = (unsigned char *)0x7f4ca4;
			do {
				if ((*(unsigned char *)(v22 - 2) == 6 || *(unsigned char *)(v22 - 2) == 7)
					&& *(int *)v22 != *(int *)(recA + 4)
					&& *(int *)v22 != *(int *)(recB + 4)) {
					io_FormatTextBuffer(text, 0x1737, *(unsigned short *)recA, r);
					he_MessageBoxQuickjump(*(int *)v22, -1, text, 0, 0x5f0, *(int *)(r + 1), -1, 0, 0);
				}
				v22 = v22 + 0x87 * 4;
			} while ((int)v22 < (int)0x85a0a4);
			*(int *)(p + 0x70) = *(int *)(p + 0x70) + 1;
			*(MSGCOLOR *)q = *(MSGCOLOR *)&gm_GameTime;
			gm_AddTime(q, 0, 10, 0);
			return;
			}
		label_561a7a:
			recA = (unsigned char*)&((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*)(r + 0x27)];
			recB = (unsigned char*)&((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*)(p + 8)];
			if (gm_HasActiveSpecialObject(recA, 0x2c0)) {
				gm_ModifyHealth(*(int *)(recB + 4), -1);
				if (*(unsigned char *)(recB + 2) == 6 || *(unsigned char *)(recB + 2) == 7) {
					io_FormatTextBuffer(text, 0x1013, *(unsigned short *)recA, r);
					he_PostEntityMessage(*(int *)(recB + 4), -1, text, 0, 0x5fa, 0);
				}
				if (*(unsigned char *)(recA + 2) == 6 || *(unsigned char *)(recA + 2) == 7) {
					io_FormatTextBuffer(text, 0x1011, r);
					he_PostEntityMessage(*(int *)(recA + 4), -1, text, 0, 0x5fb, g_6a6538);
				}
			label_561b4d:
				*(int *)(p + 0x70) = *(int *)(p + 0x70) + 1;
				return;
			}
			io_FormatTextBuffer(text, 0x1738, *(unsigned short *)(r + 0x27), r);
			he_MessageBoxQuickjump(*(int *)(recB + 4), -1, text, 0, 0x5f0, *(int *)(r + 1), -1, 0, 0);
			if (*(unsigned short *)(r + 0x27) != 0xffff) {
				io_FormatTextBuffer(text, 0x1739, r);
				he_MessageBoxQuickjump(*(int *)(recA + 4), -1, text, 0, 0x5f0, *(int *)(r + 1), -1, 0, 0);
				gm_TryRecordCrime(0x18, 1,
					*(int *)((unsigned char*)&((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*)(p + 8)] + 4),
					*(int *)((unsigned char*)&((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*)(r + 0x27)] + 4),
					*(int *)(r + 1));
				*(int *)(p + 0x70) = -1;
				return;
			}
			goto label_561d51;
		}
	case 5:
		{
			int v10;
			float v24;

			if (*(unsigned char *)(p + 0xc2) >= 1)
				goto label_56211d;

			{
			char names[3][64] = {"dummy_TUER", "dummy_FAHNE", "dummy_RAUCH_0"};
			unsigned char *r;
			unsigned char *model;
			unsigned char *query;
			unsigned char color[4];
			int n;

			pos[0] = -243.0f;
			pos[1] = -90.0f;
			pos[2] = 190.0f;
			*(int *)(pos + 3) = 0;
			pos[4] = -50.0f;
			*(int *)(pos + 5) = 0;
			pos[6] = 38.0f;
			*(int *)(pos + 7) = 0;
			v24 = 1.0f;
			v10 = d3_CurrentContextIndex;
			r = (unsigned char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(p + 0xac));
			if (r == 0)
				goto label_561d51;
			if (*(unsigned char *)(p + 0xc2) == 0 && d3_CurrentContextIndex == 0) {
				n = sb_PrepareVoice(0, g_677640);
				if (n != 0)
					d3snd_PlayObjectSound(n, *(int *)(r + 0x61), 0x6b, 0x463ea000);
				v24 = 3.0f;
			}
			d3_SelectSceneContext(0, 1);
			model = (unsigned char *)*(int *)(r + 0x61);
			if (model == 0)
				goto label_562049;
			if (!(*(unsigned char *)(p + 0xc2) == 0)) {
				n = gm_RandomMod(3) & 0xffff;
				model = (unsigned char *)d3_FindSceneObject((void *)*(int *)(r + 0x61), 0x100, 0, &names[n][0]);
				if (model != 0)
					d3_TransformPoint((char *)model, (char *)model + 0x4c, pos);
				else
					model = (unsigned char *)d3_FindSceneObject((void *)*(int *)(r + 0x61), 0x100, 0, "dummy_TUER");
			} else {
				*(unsigned char *)(msg + 4) = 0x4f;
				*(int *)(msg + 8) = *(int *)((unsigned char*)&((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*)(p + 8)] + 4);
				*(int *)(msg + 0xc) = -1;
				*(int *)(msg + 0x28) = gm_GameTime;
				*(int *)(msg + 0x2c) = g_7f4c04;
				*(int *)(msg + 0x30) = g_7f4c08;
				*(unsigned short *)(msg + 0x34) = g_7f4c0c;
				*(unsigned char *)(msg + 0x36) = 2;
				*(int *)(msg + 0x58) = *(int *)(r + 1);
				*(unsigned char *)(msg + 0xb0) = 0;
				query = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*)r];
				*(int *)(msg + 0x5c) = (gm_RandomMod(0x10) & 0xffff) - *(unsigned char *)(query + 0x247) * 3 + 0x14;
				cm_SendCopyEntityData(msg);
			}
			if (model == 0 || v10 != 0)
				goto label_562049;
			d3_TransformPoint((char *)model, (char *)model + 0x4c, pos);
			pos[0] = (float)(gm_RandomMod(0x40) & 0xffff) + pos[0] - 32.0f;
			pos[1] = (float)(gm_RandomMod(0x40) & 0xffff) + pos[1];
			pos[2] = (float)(gm_RandomMod(0x40) & 0xffff) + pos[2] - 32.0f;
			color[3] = 0x3f;
			color[2] = 0xc0;
			color[1] = 0xc0;
			color[0] = 0xc0;
			fcn_00418000(v10, pos, 0x1e, 15.0f, 50.0f, 100.0f, 150.0f, 140.0f, 35.0f,
				pos + 4, 400, 6, *(int *)color);
			d3_SpawnRockDebrisEffect(v10, pos, 0x1e, 5.0f, 2.5f, 1.0f, 3.0f, -3.0f, 4.0f, 7.0f, 8.0f,
				*(int *)color);
			fcn_00417d00(v10, pos, (int)(v24 * 40.0f), v24 * 140.0f, v24 * 100.0f,
				20.0f, 60.0f, 0x50);
		label_562049:
			*(MSGCOLOR *)(p + 0x52) = *(MSGCOLOR *)&gm_GameTime;
			gm_AddTime((void *)(p + 0x52), 0, gm_RandomMod(2) & 0xffff, 0);
			*(unsigned char *)(p + 0xc2) = *(unsigned char *)(p + 0xc2) + 1;
			d3_SelectSceneContext(v10, 1);
			return;
			}
		}
	case 6:
		{
			unsigned char *r;

			r = (unsigned char *)gm_LookupEntityRecordById(*(int *)(p + 0xc4));
			if (r == 0) {
				*(int *)(p + 0x70) = -1;
				return;
			}
			if (*(int *)(*(int *)(r + 0x184) + 0x128) != 0) {
				*(MSGCOLOR *)(p + 0x52) = *(MSGCOLOR *)&gm_GameTime;
				gm_AddTime((void *)(p + 0x52), 0, 4, 0);
				goto label_56211d;
			} else {
				goto label_56148f;
			}
		}
	case -2:
	case -1:
		if (*(int *)(p + 0xc4) != -1)
			cm_RequestKillSpieler(*(int *)(p + 0xc4), 1);
		he_FreeAction(p);
		return;
	default:
		return;
	}
label_561d51:
	*(int *)(p + 0x70) = -1;
	return;
label_56211d:
	*(int *)(p + 0x70) = 6;
	return;
}
unsigned char _dpad_6f2578[517488];
