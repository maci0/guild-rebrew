/* Resident-capacity message job.  A four-state machine: wait for the clock,
   book the move-in, wait for the booking to be accepted, then take one
   resident out of the house counters and report the result. */
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "client_types.h"

extern char g_7f4ca0[];
extern int g_7f4ca4;
extern unsigned char g_773d75;
extern pos14_7f4c00 gm_GameTime;
extern char s_675908[];
extern char s_6a625c[];
extern char s_6a5b54[];

int __cdecl gm_CompareGameTime(void*, void*);
void __cdecl gm_AddTime(void*, int, int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
float __cdecl fcn_005101e0(unsigned char*, int, int, int);
int __cdecl gm_AccumulateTyped2(char*);
int __cdecl fcn_0050d320(char*, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
void __cdecl he_FreeAction(void*);
int __cdecl cm_GetCommandStatus(int);
char* __cdecl cm_GetCommandResult(int);
int __cdecl fcn_004c6090(unsigned char*, int, int, int);
void __cdecl cm_RequestChrMoveToUniverse(int, int, int, char*);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
char* __cdecl gm_FindBuildingPrimarySlot(char*);
int __cdecl gm_LookupEntityRecordById(int);
char* __cdecl fcn_0050dc90(char*);
char* __cdecl gm_GetEntityTableEntry(char*);
int __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x0055c740 */
void __cdecl he_RunHireWorkerJob(char* ctx)
{
	char text[0x400];
	char* rec;
	char* ent;
	char* h;
	unsigned short* obj;
	unsigned short bank;
	unsigned char kind;
	int state;
	int ver;
	int i;

	state = *(int*) (ctx + 0x70);
	switch (state) {
	case 0:
		*(int*) (ctx + 0x70) = state + 1;
		return;
	case 1:
		if (gm_CompareGameTime(ctx + 0x52, &gm_GameTime) >= 0) {
			return;
		}
		rec = gm_StartFilteredEntitySearch(1, 1, *(int*) (ctx + 0x10));
		if (rec == 0) {
			break;
		}
		ver = *(unsigned char*) rec;
		ver = (int) fcn_005101e0((unsigned char*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (rec + 0x27)]),
		    ver, -1, 1);
		if (ver > gm_AccumulateTyped2((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (rec + 0x27)])) {
			io_FormatTextBuffer(text, 0x1a40, rec);
			he_MessageBoxQuickjump(((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (rec + 0x27)].entity_id,
			    *(int*) (ctx + 0x10), text, 0, 0x5f2, *(int*) (rec + 1),
			    *(int*) (ctx + 0xe0), 0, 0);
			he_FreeAction(ctx);
			return;
		}
		for (i = 0; i < 0xc; i++) {
			if (*(int*) (ctx + 0xb0 + i * 4) > 0) {
				*(int*) (ctx + 0xe4) = fcn_004c6090((unsigned char*) rec,
				    0, *(unsigned char*) (ctx + 0xac), 0);
				*(pos14_7f4c00*) (ctx + 0x52) = gm_GameTime;



				gm_AddTime(ctx + 0x52, 0, 0, 1);
				*(int*) (ctx + 0x70) = *(int*) (ctx + 0x70) + 1;
				return;
			}
		}
		break;
	case 2:
		ver = *(int*) (ctx + 0xe4);
		if (ver == -1) {
			return;
		}
		if (!cm_GetCommandStatus(ver)) {
			return;
		}
		ent = cm_GetCommandResult(*(int*) (ctx + 0xe4));
		if (ent == 0) {
			he_PostEntityMessage(((ENTITY_RECORD*)g_7f4ca0)
			    [*(unsigned short*) (ctx + 8)].entity_id,
			    -1, s_6a625c, 0, 0x5f2, 0);
			he_FreeAction(ctx);
			return;
		}
		*(int*) (ctx + 0xe8) = *(int*) (ent + 4);
		rec = gm_StartFilteredEntitySearch(1, 1, *(int*) (ctx + 0x10));
		if (rec == 0) {
			break;
		}
		if (*(int*) (ctx + 0xe0) == -1) {
			h = gm_FindBuildingPrimarySlot(rec);
			if (h != 0) {
				*(int*) (ctx + 0xe0) = *(int*) (h + 2);
			}
		}
		cm_RequestChrMoveToUniverse(*(int*) (ctx + 0xe8), *(int*) (ctx + 0x10),
		    *(int*) (ctx + 0xe0), s_675908);
		*(int*) (ctx + 0x70) = 3;
		*(pos14_7f4c00*) (ctx + 0x52) = gm_GameTime;



		gm_AddTime(ctx + 0x52, 0, 0, 1);
		return;
	case 3:
		rec = gm_StartFilteredEntitySearch(1, 1, *(int*) (ctx + 0x10));
		if (rec == 0) {
			break;
		}
		obj = (unsigned short*) gm_LookupEntityRecordById(*(int*) (ctx + 0xe8));
		for (i = 0; i < 0xc; i++) {
			if (obj == 0 || *(int*) (ctx + 0xb0 + i * 4) <= 0) {
				continue;
			}
			ver = (int) fcn_005101e0((unsigned char*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)
			    [*(unsigned short*) (rec + 0x27)]), *(unsigned char*) rec, -1, 1);
			*(int*) (ctx + 0xb0 + i * 4) = *(int*) (ctx + 0xb0 + i * 4) - 1;
			bank = *(unsigned short*) (ctx + 8);
			kind = ((ENTITY_RECORD*)g_7f4ca0)[bank].entity_state;
			if (kind == 6 || kind == 7) {
				h = fcn_0050dc90(rec);
				io_FormatTextBuffer(text, 0x1bab, ver, *obj, rec);
				if (h != 0 && (*(unsigned char*) (h + 0x1b4) & 1)) {
					he_MessageBoxQuickjump(((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (ctx + 8)].entity_id,
					    *(int*) (rec + 1), text, 0, 0x60c, *(int*) (rec + 1),
					    *(int*) (ctx + 0xe0), 0, s_6a5b54);
				} else {
					he_MessageBoxQuickjump(((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (ctx + 8)].entity_id,
					    *(int*) (rec + 1), text, 0, 0x5f2, *(int*) (rec + 1),
					    *(int*) (ctx + 0xe0), 0, s_6a5b54);
				}
			}
			cm_RequestTransferCurrencyNoKill(*(int*) (obj + 2),
			    ((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (ctx + 8)].entity_id, g_773d75, ver);
			h = gm_GetEntityTableEntry((char*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (ctx + 8)]));
			if (h != 0) {
				*(int*) (h + 0x4c) = *(int*) (h + 0x4c) + ver;
			}
			break;
		}
		for (i = 0; i < 0xc; i++) {
			if (*(int*) (ctx + 0xb0 + i * 4) > 0) {
				break;
			}
		}
		if (i >= 0xc) {
			he_FreeAction(ctx);
			return;
		}
		*(pos14_7f4c00*) (ctx + 0x52) = gm_GameTime;



		gm_AddTime(ctx + 0x52, 0, (gm_RandomMod(10) & 0xffff) + 0x1e, 0);
		*(int*) (ctx + 0x70) = 1;
		return;
	case -2:
	case -1:
		break;
	default:
		return;
	}
	he_FreeAction(ctx);
}
