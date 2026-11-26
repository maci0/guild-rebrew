

#include "client_types.h"


// SIZE 0xe

#include "Develop/DieGildeAddOn/game/entity_record.h"








typedef struct {
	char b[0x2f4];
} Row5a92;
// SIZE 0x2f4


#include "Develop/DieGildeAddOn/game/game_player.h"

extern pos14_7f4c00 gm_GameTime;
extern unsigned char g_773d75;
extern trade_868080 g_868080[];
extern unsigned char g_6a375c;
extern char g_6aae78[];
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

int __cdecl gm_AccumulateTyped2(ENTITY_RECORD*);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00526120(char*, int);
void __cdecl d3_EndCameraAndUiMode(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl gm_CheckEntityStock(ENTITY_RECORD*, int, unsigned char);
int __cdecl d2_IsTutorialInactive(void);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
void __cdecl cm_SendCopyEntityData(char*);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, int, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_RunBuergerrechtDialog(char* p)
{
	ENTITY_RECORD* ent;
	char* q;
	int h;
	int ok;
	int n;
	int i;
	pos14_7f4c00 st;

	ent = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]);
	n = gm_AccumulateTyped2(ent);
	q = fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x115);
	ok = 0;
	if (n < 0x3e80) {
		char text[0x100];

		io_FormatTextBuffer(text, 0x1a00);
		fcn_00526120(text, ok);
		d3_EndCameraAndUiMode();
		return;
	}
	h = fcn_00470820(0, 0, g_6aae78);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	io_AppendText(0x19fe, ent->entity_index, 0x3e80, &((Row5a92*)g_868080)[g_773d75]);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2 && gm_CheckEntityStock(ent, 0x3e80, g_773d75) != 0) {
				char msg[0xf8];
				char text[0x200];

				n = 0;
				{
					char* fdest;
					int flen;

					flen = sizeof(msg);
					fdest = msg;
					__asm {
						mov edi, fdest
						mov ebx, flen
						xor eax, eax
						lea ecx, [edi+edi*2]
						and ecx, 3
						sub ebx, ecx
						jle short L1
						rep stosb
						mov ecx, ebx
						and ebx, 3
						shr ecx, 2
						rep stosd
					L1:
						add ecx, ebx
						rep stosb
					}
				}
				*(int*) (msg + 8) = ent->entity_id;
				msg[4] = 0x69;
				*(int*) (msg + 0xc) = -1;
				msg[0x36] = 9;
				*(pos14_7f4c00*) (msg + 0x28) = (*(pos14_7f4c00*)&gm_GameTime);
				if (d2_IsTutorialInactive() == 0) {
					gm_AddTime((pos14_7f4c00*) (msg + 0x28), 0, 5, 0);
				} else {
					gm_AddTime((pos14_7f4c00*) (msg + 0x28), gm_RandomMod(3) + 1, 0, 0);
				}
				st = *(pos14_7f4c00*) (msg + 0x28);
				msg[0x58] = 2;
				*(int*) (msg + 0x5c) = ent->entity_id;
				cm_SendCopyEntityData(msg);
				for (i = 0; i < 768 && n < g_6a375c; i++) {
					if ((((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type == 6 || ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type == 7) && ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i]) != ent) {
						{
							char* fdest;
							int flen;

							flen = sizeof(msg);
							fdest = msg;
							__asm {
								mov edi, fdest
								mov ebx, flen
								xor eax, eax
								lea ecx, [edi+edi*2]
								and ecx, 3
								sub ebx, ecx
								jle short L2
								rep stosb
								mov ecx, ebx
								and ebx, 3
								shr ecx, 2
								rep stosd
							L2:
								add ecx, ebx
								rep stosb
							}
						}
						*(int*) (msg + 8) = ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id;
						msg[4] = 0x69;
						*(int*) (msg + 0xc) = -1;
						msg[0x36] = 9;
						*(pos14_7f4c00*) (msg + 0x28) = st;
						msg[0x58] = 2;
						*(int*) (msg + 0x5c) = ent->entity_id;
						cm_SendCopyEntityData(msg);
						n++;
					}
				}
				cm_RequestTransferCurrencyNoKill(*(int*) (q + 2), ent->entity_id, 0, 0x3e80);
				cm_RequestChangeBits(ent->entity_id, 0x1c8, 4, 0, 0x4000);
				io_FormatTextBuffer(text, 0x19ff);
				fcn_0057e880(0x2e, 0, 0, 0);
				ok = 1;
				fcn_00526120(text, 0);
			}
			g_774654 = 1;
		}
	} while (main_RunFrameLoop(d2_RunBuergerrechtDialog, 0x677c7) != 0);
	d2_DestroyForm(h);
	d3_EndCameraAndUiMode();
	if (ok) {
		fcn_0057e880(0x2e, 0, 1, 0);
	}
}
