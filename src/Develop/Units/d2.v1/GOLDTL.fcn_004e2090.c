#include <stdio.h>
extern int cut_EventLoopFlags, d2_SuppressOverlay;
extern char g_6b5c60[];
extern char g_6811b0[];

char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_IncrementMissionActionCount(char*, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
char* __cdecl gm_SelectEntityHeadSet(int);
int __cdecl fcn_004e4ae0(char*, int);
void __cdecl fcn_004e4730(char*);
void __cdecl msx_StartMusicIfAllowed(char*);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl d2_SetFormVisibility(int, int);
int __cdecl evt_StartGfxScript(char*, char*);
int __cdecl cut_WaitForTimeoutOrInput(int, int, int*);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char* fmt, ...);
int __cdecl fcn_004e4b20(int, int, char*, int);
int __cdecl sb_CheckVoicePlaying(int);
int __cdecl cut_WaitForScriptOrInput(int, void*, int*);
int __cdecl cut_ReleaseSceneContexts(int*);

/* ADDRESS: GOLDTL 0x004e2090 */
void __cdecl fcn_004e2090(int event)
{
	unsigned short* entity1;
	unsigned short* entity2;
	unsigned short* swapEntity;
	char text[256];
	int value;
	int otherName;
	int scene[4];





	entity1 = (unsigned short*) gm_LookupEntityRecordById(*(int*) (event + 0x34));
	if (entity1 == 0) {
		return;
	}
	entity2 = (unsigned short*) gm_LookupEntityRecordById(*(int*) (event + 0x38));
	if (entity2 == 0) {
		return;
	}
	if (((char*) entity1)[2] == 6) {
		gm_IncrementMissionActionCount((char*) entity1, 0x28);
	}
	if (((char*) entity2)[2] == 6) {
		gm_IncrementMissionActionCount((char*) entity2, 0x28);
	}
	cut_EventLoopFlags = 0x702c6;
	d2_SuppressOverlay = 1;
	cm_RequestChangeBits(*(int*) &entity1[2], 0x1c8, 4, 0, 0x40000);
	cm_RequestChangeBits(*(int*) &entity2[2], 0x1c8, 4, 0, 0x40000);
	value = (int) gm_SelectEntityHeadSet(*entity1);
	otherName = (int) gm_SelectEntityHeadSet(*entity2);
	if (((char*) entity1)[9] == 0) {
		sprintf(text, "%s %s %i", (char*) (value + 4), (char*) (otherName + 4), 1);
	} else {
		swapEntity = entity2; entity2 = entity1; entity1 = swapEntity;
		sprintf(text, "%s %s %i", (char*) (otherName + 4), (char*) (value + 4), 1);
	}




	scene[2] = fcn_004e4ae0("ADDON\\HOCHZEIT_NEU.sbf", 0);
	fcn_004e4730("KIRCHE_HOCHZEIT.ed3");
	msx_StartMusicIfAllowed("cd2\\Hochzeit.mp3");
	scene[1] = d2_LoadForm(0, 0, "cutscenes\\hochzeit");
	fcn_00471d80(scene[1], 3);
	d2_SetFormVisibility(scene[1], 0);
	scene[0] = evt_StartGfxScript("cutscenes\\hochzeit\\hochzeit-create.esc", text);
	scene[0] = evt_StartGfxScript("cutscenes\\hochzeit\\hochzeit-intro.esc", g_6b5c60);
	scene[0] = evt_StartGfxScript("cutscenes\\hochzeit\\hochzeit-reden1.esc", g_6b5c60);
	if (cut_WaitForTimeoutOrInput(0x5dc, (int) cut_ReleaseSceneContexts, scene)) {
		return;
	}
	d2_SetFormVisibility(scene[1], 1);
	d2_SetForm(scene[1], 0);
	io_AppendText((char*) 0x1aa9, *entity1, *entity2);
	scene[3] = fcn_004e4b20(0xfffffff9, scene[2], "_HOCHZEIT_NEU_MAIN_00", 0);
	value = sb_CheckVoicePlaying(scene[3]);
	while (value != 0) {
		if (cut_WaitForTimeoutOrInput(1000, (int) cut_ReleaseSceneContexts, scene)) {
			return;
		}
		value = sb_CheckVoicePlaying(scene[3]);
	}
	if (cut_WaitForTimeoutOrInput(1000, (int) cut_ReleaseSceneContexts, scene)) {
		return;
	}
	d2_SetForm(scene[1], 0);
	io_AppendText(g_6811b0);
	d2_SetFormVisibility(scene[1], 0);
	value = cut_WaitForScriptOrInput(scene[0], (void*) cut_ReleaseSceneContexts, scene);
	if (value != 0) {
		return;
	}
	if (cut_WaitForTimeoutOrInput(1000, (int) cut_ReleaseSceneContexts, scene)) {
		return;
	}
	scene[0] = evt_StartGfxScript("cutscenes\\hochzeit\\hochzeit-reden2.esc", g_6b5c60);
	d2_SetForm(scene[1], 0);
	d2_SetFormVisibility(scene[1], 1);
	io_AppendText((char*) 0x1aac, *entity1, *entity2);
	scene[3] = fcn_004e4b20(0xfffffff9, scene[2], "_HOCHZEIT_NEU_MAIN_03", 0);
	value = sb_CheckVoicePlaying(scene[3]);
	while (value != 0) {
		if (cut_WaitForTimeoutOrInput(1000, (int) cut_ReleaseSceneContexts, scene)) {
			return;
		}
		value = sb_CheckVoicePlaying(scene[3]);
	}
	if (cut_WaitForTimeoutOrInput(1000, (int) cut_ReleaseSceneContexts, scene)) {
		return;
	}
	d2_SetForm(scene[1], 0);
	io_AppendText(g_6811b0);
	d2_SetFormVisibility(scene[1], 0);
	if (cut_WaitForTimeoutOrInput(500, (int) cut_ReleaseSceneContexts, scene)) {
		return;
	}
	d2_SetFormVisibility(scene[1], 1);
	d2_SetForm(scene[1], 0);
	io_AppendText((char*) 0x1aab);
	scene[3] = fcn_004e4b20(0xfffffff9, scene[2], "_HOCHZEIT_NEU_M", 0);
	value = sb_CheckVoicePlaying(scene[3]);
	while (value != 0) {
		if (cut_WaitForTimeoutOrInput(1000, (int) cut_ReleaseSceneContexts, scene)) {
			return;
		}
		value = sb_CheckVoicePlaying(scene[3]);
	}
	if (cut_WaitForTimeoutOrInput(1000, (int) cut_ReleaseSceneContexts, scene)) {
		return;
	}
	value = cut_WaitForScriptOrInput(scene[0], (void*) cut_ReleaseSceneContexts, scene);
	if (value != 0) {
		return;
	}
	scene[0] = evt_StartGfxScript("cutscenes\\hochzeit\\hochzeit-reden3.esc", g_6b5c60);
	d2_SetFormVisibility(scene[1], 0);
	d2_SetForm(scene[1], 0);
	io_AppendText(g_6811b0);
	if (cut_WaitForTimeoutOrInput(0x5dc, (int) cut_ReleaseSceneContexts, scene)) {
		return;
	}
	d2_SetFormVisibility(scene[1], 1);
	d2_SetForm(scene[1], 0);
	io_AppendText((char*) 0x1aaa, *entity2, *entity1);
	scene[3] = fcn_004e4b20(0xfffffff9, scene[2], "_HOCHZEIT_NEU_MAIN_01", 0);
	value = sb_CheckVoicePlaying(scene[3]);
	while (value != 0) {
		if (cut_WaitForTimeoutOrInput(1000, (int) cut_ReleaseSceneContexts, scene)) {
			return;
		}
		value = sb_CheckVoicePlaying(scene[3]);
	}
	if (cut_WaitForTimeoutOrInput(500, (int) cut_ReleaseSceneContexts, scene)) {
		return;
	}
	d2_SetFormVisibility(scene[1], 0);
	d2_SetForm(scene[1], 0);
	io_AppendText(g_6811b0);
	if (cut_WaitForTimeoutOrInput(500, (int) cut_ReleaseSceneContexts, scene)) {
		return;
	}
	d2_SetFormVisibility(scene[1], 1);
	d2_SetForm(scene[1], 0);
	io_AppendText((char*) 0x1aab);
	scene[3] = fcn_004e4b20(0xfffffff9, scene[2], "_HOCHZEIT_NEU_W", 0);
	value = sb_CheckVoicePlaying(scene[3]);
	while (value != 0) {
		if (cut_WaitForTimeoutOrInput(1000, (int) cut_ReleaseSceneContexts, scene)) {
			return;
		}
		value = sb_CheckVoicePlaying(scene[3]);
	}
	if (cut_WaitForTimeoutOrInput(500, (int) cut_ReleaseSceneContexts, scene)) {
		return;
	}
	value = cut_WaitForScriptOrInput(scene[0], (void*) cut_ReleaseSceneContexts, scene);
	if (value != 0) {
		return;
	}
	scene[0] = evt_StartGfxScript("cutscenes\\hochzeit\\hochzeit-reden4.esc", g_6b5c60);
	d2_SetForm(scene[1], 0);
	io_AppendText((char*) 0x1aad);
	scene[3] = fcn_004e4b20(0xfffffff9, scene[2], "_HOCHZEIT_NEU_MAIN_04", 0);
	value = sb_CheckVoicePlaying(scene[3]);
	while (value != 0) {
		if (cut_WaitForTimeoutOrInput(1000, (int) cut_ReleaseSceneContexts, scene)) {
			return;
		}
		value = sb_CheckVoicePlaying(scene[3]);
	}
	if (cut_WaitForTimeoutOrInput(500, (int) cut_ReleaseSceneContexts, scene)) {
		return;
	}
	d2_SetFormVisibility(scene[1], 0);
	d2_SetForm(scene[1], 0);
	io_AppendText(g_6811b0);
	if (cut_WaitForScriptOrInput(scene[0], (void*) cut_ReleaseSceneContexts, scene)) {
		return;
	}
	scene[0] = 0xffffffff;
	cut_ReleaseSceneContexts(scene);
}
