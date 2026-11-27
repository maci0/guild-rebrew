


extern char g_68d00c[];
extern char g_6b5c60[];
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl cut_FadeToBlack(void);
void __cdecl sb_StopVoice(int, int);
void __cdecl fcn_004230e0(int);
void __cdecl d2_DestroyForm(int);
void __cdecl evt_StopScriptIfActive(int);
int __cdecl evt_StartGfxScript(char*, char*);
void __cdecl cut_WaitForScript(int);
void __cdecl cut_CleanupCutscene(void);
void __cdecl msx_RestoreMusicIfAllowed(void);

int __cdecl cut_ReleaseSceneContexts(int* scene)
{
	cut_FadeToBlack();
	if (scene[3] != 0)
		sb_StopVoice(scene[3], 0);
	scene[3] = 0;
	fcn_004230e0(scene[2]);
	if (scene[1] != -1)
		d2_DestroyForm(scene[1]);
	if (scene[0] != -1)
		evt_StopScriptIfActive(scene[0]);
	scene[0] = evt_StartGfxScript(g_68d00c, g_6b5c60);
	cut_WaitForScript(scene[0]);
	scene[0] = -1;
	scene[1] = -1;
	g_772f54 = 0;
	cut_CleanupCutscene();
	msx_RestoreMusicIfAllowed();
	d2_SuppressOverlay = 0;
	return 1;
}
