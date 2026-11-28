#include <string.h>

typedef struct MsgItem {
	int id;			/* +0x00 */
	int value;		/* +0x04 */
	char pad08[0x10];	/* +0x08 */
} MsgItem;
/* SIZE 0x18 */

typedef struct MsgCtx {
	int dlg;		/* +0x000 */
	int flags;		/* +0x004 */
	int win;		/* +0x008 */
	int pad0c[0x13];	/* +0x00c */
	int msg;		/* +0x058 */
	char text[0x80];	/* +0x05c */
	MsgItem queue[0x100];	/* +0x0dc */
	int handles[0x300];	/* +0x18dc */
	int ids[0x80];		/* +0x24dc */
	int ids10[0x10];	/* +0x26dc */
	char pad[0x88];		/* +0x271c */
	int count;		/* +0x27a4 */
	char padTail[0x4];	/* +0x27a8 */
} MsgCtx;
/* SIZE 0x27ac */

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int tp_d2_SelectedControl;
extern int g_6ab3dc;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char g_6b5c60[];
extern char* g_1015ea0;
extern char* g_774a68;
extern char g_10161bc[];

int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_InitLandkarteDialog(MsgCtx*);
void __cdecl d2_BuildCityScrollMap(MsgCtx*);
void __cdecl d2_UpdateCityScrollMap(MsgCtx*);
void __cdecl d2_DispatchTutorialInput(int, int, int, int);
void __cdecl d2_DestroyMapDialog(int*);
void __cdecl d2_SetFormVisibility(int, int);
void __cdecl d2_SetSlotVisibility(int, int);
int __cdecl d2_DispatchLawTargetDialog(char*, int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x005bdc30 */
int __cdecl d2_RunCityScrollMapDialog(int flags, void* state, char* name, void (__cdecl* cb)(int, int))
{
	MsgCtx ctx;
	int i;
	int v;
	v = 0;
	memset(ctx.pad0c, 0, 0x50);
	if (state != 0) {
		memcpy(ctx.pad0c, state, 0x50);
	}
	ctx.flags = flags;
	if (name != 0) {
		strcpy(ctx.text, name);
	}
	else {
		ctx.text[0] = g_6b5c60[0];
	}
	d2_InitLandkarteDialog(&ctx);
	d2_BuildCityScrollMap(&ctx);
	while (main_RunFrameLoop((void*) d2_RunCityScrollMapDialog, 0x677c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		g_6ab3dc = (tp_d2_SelectedControl == 0);
		d2_UpdateCityScrollMap(&ctx);
		if (flags & 4) {
			if (g_14ce8d8 != 0 && d2_CurrentElementId != -1) {
				for (i = 0; i < 0x10; i++) {
					if (ctx.ids10[i] != -1 && d2_CurrentElementId == ctx.ids10[i]) {
						v = *(int*) (&((D2_CONTROL_TL*) (g_1015ea0))[ctx.ids10[i]].associated_object);
						if (v != 0 && cb != 0) {
							d2_SetFormVisibility(ctx.dlg, 0);
							d2_SetSlotVisibility(*(int*) (g_10161bc + ctx.win * 0x3cc), 0);
							cb(v, v);
							d2_SetFormVisibility(ctx.dlg, 1);
							d2_SetSlotVisibility(*(int*) (g_10161bc + ctx.win * 0x3cc), 1);
						}
						else {
							g_774654 = 1;
						}
						break;
					}
				}
			}
		}
		else if ((flags & 8) && g_14ce8d8 != 0 && d2_CurrentElementId != -1) {
			for (i = 0; i < 0x100; i++) {
				if (ctx.ids[i] != -1 && ctx.ids[i] == d2_CurrentElementId) {
					v = *(int*) (g_774a68 + i * 4);
					g_774654 = 1;
					break;
				}
			}
		}
		for (i = 0; i < ctx.count; i++) {
			if (d2_CurrentElementId != -1 && d2_CurrentElementId == ctx.queue[i].id && g_14ce8d8 != 0) {
				v = 0;
				if (flags & 1) {
					v = ctx.queue[i].value;
				}
				else {
					if (!(flags & 2)) {
						continue;
					}
					d2_SetFormVisibility(ctx.dlg, 0);
					d2_SetSlotVisibility(*(int*) (g_10161bc + ctx.win * 0x3cc), 0);
					v = d2_DispatchLawTargetDialog((char*) ctx.queue[i].value, (int) state, (int) name, (int) cb);
					d2_SetSlotVisibility(*(int*) (g_10161bc + ctx.win * 0x3cc), 1);
					d2_SetFormVisibility(ctx.dlg, 1);
				}
				if (v == 0) {
					continue;
				}
				if (cb == 0) {
					g_774654 = 1;
					break;
				}
				if (flags & 2) {
					continue;
				}
				d2_SetFormVisibility(ctx.dlg, 0);
				d2_SetSlotVisibility(*(int*) (g_10161bc + ctx.win * 0x3cc), 0);
				cb(v, ctx.queue[i].value);
				d2_SetFormVisibility(ctx.dlg, 1);
				d2_SetSlotVisibility(*(int*) (g_10161bc + ctx.win * 0x3cc), 1);
				break;
			}
		}
	}
	d2_DispatchTutorialInput(0xd, v, 1, 0);
	d2_DestroyMapDialog(&ctx.dlg);
	return v;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_1015f50[620];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_10160c0[216];
unsigned char _dpad_1016199[27];
unsigned char _dpad_10161b5[7];
#endif
