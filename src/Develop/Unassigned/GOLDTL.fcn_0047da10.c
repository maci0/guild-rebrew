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

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern GAME_TIMESTAMP g_100dc04;
extern int g_100dc00;
extern int g_100dc14;
extern int g_7747b4;
float g_67db50 = 1.0f;
float g_67db54 = 0.5f;
extern unsigned char g_7747b0;
#include "Develop/DieGildeAddOn/game/entity_record.h"

int __cdecl gm_GetElapsedMinutes(GAME_TIMESTAMP* a, GAME_TIMESTAMP* b);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl ai_RepairMeisterObjects(AI_STEP_ENTITY* e);
void __cdecl ai_UpdateEntityTurn(AI_STEP_ENTITY* e);
int __cdecl gm_IsLocalSimEntity(AI_STEP_ENTITY* e);
#include "client_packet_builder.h"
void __cdecl cm_AppendPacketFieldValue(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);

/* ADDRESS: GOLDTL 0x0047da10 */
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
	d = gm_GetElapsedMinutes(&g_100dc04, &now);
	f = d * 12.8f;
	n = (int) f;
	g_67db50 = (float) g_7747b4;
	g_67db54 = g_7747b4 * 0.0625f + 0.5f;
	if (d <= 0 || (*(GAME_TIMESTAMP*)&gm_GameTime).hour > 0x16 || (*(GAME_TIMESTAMP*)&gm_GameTime).hour < 6)
		return;
	if (g_100dc04.unit_0 < now.unit_0) {
		g_100dc04 = now;
		return;
	}
	if (d > 0x3c) {
		g_100dc04.hour++;
		n = 0x300;
	} else {
		g_100dc04 = now;
		(*(float *)&g_100dc14) += f - n;
		if ((*(float *)&g_100dc14) >= 1.0f) {
			(*(float *)&g_100dc14) -= 1.0f;
			n++;
		}
	}
	fcn_0064d41a(buf, "Player count: %i, Starting with: %i Count: %i Deltatime: %i", n, g_100dc00, n, d);
	idx = g_100dc00;
	for (k = n; k != 0; k--) {
		if ((*(unsigned short*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[idx].entity_index) != 0xffff) {
			e = ((AI_STEP_ENTITY*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[idx]);
			ai_RepairMeisterObjects(e);
			if ((*(GAME_TIMESTAMP*)&gm_GameTime).hour > 6 && (*(GAME_TIMESTAMP*)&gm_GameTime).hour < 0x16 && (g_7747b0 & 0x80) == 0 && (e->kind == 5
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
		g_100dc04.hour++;
		g_100dc04.minute = 0;
		g_100dc04.second = 0;
		(*(float *)&g_100dc14) = 0;
	}
	fcn_0064d41a(buf, "Next Player: %i", g_100dc00);
}
