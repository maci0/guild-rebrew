#include "Develop/DieGildeAddOn/game/game_timestamp.h"







// SIZE 0xe


// SIZE 0x21c
typedef struct
{
	unsigned short id;
	unsigned char kind;
	char pad3;
	int h;
	char pad8[0x24 - 8];
	int gold;
	char pad28[0x1cc - 0x28];
	int flags;
	char pad1d0[0x21c - 0x1d0];
} AI_STEP_ENTITY;

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern GAME_TIMESTAMP ai_LastTurnTimestamp;
extern int g_100dc00;
extern int ai_TurnCarryAccumulator;
extern int gm_DifficultyLevel;
float ai_DifficultyFactor = 1.0f;
float ai_DifficultyRate = 0.5f;
extern unsigned char gm_ClientModeFlags;
#include "Develop/DieGildeAddOn/game/entity_record.h"

int __cdecl gm_GetElapsedMinutes(GAME_TIMESTAMP* a, GAME_TIMESTAMP* b);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl ai_RepairMeisterObjects(AI_STEP_ENTITY* e);
void __cdecl ai_UpdateEntityTurn(AI_STEP_ENTITY* e);
int __cdecl gm_IsLocalSimEntity(AI_STEP_ENTITY* e);
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
void __cdecl cm_AppendPacketFieldValue(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);

/* ADDRESS: GOLDTL 0x0047da10 */
/* ADDRESS: GOLDDE 0x0046c9d0 */
void __cdecl ai_StepEntityTurns(void)
{
	float f;
	int n;
	GAME_TIMESTAMP now;
	char buf[0x400];
	AI_STEP_ENTITY* e;
	int d;
	int k;
	int idx;

	now = (*(GAME_TIMESTAMP*)&gm_GameTime);
	d = gm_GetElapsedMinutes(&ai_LastTurnTimestamp, &now);
	f = d * 12.8f;
	n = (int) f;
	ai_DifficultyFactor = (float) gm_DifficultyLevel;
	ai_DifficultyRate = gm_DifficultyLevel * 0.0625f + 0.5f;
	if (d <= 0 || (*(GAME_TIMESTAMP*)&gm_GameTime).hour > 0x16 || (*(GAME_TIMESTAMP*)&gm_GameTime).hour < 6)
		return;
	if (ai_LastTurnTimestamp.unit_0 < now.unit_0) {
		ai_LastTurnTimestamp = now;
		return;
	}
	if (d > 0x3c) {
		ai_LastTurnTimestamp.hour++;
		n = 0x300;
	} else {
		ai_LastTurnTimestamp = now;
		(*(float *)&ai_TurnCarryAccumulator) += f - n;
		if ((*(float *)&ai_TurnCarryAccumulator) >= 1.0f) {
			(*(float *)&ai_TurnCarryAccumulator) -= 1.0f;
			n++;
		}
	}
	fcn_0064d41a(buf, "Player count: %i, Starting with: %i Count: %i Deltatime: %i", n, g_100dc00, n, d);
	idx = g_100dc00;
	for (k = n; k != 0; k--) {
		if ((*(unsigned short*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[idx].entity_index) != 0xffff) {
			e = ((AI_STEP_ENTITY*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[idx]);
			ai_RepairMeisterObjects(e);
			if ((*(GAME_TIMESTAMP*)&gm_GameTime).hour > 6 && (*(GAME_TIMESTAMP*)&gm_GameTime).hour < 0x16 && (gm_ClientModeFlags & 0x80) == 0 && (e->kind == 5
			    || ((e->id ^ (*(GAME_TIMESTAMP*)&gm_GameTime).hour) & 1) == 0))
				ai_UpdateEntityTurn(e);
			if ((gm_IsLocalSimEntity(e) != 0 && e->gold != 0) || (e->flags & 0x3000)) {
				int v;

				v = -e->gold - (int) (e->gold * -0.89f);
				cm_BeginPacketFieldDelta((char*) e, e->h);
				cm_AppendPacketFieldValue(4, 1, 0x24, &v);
				cm_RequestChangeAttribute();
			}
		}
		idx = (idx + 1) % 0x300;
	}
	g_100dc00 = idx;
	if (g_100dc00 == 0x300) {
		g_100dc00 = 0;
		ai_LastTurnTimestamp.hour++;
		ai_LastTurnTimestamp.minute = 0;
		ai_LastTurnTimestamp.second = 0;
		(*(float *)&ai_TurnCarryAccumulator) = 0;
	}
	fcn_0064d41a(buf, "Next Player: %i", g_100dc00);
}
