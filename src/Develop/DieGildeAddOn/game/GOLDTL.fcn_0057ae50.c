


/* 'sPgf': tag the effect object with its owner id */
#define FX_MAGIC 0x66675073

#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl evt_FindScriptById(int);
char* __cdecl evt_LoadGfxScript(const char* name);
void __cdecl fcn_004432d0(int, int);
void __cdecl d3_TransformPoint(char*, char*, float*);
void __cdecl fcn_00428340(char* o, int n, ...);
void __cdecl evt_RequestScriptExit(char*);
void __cdecl he_FreeAction(char*);

void __cdecl he_UpdateNecromancerFog(char* u)
{
	float pos[4];
	char* q;
	char* e;
	char* o;
	int saved;

	q = he_StartHandlungSearch(1, 1, *(int*) (u + 0xac));
	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0x10));
	if (e == 0 || *(char**) (e + 0x61) == 0 || q == 0 || *(int*) (q + 0x70) == -2 || *(int*) (q + 0x70) == -1) {
		o = evt_FindScriptById(*(int*) (u + 0xb0));
		if (o != 0 && *(int*) o == FX_MAGIC && *(int*) (o + 4) == *(int*) (u + 0x10)) {
			saved = d3_CurrentContextIndex;
			fcn_004432d0(0, 1);
			evt_RequestScriptExit(o);
			fcn_004432d0(saved, 1);
		}
		he_FreeAction(u);
		return;
	}
	if (*(int*) (u + 0xb0) != -1) {
		o = evt_FindScriptById(*(int*) (u + 0xb0));
		if (o != 0) {
			if (*(int*) o == FX_MAGIC && *(int*) (o + 4) == *(int*) (u + 0x10)) {
				return;
			}
			*(int*) (u + 0xb0) = -1;
		}
	}
	if (*(int*) (u + 0xb4) == 2) {
		o = evt_LoadGfxScript("LOCATIONS\\NEKROMANTENTURM\\NEBEL_DES_GRAUENS_GROSS.esc");
	} else if (*(int*) (u + 0xb4) == 1) {
		o = evt_LoadGfxScript("LOCATIONS\\NEKROMANTENTURM\\NEBEL_DES_GRAUENS_MITTEL.esc");
	} else {
		o = evt_LoadGfxScript("LOCATIONS\\NEKROMANTENTURM\\NEBEL_DES_GRAUENS_KLEIN.esc");
	}
	if (o == 0) {
		return;
	}
	*(int*) o = FX_MAGIC;
	*(int*) (o + 4) = *(int*) (u + 0x10);
	saved = d3_CurrentContextIndex;
	fcn_004432d0(0, 1);
	d3_TransformPoint(*(char**) (e + 0x61), *(char**) (e + 0x61) + 0x4c, pos);
	pos[1] += 500.0f;
	fcn_00428340(o, 3, (int) pos[0], (int) pos[1], (int) pos[2]);
	*(int*) (o + 0x104) = 0;
	fcn_004432d0(saved, 1);
	*(int*) (u + 0xb0) = *(int*) (o + 0x100);
}
