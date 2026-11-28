extern char gm_EntitySlotTable[];
extern int g_14b5280;
extern int cm_PacketDeltaBase;
extern float flt_665ecc;
#include "Develop/DieGildeAddOn/game/entity_record.h"
char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
int __cdecl he_PostEntityMessage(int, int, char*, unsigned char, int, char*);
int __cdecl he_GetEntityHomeTarget(char*, int*, int*, int);
int __cdecl ch_StartMovement(int, int, int, int, int, int);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
int __cdecl cm_AppendPacketFieldDelta(unsigned char, unsigned char, unsigned short, char*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl he_FreeAction(char*);
char* __cdecl gm_FindBuildingOwner(int);
char* __cdecl he_RegisterApEvent(int, char*, int, int);
int __cdecl gm_WalkEntityChain(unsigned short);
void __cdecl cm_SendCopyEntityData(int);

/* Entity event handler: state 0 builds and posts the event message, state -1
 * clears the entity's event flag and frees its track. */
/* Entity event handler: state 0 builds and posts the event message, state -1
 * clears the entity's event flag and frees its track. */
/* ADDRESS: GOLDTL 0x00569760 */
void __cdecl he_RunEntfuehrungHostage(char* eventTrack)
{
	float f;
	char* p;
	int n;
	char* e;
	char* rec;
	char* pl;
	int eid;
	int award;
	struct {
		char msg[0xf8];
		char text[0x200];
	} b;

	if (*(int*) (eventTrack + 0x70) < -2) {
		return;
	}
	if (*(int*) (eventTrack + 0x70) >= 0) {
		if (*(int*) (eventTrack + 0x70) != 0) {
			return;
		}

		e = gm_LookupEntityRecordById(*(int*) (eventTrack + 0xac));
		rec = gm_StartFilteredEntitySearch(1, 1, *(int*) (eventTrack + 0xb0));
		if (rec == 0 || e == 0) {
			*(int*) (eventTrack + 0x70) = -1;
			return;
		}
		p = (char*) &((ENTITY_RECORD*) gm_EntitySlotTable)[*(unsigned short*) (rec + 0x27)];
		if (*(int*) (rec + 0x65) == -1) {
			*(int*) (rec + 0x65) = *(int*) (e + 4);
		}
		if (*(unsigned char*) (e + 0x1b1) <= 0) {
			int idx;
			idx = -1;
			if ((*(unsigned char*) (eventTrack + 0x78) & 2) != 0) {
				io_FormatTextBuffer(b.text, (char*) 0x19da);
				he_PostEntityMessage(*(int*) (e + 4), *(int*) (e + 4), b.text, 0, 0x5fb, 0);
				if (*(int*) (e + 0x184) != 0) {
					if (he_GetEntityHomeTarget(e, &n, (int*) &f, 0) != 0) {
						ch_StartMovement(*(int*) (e + 4), n, *(int*) &f, 0, 0, (int) 0x6a69c8);
					}
				}
				cm_BeginPacketFieldDelta(rec, *(int*) (rec + 1));
				cm_AppendPacketFieldDelta(4, 1, (unsigned short) ((int) rec - cm_PacketDeltaBase + 0x65),
				             (char*) &idx);
				cm_RequestChangeAttribute();
			}
			he_FreeAction(eventTrack);
			return;
		}

		pl = gm_FindBuildingOwner((int) rec);
		if ((*(unsigned char*) (eventTrack + 0x78) & 2) == 0) {
			return;
		}
		he_RegisterApEvent(*(unsigned short*) p, (char*) g_14b5280, -2, 0);
		io_FormatTextBuffer(b.text, (char*) 0x19c2, eventTrack + 0xb4);
		he_PostEntityMessage(*(int*) (e + 4), *(int*) (e + 4), b.text, 0, 0x5f0, 0);
		if (pl == 0) {
			return;
		}
		if ((pl[0x1b4] & 1) == 0) {
			return;
		}
		if (*(unsigned char*) (e + 0x1b1) >= 4) {
			f = 0.1f;
		} else if (*(unsigned char*) (e + 0x1b1) == 3) {
			f = 0.06f;
		} else if (*(unsigned char*) (e + 0x1b1) == 2) {
			f = 0.04f;
		} else if (*(unsigned char*) (e + 0x1b1) == 1) {
			f = 0.02f;
		}
		n = gm_WalkEntityChain(*(unsigned short*) e);
		award = (int) ((flt_665ecc < (float) n ? flt_665ecc : (float) n) * f);
		eid = *(int*) (e + 4);
		*(int*) (b.msg + 0xc) = *(int*) (rec + 1);
		*(unsigned char*) (b.msg + 4) = 0x3e;
		*(int*) (b.msg + 8) = eid;
		*(unsigned char*) (b.msg + 0x36) = 9;
		*(int*) (b.msg + 0x58) = eid;
		*(int*) (b.msg + 0x60) = award;
		*(int*) (b.msg + 0x5c) = ((ENTITY_RECORD*) gm_EntitySlotTable)[
		                                  *(unsigned short*) (eventTrack + 8)].entity_id;
		cm_SendCopyEntityData((int) b.msg);
	} else {
		e = gm_LookupEntityRecordById(*(int*) (eventTrack + 0xac));
		if (e != 0) {
			e[0x1b1] = 0;
		}
		he_FreeAction(eventTrack);
	}
}
