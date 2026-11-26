#include "Develop/DieGildeAddOn/game/spiel.h"
#include "client_types.h"
#include <string.h>

// SIZE 0x2f4
typedef struct {
	char name[0x2f4];
} Dyn;

extern char g_868060[];
extern pos14_7f4c00 gm_GameTime;

char *__cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_HasActiveSpecialObject(char *, int);
char *__cdecl he_StartHandlungSearch(int, int, int);
char *__cdecl he_fn_Handlung(void);
int __cdecl gm_FindRecordById(int);
unsigned short __cdecl gm_RandomMod(int);

float __cdecl eval_ObjektPreis2Credits(int, char);
void *__cdecl fcn_00502cd0(int, int, ...);
void *__cdecl gm_NextEntityQueryMatch(void);
void __cdecl cm_SendRemoveLinkedObject(int, int, int);
void __cdecl fcn_004c5620(int, void *);
void __cdecl io_FormatTextBuffer(char *, int, ...);
void __cdecl he_PostEntityMessage(int, int, char *, int, int, int);

/* ADDRESS: GOLDTL 0x004b9030 */
int __cdecl gm_SabotageHandlungShipment(int *msg)
{
	char *a;
	char *b;
	int total;
	char *victim;
	char *recs[8];
	char *ents[8];
	char buf[0x200];
	char *task;
	char *item;
	char *cargo;

	int n;
	int k;

	n = 0;
	victim = gm_LookupEntityRecordById(*msg);
	if (victim == 0) {
		return 1;
	}
	if (gm_HasActiveSpecialObject(victim, 0x290) != 0) {
		return 0x400;
	}
	for (task = he_StartHandlungSearch(1, 0, 0xf); task != 0 && n < 8; task = he_fn_Handlung()) {
		item = (char *) gm_FindRecordById(*(int *) (task + 0xac));
		if (item != 0 && *(int *) (item + 0xa) == *(unsigned short *) victim) {
			gm_ResolveEntityById((void **) (&a), 0, 0, *(int *) (task + 0xb4));
			gm_ResolveEntityById((void **) (&b), 0, 0, *(int *) (task + 0xb0));
			if ((a != 0 && gm_CheckEntityType(a) != 0) || (b != 0 && gm_CheckEntityType(b) != 0)) {
				if ((b != 0 && a != 0 && *b == 0x47) || *a == 0x47) {
					ents[n] = task;
					recs[n] = item;
					n++;
				}
			}
		}
	}
	if (n == 0) {
		return 0x400;
	}
	k = gm_RandomMod(n);
	task = ents[k];
	item = recs[k];
	total = (int) eval_ObjektPreis2Credits(*(unsigned short *) item, *(char *) (item + 0x12));

	cargo = (char *) fcn_00502cd0(*(int *) (item + 0x14), 2, 5, 6);
	while (cargo != 0) {
		total = (int) (eval_ObjektPreis2Credits(*(unsigned short *) cargo, *(char *) (item + 0x12))
		             * *(int *) (cargo + 0xe)
		             + total);

		cargo = (char *) gm_NextEntityQueryMatch();
	}
	*(pos14_7f4c00 *) (task + 0x52) = gm_GameTime;
	cm_SendRemoveLinkedObject(-1, -1, *(int *) (item + 2));
	fcn_004c5620(-1, task);
	gm_ResolveEntityById((void **) (&b), 0, 0, *(int *) (task + 0xb0));
	gm_ResolveEntityById((void **) (&a), 0, 0, *(int *) (task + 0xb4));
	if (b != 0 && a != 0) {
		if (*b == 0x47) {
			io_FormatTextBuffer(buf, *(unsigned short *) (msg + 1) + 0x12e7,
			             ((Dyn *) g_868060)[*(int *) (b + 0x65)].name,
			             ((Dyn *) g_868060)[0].name, total);
		} else {
			io_FormatTextBuffer(buf, *(unsigned short *) (msg + 1) + 0x12e7,
			             ((Dyn *) g_868060)[0].name,
			             ((Dyn *) g_868060)[*(int *) (a + 0x65)].name, total);
		}
		he_PostEntityMessage(*(int *) (victim + 4), *(int *) (victim + 4), buf, strlen(buf) > 0x100, 0x5ef, 0);
	}
	return 0;
}
