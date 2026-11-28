#include "Develop/DieGildeAddOn/game/event_callbacks.h"

#include <string.h>

extern char* g_14a9a28;
extern char str_empty[];

char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl cm_RequestKillSpieler(int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_SendCmdMessage(char*, char*, char*, char*);

#include "Develop/DieGildeAddOn/game/game_data.h"
extern char io_LastKeyScancode;
extern int tp_d2_SelectedControl;
extern int g_7747f0;

char* __cdecl gm_LookupEntityRecordById(int);
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl sb_LoadLocalizedSampleBankIfAllowed(char*, int);
void __cdecl msx_StartMusicIfAllowed(char*);
void __cdecl cut_StartSceneCutscene(char*);
int __cdecl cut_PlayEventScript(char*);
int __cdecl cut_WaitForTimeoutOrInput(int, int, int);
int __cdecl cut_RandMod(int);
void __cdecl d3snd_QueueSoundIfAllowed(int, int, char*, int, int);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
char* __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, char*);
void __cdecl d2_SetBildArgument(int, int);
void __cdecl d2_SelectControl(int);
char* __cdecl d2_GetControlValue(int);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl d2_DestroyForm(int);
void __cdecl cut_FadeToBlack(void);
void __cdecl evt_StopScriptIfActive(int);
void __cdecl cut_WaitForScript(int);
void __cdecl d3snd_StopTrackedVoices(void);
void __cdecl cut_UnloadSampleBank(int);
void __cdecl cut_CleanupCutscene(void);
void __cdecl msx_RestoreMusicIfAllowed(void);

char* __cdecl gm_LookupEntityRecordById(int);
float __cdecl gm_GetEntityHealth(char*);

/* ADDRESS: GOLD 0x004e0e90 */
/* ADDRESS: GOLDTL 0x004e27b0 */
int __cdecl gm_NotifyGeburt(char* event)
{
	char buf[0x200];
	char* parent;
	char* child;
	char* spouse;

	parent = gm_LookupEntityRecordById(*(int*) (event + 0x34));
	child = gm_LookupEntityRecordById(*(int*) (event + 0x38));
	if (parent == 0 || child == 0)
		return 0;
	spouse = gm_LookupEntityRecordById(*(int*) (parent + 0x5c));
	if (spouse == 0 || spouse[2] == 0xf) {
		cm_RequestKillSpieler(*(int*) (child + 4), 1);
		return 0;
	}
	if (parent[2] == 6 || parent[2] == 7) {
		io_FormatTextBuffer(buf, 0x11c1);
		strcat(buf, g_14a9a28);
		he_SendCmdMessage(parent, event, buf, str_empty);
	}
	return 1;
}

/* ADDRESS: GOLDTL 0x004e2890 */
void __cdecl cut_PlayBirthCutscene(char* event)
{
	char buf[0x10];
	char* parent;
	char* child;
	int snd;
	int esc;
	int n;
	int sc;
	int w;

	parent = gm_LookupEntityRecordById(*(int*) (event + 0x34));
	child = gm_LookupEntityRecordById(*(int*) (event + 0x38));
	if (parent == 0 || child == 0)
		return;
	{
		int v;

		v = 8;
		cm_BeginPacketFieldDelta(child, *(int*) (child + 4));
		cm_AppendPacketFieldDelta(1, 1, 2, &v);
		cm_RequestChangeAttribute();
	}
	cut_EventLoopFlags = 0x702c6;
	d2_SuppressOverlay = 1;
	snd = sb_LoadLocalizedSampleBankIfAllowed("GEBURT.sbf", 0);
	msx_StartMusicIfAllowed("cd2\\Geburt.mp3");
	cut_StartSceneCutscene("Geburt.ed3");
	esc = cut_PlayEventScript("cutscenes\\geburt\\enter_Geburt.esc");
	if (cut_WaitForTimeoutOrInput(0x1964, 0, 0) == 0) {
		if (parent[9] == 0) {
			if (child[9] == 0)
				d3snd_QueueSoundIfAllowed(-8, snd, "_GEBURT", cut_RandMod(2), 0);
			else
				d3snd_QueueSoundIfAllowed(-8, snd, "_GEBURT", cut_RandMod(2) + 2, 0);
		} else if (child[9] == 0) {
			d3snd_QueueSoundIfAllowed(-8, snd, "_GEBURT", cut_RandMod(2) + 4, 0);
		} else {
			d3snd_QueueSoundIfAllowed(-8, snd, "_GEBURT", cut_RandMod(2) + 6, 0);
		}
		if (cut_WaitForTimeoutOrInput(1000, 0, 0) == 0) {
			for (n = cut_RandMod(4) + 2; n > 0; n--)
				d3snd_QueueSoundIfAllowed(-8, snd, "_GEBURT_GESCHREI", cut_RandMod(5), gm_RandomMod(0x800) + 1000);
			cut_WaitForTimeoutOrInput(7000, 0, 0);
		}
	}
	sc = d2_LoadForm(0, 0, "cutscenes\\geburt");
	d2_CenterDialogWindows(sc);
	d2_SetForm(sc, 1);
	if (child[9] == 0)
		io_AppendText(0x1aae);
	else
		io_AppendText(0x1aaf);
	d2_SetForm(sc, 2);
	w = d2_GetWindowListItem(sc, 2, io_AppendText((int) "$L%t", child + 0x30));
	d2_SetBildArgument(w, 0xf);
	d2_SelectControl(w);
	for (;;) {
		if (io_LastKeyScancode == 0x1c || tp_d2_SelectedControl == 0) {
			strcpy(buf, d2_GetControlValue(w));
			if (buf[0] != 0)
				break;
			d2_SelectControl(w);
		}
		if (main_RunFrameLoop(0, cut_EventLoopFlags) == 0 || g_7747f0 != 0)
			break;
	}
	cm_BeginPacketFieldDelta(child, *(int*) (child + 4));
	cm_AppendPacketFieldDelta(1, 0x10, 0x30, buf);
	cm_RequestChangeAttribute();
	d2_DestroyForm(sc);
	cut_FadeToBlack();
	evt_StopScriptIfActive(esc);
	cut_WaitForScript(esc);
	d3snd_StopTrackedVoices();
	cut_UnloadSampleBank(snd);
	cut_StartTick = 0;
	cut_CleanupCutscene();
	msx_RestoreMusicIfAllowed();
	d2_SuppressOverlay = 0;
}

/* ADDRESS: GOLDTL 0x004e2b40 */
int __cdecl cut_CheckDeathCutscene(char* event)
{
	if (gm_GetEntityHealth(gm_LookupEntityRecordById(*(int*) (event + 0x34))) > 0.0f)
		return 0;
	return 1;
}
