

typedef struct Ent {
	unsigned short id;
	unsigned char kind;
} Ent;

typedef struct Party {
	char pad0[0x30];
	unsigned char count;
	char pad31[3];
	int ids[1];
} Party;

typedef struct Obj {
	char pad0[0x88];
	int owner;
} Obj;

typedef struct Unit {
	char pad0[0x184];
	Obj* obj;
} Unit;

typedef struct Slot {
	char pad0[0x35c];
} Slot;
// SIZE 0x35c

typedef struct Game {
	int pad0;
	int player;
} Game;

extern volatile int tb_TimerTicks;
#include "Develop/Units/Msx/client_sound.h"
extern int g_772e94;
extern int cut_CombatCancelledEntity;
extern int cut_CombatResolved;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern unsigned char gm_ClientModeFlags;
extern char io_LastKeyScancode;
extern char* ch_ContextCharacters[32];
extern int d3_ActiveScene;
extern char str_empty[];
extern char* g_14a97d4;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned short* cut_ActivePlayerEntity;

unsigned short __cdecl gm_RandomMod(int n);
void __cdecl cut_RefreshCombatContextCharacters(void);
void __cdecl d2_InitCombatHud(int);
#include "Develop/Units/Msx/msx.h"
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl ch_SetAnimationPaused(Obj*, int);
void __cdecl d2_ShowStatusBanner(char*);
void __cdecl d2_UpdateCombatFrame(int);
Ent* __cdecl gm_LookupEntityRecordById(int);
void __cdecl cut_AssignCombatTeamOrders(Ent*);
void __cdecl cut_ResolveCombatWinner(Party*);
void __cdecl gm_UpdateTaskProgress(Slot*);
void __cdecl d2_DestroyCombatHud(void);

/* ADDRESS: GOLDDE 0x004c6c10 */
void __cdecl cut_RunTacticalCombat(int arg)
{
	unsigned int last;
	int r;
	Ent* e;
	int id;
	int i;

	last = (unsigned int) tb_TimerTicks - 0x15e;
	r = gm_RandomMod(100);
	cut_RefreshCombatContextCharacters();
	d2_InitCombatHud(arg);
	tp_cut_CombatAmbientTrack = 0;
	if (r < 0x32) {
		tp_cut_CombatAmbientTrack = msx_StartAmbientTrack("Athmos\\Kampfathmo_1.mp3", 0xb);
	} else {
		tp_cut_CombatAmbientTrack = msx_StartAmbientTrack("Athmos\\Kampfathmo_2.mp3", 0xb);
	}
	g_772e94 = 0;
	while (main_RunFrameLoop(cut_RunTacticalCombat, 0xfd6c6) != 0) {
		if (cut_CombatResolved != 0) {
			break;
		}
		if (((*(int*)&gm_ClientModeFlags) & 4) == 0 && io_LastKeyScancode == 0x39) {
			g_772e94 = g_772e94 == 0;
			for (i = 0; i < 0x20; i++) {
				if (((Unit**)ch_ContextCharacters)[i] != 0 && ((Unit**)ch_ContextCharacters)[i]->obj->owner == d3_ActiveScene) {
					ch_SetAnimationPaused(((Unit**)ch_ContextCharacters)[i]->obj, g_772e94);
				}
			}
			d2_ShowStatusBanner(&(*(char*)str_empty));
		}
		if (g_772e94 != 0) {
			d2_ShowStatusBanner(g_14a97d4);
		} else {
			d2_UpdateCombatFrame(arg);
		}
		if (cut_CombatCancelledEntity != 0 || cut_CombatResolved != 0) {
			d2_DialogCloseRequested = 1;
		} else if (g_772e94 == 0) {
			if ((unsigned int) tb_TimerTicks > last + 0x1a4) {
				for (i = 0; i < ((Party*)g_772eb4)->count; i++) {
					id = ((Party*)g_772eb4)->ids[i];
					if (id != -1) {
						e = gm_LookupEntityRecordById(id);
						if (e != 0 && e->kind != 6 && e->kind != 7) {
							cut_AssignCombatTeamOrders(e);
						}
					}
				}
				last = (unsigned int) tb_TimerTicks;
			}
			if (((Game*)cut_ActivePlayerEntity)->player == g_68b79c) {
				cut_ResolveCombatWinner(((Party*)g_772eb4));
				for (i = 0; i < ((Party*)g_772eb4)->count; i++) {
					if (((Party*)g_772eb4)->ids[i] != -1) {
						gm_UpdateTaskProgress(&((Slot*)cut_ParticipantSlots)[i]);
					}
				}
			}
			if (cut_CombatCancelledEntity != 0 || cut_CombatResolved != 0) {
				d2_DialogCloseRequested = 1;
			}
		}
	}
	d2_DestroyCombatHud();
}
