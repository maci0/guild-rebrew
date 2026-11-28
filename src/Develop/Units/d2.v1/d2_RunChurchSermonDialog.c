extern int g_774654;
extern int d2_CurrentElementId;
extern int g_14ce8e0;
#include <string.h>

#include "Develop/client_types.h"

#pragma pack(push, 1)
typedef struct tag7 {
	char a;
	char b;
	int id;
	char c;
} tag7;
#pragma pack(pop)
/* SIZE 0x7 */

/* packet body built for fcn_004c5530: church sermon (type 0x2b) */
typedef struct SERMON_ACTION_PKT {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad37[0x25];
	char b5c;
	char pad5d[0x9b];
} SERMON_ACTION_PKT;
/* SIZE 0xf8 */

/* picture/text description passed to fcn_005ca560 and fcn_005ca740 */
typedef struct SERMON_TARGET_SEL {
	char* e;
	char pad4[0xc];
	int x;
	int y;
	char pad18[0x18];
	int f30;
	char pad34[4];
} SERMON_TARGET_SEL;
/* SIZE 0x38 */

#include "Develop/DieGildeAddOn/game/game_player.h"
extern char* gm_CityEntity;
extern int d2_CurrentWindowId;
extern char* g_772500;
extern char* g_77255c;
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char g_7f4ca4[];
char g_6811b0[] = "$C";
extern volatile int g_6b7fac;
extern int g_100f1dc;
extern int g_666018;
extern int g_66601c;

unsigned short* __cdecl fcn_00502cd0(int container, int count, int arg, int arg2);
char* __cdecl cm_GetCommandResult(int rc);
int __cdecl cm_GetCommandStatus(int rc);
int __cdecl cm_AreQueuedCommandsDone(void);
int __cdecl cm_FlushCommandQueue(void);
int __cdecl cm_PollCommandQueue(void);
void __cdecl cm_ExecCommand(void);
int __cdecl cm_RequestAllocThemaPredigt(int entity_id, tag7 key);
int __cdecl cm_SendCopyEntityData(SERMON_ACTION_PKT* m);
int __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_BeginPacketFieldDelta(char* base, int entity_id);
int __cdecl cm_AppendPacketFieldDelta(unsigned char size, unsigned char count, unsigned short off, char* src);
char* __cdecl he_StartHandlungSearch(int kind, int first, int id, int arg, int entity_id);
char* __cdecl gm_LookupEntityRecordById(int description_id);
int __cdecl d2_LoadForm(int x, int y, char* title);
int __cdecl d2_SetOverlayAnimation(int a1, int a2);
void __cdecl d2_CenterDialogWindows(int dlg);
void __cdecl d2_DestroyForm(int dlg);
void __cdecl d2_SetForm(int dlg, int page);
int __cdecl d2_GetWindowListItem(int dlg, int page, int id);
void __cdecl d2_SetElementEnabled(int button, int state);
int __cdecl d2_ClearWindowChildren(int win, int keep);
void __cdecl d2_InitWindowBounds(int win);
int __cdecl io_AppendText(int id, ...);
int __cdecl main_RunFrameLoop(void* fn, int msg);
int __cdecl d2_CheckActionBlocker(char* house, int mode);
void __cdecl gm_ModifyHealth(int id, int amount);
int __cdecl d2_BuildPersonStatusDesc(SERMON_TARGET_SEL* sel);
int __cdecl d2_DrawPersonCard(int x, int y, int win, int id, SERMON_TARGET_SEL* sel, int flag);
int __cdecl io_FormatTextBuffer(char* buf, int id, ...);
char* __cdecl d2_OpenTargetPicker(void* m, char* text, int a2, int a3);
int __cdecl gm_RandomMod(unsigned short range);
void __cdecl d3_EndCameraAndUiMode(void);

/* ADDRESS: GOLDTL 0x005ac2d0 */
void __cdecl d2_RunChurchSermonDialog(char* building)
{
	SERMON_ACTION_PKT pkt;
	char text[0x20];
	char pkt2[0x50];
	SERMON_TARGET_SEL sel;
	int prev;
	int btnState2;
	int btnState1;
	int btnState0;
	char* info;
	int btnCancel;
	char* unit;
	char v16;
	char v15;
	char v18;
	int state;
	char v12;
	int flag;
	char* obj;
	int rc;
	int dlg;
	int i;

	btnState1 = 0;
	btnState2 = 0;
	btnCancel = 0;
	btnState0 = 0;
	if (building == 0) {
		return;
	}
	if (*(unsigned short*) (building + 0x27) == 0xffff) {
		return;
	}
	if (*(unsigned short*) (building + 0x27) != g_774970) {
		return;
	}
	obj = (char*) fcn_00502cd0(*(int*) (building + 0x5d), 1, 0, 0x1b5);
	if (obj == 0) {
		tag7 t;

		t.a = -1;
		t.b = -1;
		t.id = -1;
		obj = cm_GetCommandResult(cm_RequestAllocThemaPredigt(*(int*) (building + 1), t));
		while (cm_AreQueuedCommandsDone() == 0) {
			cm_FlushCommandQueue();
			cm_PollCommandQueue();
			cm_ExecCommand();
		}
	}
	unit = he_StartHandlungSearch(2, 0, 0x2b, 3, *(int*) (building + 1));
	if (unit == 0) {
		pkt.pos = gm_GameTime;
		pkt.b4 = 0x2b;
		pkt.b36 = 2;
		pkt.f8 = *(int*) (gm_CityEntity + 4);
		pkt.fc = *(int*) (building + 1);
		pkt.b5c = 0;
		rc = cm_SendCopyEntityData(&pkt);
		while (rc != -1 && cm_GetCommandStatus(rc) == 0) {
			main_RunFrameLoop((void*) 0, 0x677c7);
		}
		unit = cm_GetCommandResult(rc);
	}
	info = 0;
	if (*(char*) (obj + 0x22) == 0) {
		state = 0;
	} else if (*(char*) (obj + 0x1c) == -1 || *(char*) (obj + 0x1d) == -1) {
		state = 1;
	} else {
		info = gm_LookupEntityRecordById(*(int*) (obj + 0x1e));
		state = 2;
		if (info == 0) {
			state = 1;
		}
	}
	dlg = d2_LoadForm(0, 0, "Locations\\Kirche\\Predigt");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	flag = 1;
	g_100f1dc = -1;
	prev = g_6b7fac;
	do {
		if ((unsigned int) (g_6b7fac - prev) > 0x64 && state != 3) {
			flag = 1;
			prev = g_6b7fac;
			obj = (char*) fcn_00502cd0(*(int*) (building + 0x5d), 1, 0, 0x1b5);
			if (obj == 0 || *(unsigned short*) (building + 0x27) != g_774970) {
				state = 3;
				flag = 0;
				goto post;
			}
			if (*(char*) (obj + 0x22) == 0) {
				state = 0;
			} else if (*(char*) (obj + 0x1c) != -1 && *(char*) (obj + 0x1d) != -1
			    && *(int*) (obj + 0x1e) != -1) {
				info = gm_LookupEntityRecordById(*(int*) (obj + 0x1e));
				state = (info != 0) + 1;
			}
		} else if (flag == 0) {
			goto post;
		}
		if (state == 3) {
			goto post;
		}
		btnState0 = -1;
		btnState2 = -1;
		btnState1 = -1;
		btnCancel = -1;
		if (state == 0) {
			d2_SetForm(dlg, 1);
			io_AppendText((int) g_6811b0);
			io_AppendText(0x19a5, 1, unit + 0x52);
			d2_SetForm(dlg, 2);
			io_AppendText((int) g_6811b0);
			i = io_AppendText(0x19a6);
			btnState0 = d2_GetWindowListItem(dlg, 2, i);
			btnCancel = d2_GetWindowListItem(dlg, 2, i + 1);
		} else if (state == 1) {
			d2_SetForm(dlg, 1);
			d2_ClearWindowChildren(d2_CurrentWindowId, 1);
			io_AppendText((int) g_6811b0);
			io_AppendText(0x19a0, unit + 0x52);
			d2_SetForm(dlg, 2);
			d2_ClearWindowChildren(d2_CurrentWindowId, 1);
			io_AppendText((int) g_6811b0);
			i = io_AppendText(0x19a1);
			btnState1 = d2_GetWindowListItem(dlg, 2, i);
			btnCancel = d2_GetWindowListItem(dlg, 2, i + 1);
			if (*(int*) (unit + 0x70) > 0) {
				d2_SetElementEnabled(btnState1, 0);
			} else {
				d2_SetElementEnabled(btnState1, 1);
			}
		} else if (state == 2) {
			d2_SetForm(dlg, 1);
			d2_ClearWindowChildren(d2_CurrentWindowId, 1);
			io_AppendText((int) g_6811b0);
			io_AppendText(0x198e, unit + 0x52, *(char*) (obj + 0x1c) + 0x1990,
			    *(char*) (obj + 0x1d) + 0x1998, *(unsigned short*) info);
			sel.e = info;
			sel.x = *(int*) (g_77255c + 0xc) / 2 - *(short*) (g_772500 + 0x1ebd8) / 2;
			sel.y = 0xc3;
			sel.f30 = 1;
			d2_BuildPersonStatusDesc(&sel);
			d2_DrawPersonCard(sel.x, sel.y, d2_CurrentWindowId, 0x54, &sel, 1);
			d2_SetForm(dlg, 2);
			d2_ClearWindowChildren(d2_CurrentWindowId, 1);
			io_AppendText((int) g_6811b0);
			i = io_AppendText(0x198f);
			btnState2 = d2_GetWindowListItem(dlg, 2, i);
			btnCancel = d2_GetWindowListItem(dlg, 2, i + 1);
			if (*(int*) (unit + 0x70) > 0) {
				d2_SetElementEnabled(btnState2, 0);
			} else {
				d2_SetElementEnabled(btnState2, 1);
			}
		}
		flag = 0;
	post:
		if (g_14ce8e0 != 0 || state == 3) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == btnState0) {
				if (d2_CheckActionBlocker((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970], 1) != 0) {
					v12 = 1;
					gm_ModifyHealth(((ENTITY_RECORD*)(g_7f4ca4 - 4))[g_774970].entity_id, -1);
					cm_BeginPacketFieldDelta(obj, *(int*) (obj + 2));
					cm_AppendPacketFieldDelta(1, 1, 0x22, &v12);
					rc = cm_RequestChangeAttribute();
					flag = 1;
					state = 1;
					while (rc != -1 && cm_GetCommandStatus(rc) == 0) {
						main_RunFrameLoop((void*) 0, 0x677c7);
					}
				}
			} else if (d2_CurrentElementId == btnState1) {
				memset(pkt2, 0, 0x50);
				*(int*) (pkt2 + 4) = 0x400;
				*(int*) (pkt2 + 0x10) = 6;
				*(int*) (pkt2 + 8) = g_666018;
				*(int*) (pkt2 + 0xc) = g_66601c;
				io_FormatTextBuffer(text, 0x19a2);
				info = d2_OpenTargetPicker(pkt2, text, 0, 0);
				obj = (char*) fcn_00502cd0(*(int*) (building + 0x5d), 1, 0, 0x1b5);
				if (info != 0 && *(int*) (info + 4) != -1 && obj != 0) {
					v15 = (char) gm_RandomMod(8);
					v16 = (char) gm_RandomMod(8);
					cm_BeginPacketFieldDelta(obj, *(int*) (obj + 2));
					cm_AppendPacketFieldDelta(4, 1, 0x1e, info + 4);
					cm_RequestChangeAttribute();
					cm_BeginPacketFieldDelta(obj, *(int*) (obj + 2));
					cm_AppendPacketFieldDelta(1, 1, 0x1c, &v15);
					cm_RequestChangeAttribute();
					cm_BeginPacketFieldDelta(obj, *(int*) (obj + 2));
					cm_AppendPacketFieldDelta(1, 1, 0x1d, &v16);
					rc = cm_RequestChangeAttribute();
					state = 2;
					flag = 1;
					while (rc != -1 && cm_GetCommandStatus(rc) == 0) {
						main_RunFrameLoop((void*) 0, 0x677c7);
					}
				}
			} else if (d2_CurrentElementId == btnState2) {
				int id;

				v12 = -1;
				v18 = -1;
				id = -1;
				cm_BeginPacketFieldDelta(obj, *(int*) (obj + 2));
				cm_AppendPacketFieldDelta(4, 1, 0x1e, (char*) &id);
				cm_RequestChangeAttribute();
				cm_BeginPacketFieldDelta(obj, *(int*) (obj + 2));
				cm_AppendPacketFieldDelta(1, 1, 0x1c, &v12);
				cm_RequestChangeAttribute();
				cm_BeginPacketFieldDelta(obj, *(int*) (obj + 2));
				cm_AppendPacketFieldDelta(1, 1, 0x1d, &v18);
				rc = cm_RequestChangeAttribute();
				flag = 1;
				state = 1;
				while (rc != -1 && cm_GetCommandStatus(rc) == 0) {
					main_RunFrameLoop((void*) 0, 0x677c7);
				}
			} else if (d2_CurrentElementId == btnCancel) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunChurchSermonDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	d3_EndCameraAndUiMode();
}
unsigned char _dpad_681114[24] = {
    0x54, 0x52, 0x41, 0x45, 0x47, 0x45, 0x5f, 0x56, 0x45, 0x52, 0x47, 0x41, 0x42, 0x45, 0x5f, 0x48,
    0x53, 0x5f, 0x25, 0x2e, 0x32, 0x64, 0x00, 0x00
};
unsigned char _dpad_68112d[3] = {
    0x4e, 0x00, 0x00
};
unsigned char _dpad_681131[15] = {
    0x70, 0x65, 0x63, 0x69, 0x61, 0x6c, 0x5c, 0x6d, 0x69, 0x73, 0x73, 0x69, 0x6f, 0x6e, 0x00
};
unsigned char _dpad_681141[11] = {
    0x69, 0x61, 0x5b, 0x25, 0x73, 0x5d, 0x24, 0x4e, 0x00, 0x00, 0x00
};
unsigned char _dpad_68114d[23] = {
    0x70, 0x65, 0x63, 0x69, 0x61, 0x6c, 0x5c, 0x43, 0x48, 0x4f, 0x4f, 0x53, 0x45, 0x5f, 0x4d, 0x49,
    0x53, 0x53, 0x49, 0x4f, 0x4e, 0x00, 0x00
};
unsigned char _dpad_681165[7] = {
    0x69, 0x74, 0x5b, 0x25, 0x73, 0x5d, 0x00
};
unsigned char _dpad_68116e[66] = {
    0x6e, 0x75, 0x5c, 0x43, 0x48, 0x4f, 0x4f, 0x53, 0x45, 0x48, 0x49, 0x53, 0x54, 0x4f, 0x52, 0x59,
    0x00, 0x00, 0x5f, 0x41, 0x55, 0x46, 0x54, 0x52, 0x41, 0x45, 0x47, 0x45, 0x5f, 0x45, 0x52, 0x46,
    0x4f, 0x4c, 0x47, 0x5f, 0x48, 0x53, 0x5f, 0x25, 0x2e, 0x32, 0x64, 0x00, 0x00, 0x00, 0x41, 0x55,
    0x46, 0x54, 0x52, 0x41, 0x45, 0x47, 0x45, 0x5f, 0x41, 0x4c, 0x4c, 0x47, 0x45, 0x4d, 0x45, 0x49,
    0x4e, 0x00
};

