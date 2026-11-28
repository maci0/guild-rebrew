#include "Develop/client_types.h"
/* Location record: 0x21c-byte entries in the g_7f4ca0 table. */
typedef struct Rec {
	unsigned short id;       /* 0x000 */
	unsigned char type;      /* 0x002 */
	char pad3;
	int owner;               /* 0x004 */
	char pad8[0x16c - 8];
	char* home;              /* 0x16c */
	char pad170[0x21c - 0x170];
} Rec;
// SIZE 0x21c

#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int gm_GameTime;
extern float flt_100_0;

extern float g_665bf0;
extern double g_6628f0;

char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int id);
char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl he_FreeAction(char* e);
void __cdecl he_AssignActionSlot(char* e, int a, int id, char* rec);
void __cdecl cm_SendCancelCharacterActions(int owner);
void __cdecl ch_StartMovement(int a, int b, int c, int d, int e, char* tag);
void __cdecl gm_AddTime(int* pos, int a, int b, int c);
int __cdecl gm_GetEntityMood(char* e);
char* __cdecl gm_QueryEntities(int a, int b, int c, int d, int e);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_CalculateGebaeudeValue(char* e, int n);
void __cdecl cm_RequestTransferCurrencyNoKill(int a, int b, int c, int d);
void __cdecl he_PostEntityMessage(int a, int b, char* text, int c, int d, char* tag);
void __cdecl he_MessageBoxQuickjump(int a, int b, char* text, int c, int d, int e, int f, int g,
	char* tag);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);

/* ADDRESS: GOLDTL 0x00553cd0 */
/* ADDRESS: GOLDDE 0x0053a080 */
void __cdecl he_RunBetriebsPruefung(char* event)
{
	char buf[1024];
	char* e;
	char* q;
	unsigned short* record;
	char* p;
	unsigned char type;
	float f;
	int state;
	int x;
	int found;
	int a;
	int b;

	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (event + 0xb0));
	record = (unsigned short*) gm_LookupEntityRecordById(*(int*) (event + 0xac));
	state = *(int*) (event + 0x70);
	if (state == -2 || record == 0 || e == 0 || *(unsigned short*) (e + 0x27) == 0xffff) {
		he_FreeAction(event);
		return;
	}
	switch (state) {
	case 0:
		he_AssignActionSlot(e, 0, *record, event);
		cm_SendCancelCharacterActions(*(int*) (record + 2));
		ch_StartMovement(*(int*) (record + 2), *(int*) (e + 1), -1, 0, 1, "BetriebsPr");
		*(pos14_7f4c00*) (event + 0x52) = *(pos14_7f4c00*) &gm_GameTime;
		gm_AddTime((int*) (event + 0x52), 0, 10, 0);
		*(int*) (event + 0x70) = 1;
		return;
	case 1:
		*(pos14_7f4c00*) (event + 0x52) = *(pos14_7f4c00*) &gm_GameTime;
		gm_AddTime((int*) (event + 0x52), 0, 4, 0);
		p = *(char**) ((char*) record + 0x184);
		if (*(int*) (p + 0x128)) {
			*(int*) (event + 0x70) = 1;
			return;
		}
		f = (flt_100_0 - (float) gm_GetEntityMood(e)) * 0.01f;
		found = 0;
		for (q = gm_QueryEntities(0, 2, 7, 4, 0x1d); q != 0; q = gm_NextEntityQueryMatch()) {
			if (*(int*) (q + 0x1c) == *(int*) (e + 1)
				&& *(unsigned char*) (q + 0x12) < 0x50) {
				found = 1;
				break;
			}
		}
		if (!(f > 0.2) && found == 0) {
			io_FormatTextBuffer(buf, 0x1a76, *(unsigned short*) (e + 0x27), e);
			a = (*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (event + 8)].entity_id);
			he_PostEntityMessage(a, a, buf, 0, 0x5f0, "_NACHRICHTEN_HS_88");
			io_FormatTextBuffer(buf, 0x1a78, *(unsigned short*) (event + 8), e);
			b = (*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (e + 0x27)].entity_id);
			he_MessageBoxQuickjump(b, b, buf, 0, 0x5f0, *(int*) (e + 1), -1, 0,
				"_NACHRICHTEN_HS_86");
			*(int*) (event + 0x70) = 2;
			return;
		}
		x = (int) (gm_CalculateGebaeudeValue(e, 100) * f * 0.07f);
		cm_RequestTransferCurrencyNoKill((*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (event + 8)].entity_id),
			(*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (e + 0x27)].entity_id), 0, x);
		type = (*(unsigned char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (event + 8)].entity_type);
		if (type == 6 || type == 7) {
			io_FormatTextBuffer(buf, 0x1a75, x, *(unsigned short*) (e + 0x27), e);
			a = (*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (event + 8)].entity_id);
			he_PostEntityMessage(a, a, buf, 0, 0x5f0, "_NACHRICHTEN_HS_87");
		}
		type = (*(unsigned char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (e + 0x27)].entity_type);
		if (type == 6 || type == 7) {
			io_FormatTextBuffer(buf, 0x1a77, *(unsigned short*) (event + 8), e, x);
			b = (*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (e + 0x27)].entity_id);
			he_MessageBoxQuickjump(b, b, buf, 0, 0x5f0, *(int*) (e + 1), -1, 0,
				"_NACHRICHTEN_HS_86");
		}
		*(int*) (event + 0x70) = 2;
		return;
	case 2:
		he_AssignActionSlot(e, 0, *record, 0);
		cm_SendCancelCharacterActions(*(int*) (record + 2));
		ch_StartMovement(*(int*) (record + 2), *(int*) (event + 0xb4), *(int*) (event + 0xb8), 0,
			0, "BetriebsPr");
		he_FreeAction(event);
		return;
	}
}
