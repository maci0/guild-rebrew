__declspec(dllimport) void __stdcall Sleep(unsigned long);
#include "Develop/DieGildeAddOn/game/building_prototype.h"
int __cdecl fcn_0043a9c0();
int __cdecl fcn_0043aa30();
int __cdecl d3_SelectSceneContext();
int __cdecl fcn_0046ac30();
int __cdecl fcn_00469e30();
int __cdecl d2_AddElementToWindow();
int __cdecl fcn_00470820();
int __cdecl fcn_00471d80();
int __cdecl fcn_00471e30();
int __cdecl d2_GetWindowListItem();
int __cdecl fcn_00472380();
int __cdecl fcn_00472640();
int __cdecl d2_SetForm();
int __cdecl fcn_00476970();
int __cdecl fcn_00495890();
int __cdecl fcn_004ad8c0();
int __cdecl fcn_004b3aa0();
int __cdecl plt_UpdatePlantStages();
int __cdecl d3snd_QueueSound();
int __cdecl cm_RequestCopyEntityData();
int __cdecl fcn_004e4f10();
char __cdecl cut_RunPendingCutscenes(int);
int __cdecl srv_FormatStatEntity();
int __cdecl fcn_004eafe0();
int __cdecl fcn_004f5830();
int __cdecl fcn_004f4d10();
int __cdecl fcn_004facb0();
int __cdecl fcn_004fb390();
int __cdecl fcn_004fb630();
void __cdecl fcn_004fb650(int, int, int, float);
int __cdecl fcn_004fb7a0();
int __cdecl fcn_004fcc20();
int __cdecl gm_CollectAllTaxes();
int __cdecl fcn_004fd280();
int __cdecl fcn_004ff0f0();
int __cdecl gm_PackGameTime();
int __cdecl fcn_005016c0();
int __cdecl gm_FindNextFilteredEntity();
int __cdecl gm_StartFilteredEntitySearch();
int __cdecl init_AllocateGebaeudeSceneSlot();
int __cdecl io_AppendText();
int __cdecl fcn_00522c0();
int __cdecl fcn_00526120();
int __cdecl fcn_005356b0();
int __cdecl sv_WaitForNetworkSync();
int __cdecl main_RunFrameLoop();
int __cdecl gm_ApplyHourlyEntityUpdates();
int __cdecl fcn_005422c0();
int __cdecl fcn_005435d0();
int __cdecl main_PlayOutroMovie();
int __cdecl he_DispatchFlaggedEvents();
int __cdecl fcn_0053f100();
int __cdecl fcn_00546f80();
int __cdecl fcn_00547770();
int __cdecl fcn_005490a0();
int __cdecl fcn_005490d0();
int __cdecl io_FormatTextBuffer();
int __cdecl d2_CreateScrollPerga();
int __cdecl fcn_00535960();
int __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
#include "client_types.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
typedef struct ResetProto { unsigned char kind; unsigned char rest[0x24c]; } ResetProto;
extern int g_6a3420; extern int g_774954; extern char g_774965; extern int g_14cbca0; extern int d2_SuppressOverlay; extern double g_662cc0;
extern int g_1040480; extern int g_1040484; extern int g_1040488; extern int g_104048c; extern int d2_ScreenHeight; extern int g_1040494;
/* ADDRESS: GOLDTL 0x00543080 */
void __cdecl fcn_00543080(void)
{
	int v1;
	int v2;
	unsigned char* v3;
	unsigned int* v4;
	int v5;
	int v11;
	char messageText[256];
	char v7[12];
	char* v9;
	Rec24_99f5a0 st;
	BUILDING_PROTOTYPE* proto;

	v5 = -1;
	v1 = *(unsigned char*) &g_772d10;
	fcn_004fa750();
	v11 = 0;
	do {
		srv_FormatStatEntity(&((ENTITY_RECORD*) g_7f4ca0)[v11]);
		*(unsigned int*) &((ENTITY_RECORD*) g_7f4ca0)[v11].unk_198[0x30] &= 0xe0874703;
		((ENTITY_RECORD*) g_7f4ca0)[v11].entity_flags &= 0x3d31ffc7;
		if (((ENTITY_RECORD*) g_7f4ca0)[v11].entity_state == 6) {
			v5 = v11;
		}
		v11 += 1;
	} while (v11 < 768);
	*(short*) &g_774970 = (short) v5;
	he_DispatchFlaggedEvents();
	if (!(g_7747b0 & 4) && (unsigned short) gm_RandomMod(10) > 6) {
		v11 = fcn_005435d0();
		while (v11 != 1) {
			d2_SuppressOverlay = 0;
			*(int*) &main_LoopFlags = 0x24087;
			io_FormatTextBuffer(messageText, 0x79);
			if (!fcn_00526120(messageText, 1)) {
				g_774954 = 1;
				fcn_005356b0(0x5438c0);
				return;
			}
			fcn_0046ac30();
			Sleep(1000);
			v11 = fcn_005435d0();
		}
	}
	*(int*) &main_LoopFlags = 0x24087;
	if (g_7747b0 & 4) {
		sv_WaitForNetworkSync(0x24087);
	}
	fcn_004e4f10(0);
	if (cut_RunPendingCutscenes(v5) && g_6a3420) {
		g_1040488 = 0;
		g_1040480 = g_1040494;
		g_1040484 = 0;
		g_104048c = d2_ScreenHeight;
		fcn_00476970(*(int*) &g_77250c);
		fcn_00469e30(0x79d);
	}
	fcn_0053f100();
	fcn_00546f80();
	if (g_6a3420) {
		v2 = fcn_00470820(0, 0, 0x6a43ac);
		fcn_00471d80(v2, 3);
		d2_SetForm(v2, 1);
		io_AppendText(0x7d);
		gm_PackGameTime(0x7f4c00, v7);
		d2_SetForm(v2, 0);
		fcn_00471e30(v2);
	}
	v3 = (unsigned char*) gm_StartFilteredEntitySearch(1, 6);
	while (v3) {
		proto = &((BUILDING_PROTOTYPE*) lpGebaeudePROT)[*v3];
		if (*v3 == 0x1e) {
			v5 = init_AllocateGebaeudeSceneSlot(v3);
			if (v5 != -1) {
				v2 = d3_CurrentContextIndex;
				d3_SelectSceneContext((int) *(char*) (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*v3].category + (unsigned long)&g_7f3b00), 1);
				fcn_0043aa30(3);
				plt_UpdatePlantStages(*(unsigned int*) &v3[0x71]);
				fcn_0043a9c0(3);
				d3_SelectSceneContext(v2, 1);
			}
		} else if (proto->category == 7) {
			*(int*)(v3 + 0x69) = 0;
		}
		v3 = (unsigned char*) gm_FindNextFilteredEntity();
	}
	v5 = 0;
	fcn_005016c0();
	fcn_004facb0();
	if ((*(int*) &g_77494c & 8) || g_14cbca0 == -1) {
		fcn_004f5830();
		fcn_00535960();
		Sleep(100);
		v9 = (char*) 0x7f4ca8;
		do {
			if (*(unsigned short*) &v9[-8] != 0xffff && *v9) {
				fcn_005422c0(v5);
			}
			v9 = &v9[0x21c];
			v5 += 1;
		} while ((int) v9 < 0x85a0a8);
		fcn_00535960();
		Sleep(100);
		fcn_004ff0f0();
		fcn_00535960();
		Sleep(100);
		fcn_004fd0a0();
		fcn_00535960();
		Sleep(100);
		fcn_004fd280(3);
		fcn_004fcc20();
		fcn_00535960();
		Sleep(100);
		gm_CollectAllTaxes();
		fcn_004eafe0();
		fcn_00535960();
		Sleep(100);
		fcn_005490a0();
		fcn_005490d0();
		fcn_00535960();
		Sleep(100);
		fcn_004f4d10();
		fcn_00535960();
		Sleep(100);
		fcn_00495890();
		fcn_00535960();
		Sleep(100);
		fcn_004fb390();
		fcn_004fb630(&st);
		if (st.head == -1) {
			fcn_004fb650(1, 0x3f800000, 0x3f000000, (float)(10.0 - (double)(4 - g_7747b4) * g_662cc0));
		} else {
			fcn_004fb7a0();
		}
		fcn_00547770();
		fcn_00535960();
		Sleep(100);
		v4 = (unsigned int*) &g_7f4ca4;
		do {
			cm_RequestCopyEntityData(0xffffffff, *v4, 0, 3);
			v4 = &v4[0x87];
		} while ((int) v4 < 0x85a0a4);
		cm_RequestCopyEntityData(0xffffffff, 0xffffffff, 0, 4);
		fcn_004ad8c0();
	} else {
		fcn_004fd280(2);
	}
	v4 = (unsigned int*) 0x7f4e8c;
	do {
		*v4 = 0;
		v4 = &v4[0x87];
	} while ((int) v4 < 0x85a28c);
	if (g_6a3420) {
		if (g_774965 && !(g_7747b0 & 4)) {
			v2 = d2_CreateScrollPerga();
			d2_SetForm(v2, 2);
			io_AppendText(0x7d);
			d2_SetForm(v2, 1);
			io_AppendText(0x1ba0, *(int*) &g_774970 & 0xffff, *(int*) &g_774970 & 0xffff);
			d3snd_QueueSound(0xfffffff9, 0, 0x6a438c, 0xffffffff, 0);
			v5 = main_RunFrameLoop(0x543080, 0x66087);
			while (v5) {
				if (*(int*) &g_100f1dc == 2) {
					g_774654 = 1;
				}
				v5 = main_RunFrameLoop(0x543080, 0x66087);
			}
			fcn_00471e30(v2);
			main_PlayOutroMovie();
			g_774954 = 1;
		}
		if (g_6a3420 && !g_774954) {
			if (!(*(int*) &g_77494c & 8) && g_14cbca0 != -1) {
				fcn_004b3aa0(0);
			} else {
				fcn_004b3aa0(1);
			}
		}
	}
	if ((*(int*) &g_77494c & 8) || g_14cbca0 == -1) {
		gm_ApplyHourlyEntityUpdates();
	}
	*(char*) &g_772d10 = (char) v1;
}
