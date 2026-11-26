#include <string.h>
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "client_types.h"

extern char g_7f4ca0[];
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern char* g_entity_type_table;
extern float g_696540[];
extern float g_696550[];
extern char s_6a2e68[];
extern char s_6a2e70[];
extern char s_6a2e78[];

extern void __cdecl he_AddActionActor(int, char*);
extern void __cdecl he_RemoveActionActor(int, char*);
extern void __cdecl gm_CountBuildingWorkers(char*);
extern int __cdecl he_CountActionActors(char*);
extern void __cdecl he_FreeAction(char*);
extern int __cdecl fcn_004c5620(char, char*);
extern void __cdecl cm_BeginPacketFieldDelta(char*, int);
extern int __cdecl cm_AppendCommandSyncField(unsigned char, unsigned char, short, void*);
extern void __cdecl cm_SendSetAttribute(void);
extern char* __cdecl ch_CreateAction(char*, int, ...);
extern int __cdecl gm_GetSeason(int*);
extern int __cdecl init_EnsureObjektSceneContext(char*);
extern int __cdecl init_AllocateGebaeudeSceneSlot(unsigned char*);
extern void* __cdecl evt_FindScriptById(int);
extern void __cdecl evt_RequestScriptExit(char*);
extern int __cdecl main_RunFrameLoop(void);

/* SIZE 0x188 */
typedef struct {
	unsigned short id;	/* +0x00 */
	char pad02[2];
	int handle;		/* +0x04 */
	char pad08[0x164];
	char* active;		/* +0x16c */
	char pad170[0xc];
	char* shown;		/* +0x17c */
	char pad180[4];
	char* owner;		/* +0x184 */
} Slot_529160;

/* SIZE 0x24d */
typedef struct {
	unsigned char type;	/* +0x00 */
	char pad1[0x27];
	int object;		/* +0x28 */
	char pad2c[0x5c];
	int field88;		/* +0x88 */
} Rec_529160;


/* Shows one entity of the scene slot and queues the matching action; the
 * object type selects one of two scene-hook paths, then the shown object is
 * replaced by a4. */
/* ADDRESS: GOLDTL 0x00529160 */
void __cdecl fcn_00529160(unsigned char* activeRec, char* a2, unsigned int index, unsigned char* newShown)
{
	Slot_529160* slot;
	Rec_529160* rec;
	unsigned char* old;
	char* r;
	void* o;
	int contextIdx;
	int cls;
	int obj;
	unsigned int tick;
	unsigned char type;

	type = 0;
	if ((int) index >= 0x300) {
		return;
	}
	slot = (Slot_529160*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[index]));
	old = *(unsigned char**) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[index]) + 0x17c);
	if (newShown == old) {
		return;
	}
	if (activeRec == 0) {
		activeRec = (unsigned char*) slot->active;
	}
	if (a2 != 0) {
		rec = (Rec_529160*) ((unsigned char*) g_entity_type_table + (unsigned int) *activeRec * 0x24d);
		if (*(short*) a2 != 0xfd) {
			contextIdx = init_EnsureObjektSceneContext(a2);
		} else {
			contextIdx = init_AllocateGebaeudeSceneSlot(activeRec);
		}
		cls = gm_GetSeason((int*) &gm_GameTime);
		tick = g_7f4c04 & 0xffff;
		if ((((float) (int) tick < g_696550[cls] && g_696540[cls] <= (float) (int) tick)
		     || rec->type == 4 || rec->type == 0x13 || rec->type == 0x1d)
		    && contextIdx >= 0 && slot->owner != 0
		    && contextIdx * 0x3dc + 0x10432c0 != ((Rec_529160*) slot->owner)->field88) {
			r = ch_CreateAction(slot->owner, 0x33, contextIdx, *(int*) (activeRec + 1), *(int*) (a2 + 2));
			strcpy(r + 0x70, "sv_ChangePlayerHE");




			r = ch_CreateAction(slot->owner, 0x39, contextIdx);
			strcpy(r + 0x70, "sv_ChangePlayerHE");




			obj = ((Rec_529160*) slot->owner)->object;
			if (obj != -1) {
				o = evt_FindScriptById(obj);
				if (o != 0) {
					evt_RequestScriptExit((char*) o);
				}
			}
		}
	}
	if (old != 0) {
		he_RemoveActionActor(slot->id, (char*) old);
		switch (*old) {
		case 3:
		case 4:
		case 8:
		case 9:
			gm_CountBuildingWorkers((char*) old);
			break;
		case 20:
		case 21:
		case 140:
			if (slot->owner != 0) {
				obj = ((Rec_529160*) slot->owner)->object;
				if (obj != -1) {
					evt_RequestScriptExit((char*) evt_FindScriptById(obj));
				}
			}
			if (*(int*) (old + 0x70) < 3) {
				*(pos14_7f4c00*) (old + 0x52) = gm_GameTime;
				*(int*) (old + 0x70) = -1;
			}
			break;
		case 22:
		case 136:
		case 137:
		case 141:
		case 143:
			gm_CountBuildingWorkers((char*) old);
			if (he_CountActionActors((char*) old) <= 0) {
				*(pos14_7f4c00*) (old + 0x52) = gm_GameTime;
				fcn_004c5620(-1, (char*) old);
			}
			break;
		case 40:
			if (he_CountActionActors((char*) old) <= 0) {
				fcn_004c5620(-1, (char*) old);
			}
			break;
		case 72:
		case 73:
		case 117:
		case 161:
			he_FreeAction((char*) old);
			break;
		}
	} else if (slot->owner != 0 && ((Rec_529160*) slot->owner)->object != -1) {
		obj = ((Rec_529160*) slot->owner)->object;
		o = evt_FindScriptById(obj);
		if (o != 0 && (strstr((char*) o, s_6a2e70) != 0 || strstr((char*) o, s_6a2e68) != 0)) {
			evt_RequestScriptExit((char*) o);
		}
	}
	if (newShown != 0) {
		he_AddActionActor(slot->id, (char*) newShown);
		switch (*newShown) {
		case 3:
		case 4:
		case 8:
		case 9:
		case 20:
		case 21:
		case 140:
			gm_CountBuildingWorkers((char*) newShown);
			break;
		}
		type = *newShown;
	}
	if ((slot->shown == 0 || newShown != 0) && type == 0) {
		return;
	}
	cm_BeginPacketFieldDelta((char*) slot, slot->handle);
	cm_AppendCommandSyncField(1, 1, 0x180, &type);
	cm_SendSetAttribute();
	slot->shown = (char*) newShown;
}
