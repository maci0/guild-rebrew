#include <string.h>

extern int g_14ce8cc;
extern int g_7746a0;
extern char g_14cf736;
extern int g_67a370;
extern char* g_14a9a10;
extern short g_14ce8c0;
extern short g_14ce8c2;

typedef struct {
	int id;
	int f4;
	char pad8[4];
	unsigned char fc;
	char padr[3];
	int f10;
	int f14;
	char rest[0x14];
} TACTICAL_SLOT_PKT;
/* SIZE 0x2c */

char __cdecl d3sm_RaycastScreenPoint(int, int, int, int*, int*);
int __cdecl gm_EntitiesDifferByOwnerPtr(char*, int);
int __cdecl gm_IssueEscapeOrder(char*, char*, char*);
int __cdecl cut_AssignConquerTarget(char*, char*, char*);
int __cdecl he_QueueTradeWareCommand(char*, char*, char*);
int __cdecl cut_AssignTargetOrder(char*, char*, char*, int, int);
TACTICAL_SLOT_PKT* __cdecl gm_FindOrCreateEntitySlot(char*, char*);
int __cdecl cm_SendUpdateCutsceneEntitySlot(int, TACTICAL_SLOT_PKT*);
void __cdecl d2_ShowStatusBanner(char*);

/* ADDRESS: GOLDTL 0x004d15c0 */
char __cdecl cut_DispatchTacticalOrder(char* context, char* targetEntity)
{
	TACTICAL_SLOT_PKT l;
	TACTICAL_SLOT_PKT* e;
	int v13;
	int v12;
	int obj;
	char r;

	r = 0;
	if (g_14ce8cc) {
		if (g_7746a0) {
			if (*(int*) ((char*) g_7746a0 + 0x220) == 2) {
				obj = *(int*) ((char*) g_7746a0 + 0x204);
				if (gm_EntitiesDifferByOwnerPtr(targetEntity, obj) != 0 || g_14cf736 != 0) {
					if (cut_AssignTargetOrder(context, targetEntity, (char*) obj, 0, 0) != -1) {
						r = 1;
						goto end;
					}
				}
			} else {
				if (strcmp((char*) g_7746a0, "sp_ESCAPE") == 0) {
					gm_IssueEscapeOrder(context, targetEntity, (char*) g_7746a0);
					r = 1;
					goto end;
				}
				if (strncmp((char*) g_7746a0, "sp_CONQUER", 10) == 0) {
					cut_AssignConquerTarget(context, targetEntity, (char*) g_7746a0);
					r = 1;
					goto end;
				}
				if (strncmp((char*) g_7746a0, "WARE", 4) == 0) {
					he_QueueTradeWareCommand(context, targetEntity, (char*) g_7746a0);
					r = 1;
					goto end;
				}
			}
		} else {
			obj = *(int*) (g_67a370 + 0xb0); if (d3sm_RaycastScreenPoint(obj, g_14ce8c0 + 0x1a,
					 g_14ce8c2 + 0x1a, &v13, &v12) != 0) {
				e = gm_FindOrCreateEntitySlot(context, targetEntity);
				e->fc = 0;
				l = *e;
				l.id = *(int*) (targetEntity + 4);
				l.f4 = 1;
				l.f10 = v13;
				l.f14 = v12;
				cm_SendUpdateCutsceneEntitySlot(*(int*) (context + 0x10), &l);
				r = 1;
				goto end;
			}
			d2_ShowStatusBanner(g_14a9a10);
		}
	}
end:
	return r;
}
