


extern int g_774714;
extern int g_774950;
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_774958;
extern char g_774965;
extern int g_7749cc;
extern int g_7747bc;
extern int g_7e2470;
extern int g_7747c0;
extern int g_7747cc;
extern int g_6b5c2c;
extern int g_774978;
extern char* d2_SelectedBuilding;
extern char* sv_SelectedBuilding;
extern char* d2_VisitedBuilding;
extern unsigned char* d2_InteriorBuilding;

void __cdecl he_InitEventSystem(void);
void __cdecl gm_AdvanceGameClock(void);
#include "Develop/DieGildeAddOn/game/client_timer.h"
void __cdecl he_TickEventDeals(void);
void __cdecl cm_InitCrimeRecords(void);
void __cdecl gm_ResetCityStats(void);
int __cdecl d3_AcquireModel(char*, char*);
int __cdecl sb_LoadSampleBank(char*, int);
void __cdecl msx_SetFadeDuration(int);
void __cdecl d2_CreateEventBar(void);
void __cdecl d3_ClearSceneObjectCache(void);
void __cdecl d2_ClearStatusTextSlots(void);
void __cdecl fcn_005c80c0(void);
void __cdecl gm_AllocAmbientAnimals(void);
void __cdecl ch_ResetGridAndUniverseCache(void);
void __cdecl d2_ResetBookmarkSlots(void);
void __cdecl d3_ResetSceneContextIndices(void);
void __cdecl cut_InitCutsceneRegistry(void);

/* ADDRESS: GOLDDE 0x00526430 */
void __cdecl gm_InitGameSession(void)
{
	he_InitEventSystem();
	g_774714 = 1;
	g_774950 = 1;
	(*(int*)&gm_GameTime) = 2;
	g_774954 = 0;
	g_774958 = 0;
	g_774965 = 0;
	(*(int*)g_68a9cc) = 2;
	tb_OpenFunction(gm_AdvanceGameClock, 0x47);
	tb_SetCallbackPaused(gm_AdvanceGameClock, 1);
	he_TickEventDeals();
	cm_InitCrimeRecords();
	gm_ResetCityStats();
	g_7749cc = d3_AcquireModel("Buch", "Buch");
	if (d3snd_SoundEnabled != 0) {
		g_7747bc = sb_LoadSampleBank("natur\\regen.sbf", 0);
		g_7e2470 = sb_LoadSampleBank("natur\\wind.sbf", 0);
		g_7747c0 = sb_LoadSampleBank("natur\\blitzunddonner.sbf", 0);
		g_7747c4 = sb_LoadSampleBank("objekte\\buecher.sbf", 0);
		g_7747c8 = sb_LoadSampleBank("objekte\\TuerenUndRaeume.sbf", 0);
		g_7747cc = sb_LoadSampleBank("objekte\\Transporter.sbf", 0);
		g_6b5c2c = sb_LoadSampleBank("Lebewesen\\schritte.sbf", 1);
	}
	msx_SetFadeDuration(3000);
	d2_CreateEventBar();
	d3_ClearSceneObjectCache();
	d2_ClearStatusTextSlots();
	g_774978 = 0;
	(*(int*)&d2_SelectedBuilding) = 0;
	(*(int*)&sv_SelectedBuilding) = 0;
	(*(int*)&d2_VisitedBuilding) = 0;
	(*(int*)&d2_InteriorBuilding) = 0;
	fcn_005c80c0();
	gm_AllocAmbientAnimals();
	ch_ResetGridAndUniverseCache();
	d2_ResetBookmarkSlots();
	d3_ResetSceneContextIndices();
	cut_InitCutsceneRegistry();
}
