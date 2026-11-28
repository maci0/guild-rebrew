extern int d3_ActiveScene;
extern int g_699b10;
extern int g_6b86d8;
extern int g_6b86dc;
#include "Develop/DieGildeAddOn/game/game_data.h"



void __cdecl d3_TraverseSceneObjects(int, int, int, void*);
void __cdecl d3snd_StopSceneObjectSfxVoice(void);
void __cdecl d3snd_StopAllAmbientVoices(void);
char* __cdecl evt_FindScriptById(int);
void __cdecl evt_RequestScriptExit(char*);
void __cdecl evt_WaitForScriptExit(int);
void __cdecl ch_ClearSceneActionFinishCallbacks(int);
/* ADDRESS: GOLD 0x5136e0 */

/* ADDRESS: GOLDDE 0x00501940 */
void __cdecl d3_CleanupBuildingScene(void)
{
	char* p;

	d3_TraverseSceneObjects(d3_ActiveScene, 0, 0xa0, (void*) d3snd_StopSceneObjectSfxVoice);
	d3snd_StopAllAmbientVoices();
	g_6b86d8 = 0x400;
	g_6b86dc = 0x40;
	if (g_699b10 != -1) {
		p = evt_FindScriptById(g_699b10);
		if (p != 0) {
			evt_RequestScriptExit(p);
			evt_WaitForScriptExit(*(int*) (p + 0x100));
			g_699b10 = -1;
		}
	}
	ch_ClearSceneActionFinishCallbacks(d3_ActiveScene);
	g_67530c = -1;
}
