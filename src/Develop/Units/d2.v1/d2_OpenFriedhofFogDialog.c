/* Open the arena betting page: query the match, build the layout and poll
 * input until the page is closed. */
#include "Develop/DieGildeAddOn/game/client_data.h"
extern int d2_DialogCloseRequested;
void __cdecl io_FormatTextBuffer(char*, int, int);
int __cdecl he_StartHandlungSearch(int, int, int, int, int);
void __cdecl d3snd_QueueSound(int, int, char*, int, int);
void __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl d2_RunCityScrollMapDialog(int, int*, int, int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
void __cdecl d2_CreateGuiWindow(int, int, int, int);
void __cdecl d2_SetValueGaugeFlags(int, int);
void __cdecl d2_SetValueGaugeLabel(int, int);
void __cdecl d2_SetValueGaugeStepLabels(int, int, int, int, int);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_GetControlValue(int);
int __cdecl d2_CheckActionBlocker(int, int);
void __cdecl cm_SendCopyEntityData(int*);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d3_EndCameraAndUiMode(void);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* The reference frame keeps EBP; /O2 /Gd omits the frame pointer, so restore
 * it here instead of overriding the locked CFLAGS. */
#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x0058dbe0 */
/* ADDRESS: GOLDDE 0x005738a0 */
void __cdecl d2_OpenFriedhofFogDialog(int building)
{
	int query[0x14];
	char text[1024];
	int req[0x3e];
	int dialogId;
	int firstControl;
	int secondControl;
	int v5;
	int v6;
	int v9;
	int v27;
	int rec;
	int v30;
	int fill_n;
	char* fill;

	io_FormatTextBuffer(text, 0x40c8, 0x40b6);
	if (he_StartHandlungSearch(2, 0, 0x90, 3, *(int*) (building + 1))) {
		d3snd_QueueSound(0xffffffff, 0, (char*) 0x6a9780, 0, 100);
		d2_ShowModalMessageBox(text, 0);
		return;
	}
	fill_n = 0x50;
	fill = (char*) query;
	/*
	 * The reference zero-fills with the hand-written block-fill prelude no
	 * msvc6 C spelling emits (archived docs/codegen-walls.md 6b).
	 */
	__asm {
		mov edi, fill
		mov ebx, fill_n
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
	query[0] = 1;
	query[1] = -1;
	query[2] = (int) 0xa07c43b4;
	query[3] = 1;
	query[4] = 6;
	query[0x13] = 0x727;
	rec = d2_RunCityScrollMapDialog(1, query, *(int*) 0x14b55f8, 0, 0);
	if (!rec) {
		d3_EndCameraAndUiMode();
		return;
	}
	dialogId = d2_LoadForm(0, 0, (char*) 0x6a9768);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dialogId);
	d2_SetForm(dialogId, 0);
	d2_InitWindowBounds(*(int*) &d2_CurrentWindowId);
	d2_SetForm(dialogId, 1);
	io_AppendText(0x40b7, 0x40b6, *(unsigned short*) (rec + 0x27), rec);
	firstControl = d2_AddWindowValueGauge(100, 0xa0, 200, 0, 2, 0x7b, 0x82,
	                  *(int*) &d2_CurrentWindowId);
	d2_CreateGuiWindow(firstControl, 0, 2, 0);
	d2_SetValueGaugeFlags(firstControl, 0x82);
	d2_SetValueGaugeLabel(firstControl, *(int*) 0x14b561c);
	d2_SetValueGaugeStepLabels(firstControl, 3, *(int*) 0x14b5620, *(int*) 0x14b5624,
	             *(int*) 0x14b5628);
	secondControl = d2_AddWindowValueGauge(100, 0xbe, 200, 0, 2, 0x7b, 0x82,
	                  *(int*) &d2_CurrentWindowId);
	d2_CreateGuiWindow(secondControl, 0, 2, 0);
	d2_SetValueGaugeFlags(secondControl, 0x82);
	d2_SetValueGaugeLabel(secondControl, *(int*) 0x14b562c);
	d2_SetValueGaugeStepLabels(secondControl, 3, *(int*) 0x14b5630, *(int*) 0x14b5634,
	             *(int*) 0x14b5638);
	d2_SetForm(dialogId, 2);
	v30 = io_AppendText(0x40be);
	v27 = d2_GetWindowListItem(dialogId, 2, v30);
	v30 = d2_GetWindowListItem(dialogId, 2, v30 + 1);
	d2_DialogButtonAction = -1;
	do {
		d2_SetForm(dialogId, 3);
		io_AppendText(0x6811b0);
		v6 = (d2_GetControlValue(secondControl) + 2) * (d2_GetControlValue(firstControl) + 2);
		io_AppendText(0x40b9);
		io_AppendText(0x40ba, v6);
		if (io_RightButtonReleased) {
			goto label_58df76;
		}
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == v27) {
				v5 = gm_LocalPlayerSlot;
				if (d2_CheckActionBlocker((int) (gm_EntitySlotTable + v5 * 0x21c), v6) == 1) {
					for (v9 = 0; v9 < 0x3e; v9++) {
						req[v9] = 0;
					}
					((char*) req)[4] = (char) 0x90;
					((char*) req)[0x36] = (char) 2;
					*(int*) ((char*) req + 8) = *(int*) (gm_LocalPlayerSlot * 0x21c + (unsigned long)&gm_EntityIdField);
					*(int*) ((char*) req + 0xc) = *(int*) (building + 1);
					*(pos14_7f4c00*) ((char*) req + 0x28) = gm_GameTime;
					*(int*) ((char*) req + 0x5c) = d2_GetControlValue(firstControl);
					*(int*) ((char*) req + 0x60) = d2_GetControlValue(secondControl);
					*(int*) ((char*) req + 0x58) = *(int*) (rec + 1);
					cm_SendCopyEntityData(req);
				label_58df76:
					d2_DialogCloseRequested = 1;
				}
			} else if (d2_CurrentElementId == v30) {
				goto label_58df76;
			}
		}
	} while (main_RunFrameLoop(0x58dbe0, 0x677c7));
	d2_DestroyForm(dialogId);
	d3_EndCameraAndUiMode();
}
#pragma optimize("", on)
