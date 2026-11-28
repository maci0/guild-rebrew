

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x214];
};

#include "Develop/client_types.h"
// SIZE 0xe








extern pos14_7f4c00 gm_GameTime;
extern struct house gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
extern char str_empty[];

char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl gm_CompareGameTime(pos14_7f4c00*, pos14_7f4c00*);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl gm_GetBuildingTechEffect(char*, int, int);
int __cdecl gm_CalcElapsedWorkMinutes(pos14_7f4c00*, pos14_7f4c00*, char*);

void __cdecl cm_AppendPacketFieldValue(int, int, short, unsigned char*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
char* __cdecl gm_FindBuildingOwner(char*);
char* __cdecl gm_QueryEntities(int, int, int, int);
char* __cdecl gm_SetupEntityQuery(char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, char*, char*);
void __cdecl he_AssignActionSlot(char*, int, int, int);
void __cdecl he_FreeAction(char*);

/* ADDRESS: GOLDDE 0x00560230 */
void __cdecl he_RunUpgraden(char* e)
{
	char* who;
	char* q;
	char* r;
	char* s;
	unsigned char* p;
	char buf[0x200];

	switch (*(int*) (e + 0x70)) {
	case 0:
		who = gm_LookupEntityRecordById(*(int*) (e + 0xac));
		if (who != 0 && (unsigned char) who[*(int*) (e + 0xb0) + 0x80] < 252.0f
		    && gm_CompareGameTime(&gm_GameTime, (pos14_7f4c00*) (e + 0xb8)) < 0) {
			unsigned char add;
			float skill;
			double months;
			q = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0x10));
			if (q == 0) {
				break;
			}
			skill = (float) gm_GetBuildingTechEffect(q, 0xc, 1);
			months = gm_CalcElapsedWorkMinutes((pos14_7f4c00*) (e + 0x60), &gm_GameTime, q) * (1.0 / 30.0);
			add = (unsigned char) ((months * 8.0) * (skill * 0.01 + 1.0));
			p = (unsigned char*) &who[*(int*) (e + 0xb0) + 0x80];
			add = (unsigned char) (add / (*p * (1.0f / 252.0f) + 1.0));
			if (add + *p > 252.0f) {
				add = (unsigned char) (252.0f - *p);
			}
			cm_BeginPacketFieldDelta(who, *(int*) (who + 4));
			cm_AppendPacketFieldValue(1, 1, (short) (who - cm_PacketDeltaBase + *(int*) (e + 0xb0) + 0x80), &add);
			cm_RequestChangeAttribute();
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			*(pos14_7f4c00*) (e + 0x60) = gm_GameTime;
			gm_AddTime((pos14_7f4c00*) (e + 0x52), 0, 0x1e, 0);
			return;
		}
		who = gm_LookupEntityRecordById(*(int*) (e + 0xac));
		q = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0x10));
		if (q == 0 || who == 0) {
			break;
		}
		r = gm_FindBuildingOwner(q);
		if (r == 0 || !(r[0x1b4] & 1)) {
			s = gm_QueryEntities(*(int*) (q + 0x5d), 1, 1, *(int*) (e + 0xb4));
			if (s == 0) {
				s = gm_SetupEntityQuery(q);
			}
			if (s != 0) {
				io_FormatTextBuffer(buf, 0x1bc8, *(unsigned short*) who, q);
				he_MessageBoxQuickjump(gm_EntitySlotTable[*(unsigned short*) (e + 8)].handle, *(int*) (e + 0x10), buf, 0, 0x5f2,
				    *(int*) (q + 1), *(int*) (s + 2), str_empty, "_NACHRICHTEN_HS_81");
			}
		}
		he_AssignActionSlot(q, 0, *(unsigned short*) who, 0);
		he_FreeAction(e);
		return;
	case -2:
	case -1:
		break;
	default:
		return;
	}
	he_FreeAction(e);
}
