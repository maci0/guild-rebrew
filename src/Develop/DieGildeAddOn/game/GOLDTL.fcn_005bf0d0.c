#include <string.h>

extern unsigned char g_773d75;
extern int d2_CurrentElementId;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern char* g_7746c4;
extern unsigned short g_774970;
extern char g_7f4ca0[];
extern char g_7f4ca4[];

int __cdecl gm_WalkEntityChain(unsigned short id);
int __cdecl gm_CalculateGebaeudeValue(void* obj, int n);
int __cdecl gm_CheckEntityStock(void* slot, int value, unsigned char flag);
int __cdecl gm_CheckPrivilege(int cmd, void* slot, unsigned int* list);
void* __cdecl he_StartHandlungSearch(int a, int b, int c, int d, int e);
void* __cdecl he_fn_Handlung(void);
int __cdecl he_HasNoActiveEvent04b(void* a, void* b);
int __cdecl he_HasNoActiveAction0x2e(void* a, void* b);
int __cdecl he_HasNoActiveAction0x62(void* a);
int __cdecl he_HasNoActiveAction0x88(void* a, void* b);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
void __cdecl fcn_00526120(char* buf, int flag);
int __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl d2_CenterDialogWindows(int dlg);
void __cdecl d2_SetForm(int dlg, int flag);
void __cdecl d2_SetOverlayAnimation(int a, int b);
int __cdecl io_AppendText(int id, ...);
int __cdecl d2_GetWindowListItem(int dlg, int a, int b);
int __cdecl fcn_005c9220(unsigned int* ids);
int __cdecl main_RunFrameLoop(void* fn, int key);
void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendCopyEntityData(char* msg);
void __cdecl cm_SendTraceEnd(char* s);
void __cdecl d2_DestroyForm(int dlg);

/* ADDRESS: GOLDTL 0x005bf0d0 */
int __cdecl d2_RunSabotageDialog(unsigned short* obj, unsigned char* record)
{
	unsigned int count;
	unsigned int ids[6];
	char ev[0x100];
	char text2[0x80];
	char text[0x400];
	unsigned int slots[0x88];
	unsigned int idx;
	int value;
	int evid;
	int dlg;
	void* entity;

	count = 0;
	if (record == 0 || *(unsigned short*) (record + 0x27) == 0xffff) {
		return 0;
	}
	memset(slots, 0, sizeof(slots));
	idx = *(unsigned short*) 0x774970;
	slots[0] = 1;
	value = (int) ((float) gm_WalkEntityChain(*(unsigned short*) (0x7f4ca0 + idx * 0x21c)) * *(float*) 0x6628ac
		+ (float) gm_CalculateGebaeudeValue(record, 100) * *(float*) 0x662b10);
	if (gm_CheckPrivilege(0x1b, (void*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c), slots) & 2) {
		value = value / 2;
	}
	if (gm_CheckEntityStock((void*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c), value, g_773d75) == 0) {
		return 0;
	}
	entity = he_StartHandlungSearch(2, 2, *(unsigned short*) 0x774970, 0, 0x19);
	while (entity != 0) {
		if (*(int*) ((char*) entity + 0xac) == *(int*) (record + 1)) {
			io_FormatTextBuffer(text, 0x1702, *(unsigned short*) (record + 0x27), record);
			fcn_00526120(text, 0);
			return 0;
		}
		entity = he_fn_Handlung();
	}
	if (he_HasNoActiveEvent04b(obj, (void*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c)) == 0) {
		io_FormatTextBuffer(text, 0x1703, *(unsigned short*) (record + 0x27), record);
		fcn_00526120(text, 0);
		return 0;
	}
	if (he_HasNoActiveAction0x2e(obj, (void*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c)) == 0) {
		io_FormatTextBuffer(text, 0x1704, *(unsigned short*) obj);
		fcn_00526120(text, 0);
		return 0;
	}
	if (he_HasNoActiveAction0x62(record) == 0) {
		io_FormatTextBuffer(ev, 0x1705, record);
		fcn_00526120(ev, 0);
		return 0;
	}
	if (he_HasNoActiveAction0x88(obj, (void*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c)) == 0) {
		io_FormatTextBuffer(text, 0x409f, *(unsigned short*) obj);
		fcn_00526120(text, 0);
		return 0;
	}
	dlg = fcn_00470820(0, 0, (char*) 0x6ac494);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	evid = d2_GetWindowListItem(dlg, 1,
		io_AppendText(0x1700, 0x1711, value, *(unsigned short*) (record + 0x27),
			*(unsigned char*) record * 0xe + 0x48e));
	/* The native 0x1705 text and later packet share ev. */
	memset(ids, 0xff, 6 * sizeof(unsigned int));
	ids[0] = dlg;
	ids[1] = 2;
	ids[2] = 3;
	ids[3] = 4;
	ids[4] = 2;
	ids[5] = 0x18;
	fcn_005c9220(ids);
	while (main_RunFrameLoop((void*) d2_RunSabotageDialog, 0x677c7) != 0) {
		if (g_14ce8e0 != 0 || g_100f1dc == 1) {
			g_774654 = 1;
		}
		if (g_100f1dc == 2 && evid != -1 && d2_CurrentElementId == evid) {
			ev[4] = 0x19;
			*(int*) (ev + 8) = *(int*) (g_7f4ca4 + g_774970 * 0x21c);
			*(int*) (ev + 0xc) = *(int*) (g_7746c4 + 1);
			ev[0x36] = 1;
			*(int*) (ev + 0x7c) = value;
			*(int*) (ev + 0x58) = *(int*) (record + 1);
			cm_SendLogAction((char*) 0x67eac4);
			cm_SendCopyEntityData(ev);
			cm_SendTraceEnd((char*) 0x67eac4);
			io_FormatTextBuffer(text2, 0x1701, *(unsigned short*) (record + 0x25),
				*(unsigned char*) record * 0xe + 0x48e);
			fcn_00526120(text2, 0);
			g_774654 = 1;
			count = 1;
		}
	}
	d2_DestroyForm(dlg);
	return count;
}
