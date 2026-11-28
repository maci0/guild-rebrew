extern unsigned short* cut_ActivePlayerEntity;
extern int sv_ClickedObjekt;
extern char* ch_ContextCharacters[32];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* d2_HoveredSceneObject;
extern char io_RightShiftKeyDown;
extern unsigned short* cut_CombatDefenderEntity;
extern int g_772ed4;
extern int g_772ed8;

int __cdecl gm_GetEntityControlMask(int, char*);
int __cdecl gm_EntitiesDifferByOwnerPtr(char*, char*);
void __cdecl cut_ClearStatusOverlaySlots(void);
int* __cdecl d3snd_QueueSound(int, int, char*, int, int);

#ifdef REBREW_GOLD
#define OBJ_TITLE_OFF 0x200
#else
#define OBJ_TITLE_OFF 0x204
#endif


/* ADDRESS: GOLDTL 0x004d0f00 */
/* ADDRESS: GOLDDE 0x004be1f0 */
void __cdecl d2_SelectClickedCombatWorker(void)
{
	unsigned short* me;
	char* e;
	char* x;
	char* t;
	int i;

	me = cut_ActivePlayerEntity;
	sv_ClickedObjekt = 0;
	for (i = 0; i < 32; i++) {
		e = ch_ContextCharacters[i];
		if (e != 0 && e[0x188] != 0 && (gm_GetEntityControlMask(*me, e) & 0x800) != 0
		    && *(int*) (e + 0x184) != 0 && e[8] != 0)
			break;
	}
	if (g_14ce8cc == 0 || d2_CurrentElementId != -1)
		return;
	x = d2_HoveredSceneObject;
	if (x != 0 && *(int*) (x + 0x220) == 2) {
		t = *(char**) (x + OBJ_TITLE_OFF);
		if ((gm_GetEntityControlMask(*me, t) & 0x800) != 0 && io_RightShiftKeyDown == 0
		    && (e == 0 || gm_EntitiesDifferByOwnerPtr(e, t) == 0)) {
			cut_ClearStatusOverlaySlots();
			t[0x188] = 1;
			if (*(int*) (t + 0x16c) == (*(int*)&cut_CombatDefenderEntity))
				d3snd_QueueSound(*(unsigned short*) t, g_772ed4, "_ARBEITER_KOMMENTARE_KLICK", -1, 0);
			else
				d3snd_QueueSound(*(unsigned short*) t, g_772ed8, "_ARBEITER_KOMMENTARE_KLICK", -1, 0);
			x = d2_HoveredSceneObject;
		}
	}
	sv_ClickedObjekt = (int) x;
}
