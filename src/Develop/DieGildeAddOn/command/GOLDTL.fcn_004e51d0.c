/*
 * Run one hotkey/command step for the current object (building or vehicle):
 * refresh the selected entity list, handle the "cut" action, then dispatch
 * the per-type handler and its associated window.
 */

#include <string.h>

#include "Develop/DieGildeAddOn/game/game_player.h"

typedef struct {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	char f14;
	char pad15[0x347];
} rec35c;
/* SIZE 0x35c */

typedef void (__cdecl* cmd_handler)(void*, int);

typedef struct {
	cmd_handler f0;
	cmd_handler f4;
	unsigned char f8;
	char pad9[0xb];
} cmd_entry;
/* SIZE 0x14 */

extern unsigned char g_7747b0;   /* 0x007747b0 */
extern int cut_EventLoopFlags;             /* 0x0068bfb8 */
extern int g_68bfbc;             /* 0x0068bfbc */
extern int g_6b5c60;             /* 0x006b5c60 */
extern int g_772f24;             /* 0x00772f24 */
extern int g_772f28;             /* 0x00772f28 */
extern int g_772f2c;             /* 0x00772f2c */
extern int cut_CurrentTick;             /* 0x00772f30 */
extern int cut_ClockDeadline;             /* 0x00772f34 */
extern int cut_ClockExpired;             /* 0x00772f38 */
extern int g_772f3c;             /* 0x00772f3c */
extern int g_14ac5e8;            /* 0x014ac5e8 */
extern int g_14ac5ec;            /* 0x014ac5ec */

extern char g_9b0e20[];          /* 0x009b0e20 */
extern cmd_entry g_9b0844[];     /* 0x009b0844 */

extern char s_68d580[]; /* "cut_type:%i" */
extern char s_68b300[]; /* 0x0068b300 */

int __cdecl cut_GetRandSeed(void);
void __cdecl cut_ResetEventSlots(unsigned char*);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl cm_RequestSysMessage(int, void*);
void __cdecl cm_WaitNetworkSyncBanner(int);
int __cdecl fcn_00533a40(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl cm_StageRawPacketPayload(int, rec35c*);
int __cdecl cm_RequestSendCutInfo(int, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
int __cdecl cut_AreAllPlayersDone(unsigned char*);
void __cdecl d2_AppendPendingPlayerNames(unsigned char*);
int __cdecl main_RunFrameLoop(int, int);
int __cdecl cut_FindPrevActiveSlot(unsigned char*, int);
void __cdecl fcn_004e6c60(int);
int __cdecl sprintf(char*, const char*, ...);

/* ADDRESS: GOLDTL 0x004e51d0 */
void __cdecl cut_RunTurnRound(unsigned char* cutscene, int id)
{
	rec35c c1;
	rec35c c2;
	struct {
		int head;
		char text[120];
	} msg;
	int saved;
	int i;
	unsigned char kind;
	int h;
	int ent;
	int pos;
	int found;
	rec35c* rec;
	int* ids;

	saved = cut_GetRandSeed();
	cut_ResetEventSlots(cutscene);
	if (g_7747b0 & 4) {
		if (*(int*) (cutscene + 0xc) == *(int*) ((unsigned int) g_774970 * 0x21c + 0x7f4ca4)) {
			if (g_772f3c != 0) {
				goto label_4e526f;
			}
			memset(&msg, 0, sizeof(msg));
			msg.head = *(int*) cutscene;
			sprintf(msg.text, s_68d580, cutscene[8]);
			cm_RequestSysMessage(0x11, &msg);
		}
label_4e526f:
		if (g_772f3c == 0) {
			cm_WaitNetworkSyncBanner(g_14ac5e8);
		}
	}
	fcn_00533a40((int) &g_6b5c60);
	if (g_7747b0 & 8) {
		for (i = 0; i < (int) cutscene[0x30]; i++) {
			g_772f28 = i;
			if (*(int*) (cutscene + 0x34 + i * 4) == -1) {
				continue;
			}
			g_772f24 = gm_LookupEntityRecordById(*(int*) (cutscene + 0x34 + i * 4));
			if (g_772f24 == 0) {
				*(int*) (cutscene + 0x34 + i * 4) = -1;
				continue;
			}
			rec = &((rec35c*) g_9b0e20)[i];
			if (*(unsigned char*) (g_772f24 + 2) == 6) {
				cut_ClockDeadline = g_68bfbc + cut_CurrentTick;
				cut_ClockExpired = 0;
				((cmd_entry*) g_9b0844)[cutscene[8]].f0(rec, id);
			} else if (((cmd_entry*) g_9b0844)[cutscene[8]].f4 != 0) {
				((cmd_entry*) g_9b0844)[cutscene[8]].f4(rec, id);
			}
			d2_SetForm(*(int*) (cutscene + 0x2c), 0);
			io_AppendText((int) ((char*) rec + 0x14));
			io_AppendText((int) s_68b300);
		}
	} else if (g_7747b0 & 4) {
		g_772f24 = (unsigned int) g_774970 * 0x21c + 0x7f4ca0;
		kind = *(unsigned char*) ((unsigned int) cutscene[8] * 0x14 + 0x9b084c);
		if (kind == 1) {
			if (*(int*) (cutscene + 0xc) == *(int*) ((unsigned int) g_774970 * 0x21c + 0x7f4ca4)) {
				rec = (rec35c*) g_9b0e20;
				ids = (int*) (cutscene + 0x34);
				for (i = 0; i < (int) cutscene[0x30]; i++, ids++) {
					ent = gm_LookupEntityRecordById(*ids);
					if (ent != 0
							&& *(unsigned char*) (ent + 2) != 6
							&& *(unsigned char*) (ent + 2) != 7
							&& rec->f8 == 0) {
						c1 = *rec;
						g_772f24 = ent;
						if (((cmd_entry*) g_9b0844)[cutscene[8]].f4 != 0) {
							((cmd_entry*) g_9b0844)[cutscene[8]].f4(&c1, id);
						}
						c1.f8 = 1;
						c1.fc = 0;
						cm_StageRawPacketPayload(0x35c, &c1);
						h = cm_RequestSendCutInfo(*(int*) (ent + 4), *(int*) cutscene);
						while (cm_GetCommandStatus(h) == 0) {
							cm_StepCommandQueue();
						}
						d2_AppendPendingPlayerNames(cutscene);
						main_RunFrameLoop(0, cut_EventLoopFlags | 0x8000);
					}
					rec++;
				}
			}
			g_772f24 = (unsigned int) g_774970 * 0x21c + 0x7f4ca0;
			ent = *(int*) (g_772f24 + 4);
			for (i = 0; i < (int) cutscene[0x30]; i++) {
				if (*(int*) (cutscene + 0x34 + i * 4) == ent) {
					c1 = ((rec35c*) g_9b0e20)[i];
					cut_ClockDeadline = g_68bfbc + cut_CurrentTick;
					cut_ClockExpired = 0;
					((cmd_entry*) g_9b0844)[cutscene[8]].f0(&c1, id);
					c1.f8 = 1;
					c1.fc = 0;
					cm_StageRawPacketPayload(0x35c, &c1);
					h = cm_RequestSendCutInfo(*(int*) (g_772f24 + 4), *(int*) cutscene);
					while (cm_GetCommandStatus(h) == 0) {
						cm_StepCommandQueue();
					}
					break;
				}
			}
			while (cut_AreAllPlayersDone(cutscene) == 0) {
				d2_AppendPendingPlayerNames(cutscene);
				fcn_00533a40(g_14ac5ec);
				main_RunFrameLoop(0, cut_EventLoopFlags | 0x8000);
			}
		} else if (kind == 0) {
			pos = -1;
			found = -1;
			for (i = 0; i < (int) cutscene[0x30]; i++) {
				if (*(int*) (cutscene + 0x34 + i * 4) == *(int*) ((unsigned int) g_774970 * 0x21c + 0x7f4ca4)) {
					pos = i;
					if (pos != -1) {
						found = cut_FindPrevActiveSlot(cutscene, pos);
					}
					break;
				}
			}
			while (cut_AreAllPlayersDone(cutscene) == 0) {
				d2_AppendPendingPlayerNames(cutscene);
				main_RunFrameLoop(0, cut_EventLoopFlags | 0x8000);
				if (pos != -1
						&& (pos == 0 || ((rec35c*) g_9b0e20)[found].f8 == 1)
						&& ((rec35c*) g_9b0e20)[pos].f8 == 0) {
					g_772f28 = pos;
					c1 = ((rec35c*) g_9b0e20)[pos];
					g_772f24 = gm_LookupEntityRecordById(*(int*) (cutscene + 0x34 + pos * 4));
					d2_AppendPendingPlayerNames(cutscene);
					cut_ClockDeadline = g_68bfbc + cut_CurrentTick;
					cut_ClockExpired = 0;
					((cmd_entry*) g_9b0844)[cutscene[8]].f0(&c1, id);
					c1.f8 = 1;
					c1.fc = 0;
					cm_StageRawPacketPayload(0x35c, &c1);
					h = cm_RequestSendCutInfo(*(int*) (g_772f24 + 4), *(int*) cutscene);
					while (cm_GetCommandStatus(h) == 0) {
						cm_StepCommandQueue();
					}
					d2_AppendPendingPlayerNames(cutscene);
					main_RunFrameLoop(0, cut_EventLoopFlags | 0x8000);
				}
				if (*(int*) (cutscene + 0xc) == *(int*) ((unsigned int) g_774970 * 0x21c + 0x7f4ca4)) {
					for (i = 0; i < (int) cutscene[0x30]; i++) {
						ent = gm_LookupEntityRecordById(*(int*) (cutscene + 0x34 + i * 4));
						if (ent != 0
								&& *(unsigned char*) (ent + 2) != 6
								&& *(unsigned char*) (ent + 2) != 7
								&& (i == 0 || ((rec35c*) g_9b0e20)[cut_FindPrevActiveSlot(cutscene, i)].f8 == 1)
								&& ((rec35c*) g_9b0e20)[i].f8 == 0) {
							g_772f28 = i;
							c2 = ((rec35c*) g_9b0e20)[i];
							g_772f24 = ent;
							if (((cmd_entry*) g_9b0844)[cutscene[8]].f4 != 0) {
								((cmd_entry*) g_9b0844)[cutscene[8]].f4(&c2, id);
							}
							c2.f8 = 1;
							c2.fc = 0;
							cm_StageRawPacketPayload(0x35c, &c2);
							h = cm_RequestSendCutInfo(*(int*) (ent + 4), *(int*) cutscene);
							while (cm_GetCommandStatus(h) == 0) {
								cm_StepCommandQueue();
							}
							break;
						}
					}
				}
			}
			d2_AppendPendingPlayerNames(cutscene);
			main_RunFrameLoop(0, cut_EventLoopFlags | 0x8000);
		}
	}
	g_772f2c += 1;
	fcn_004e6c60(saved);
}
