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
int __cdecl fcn_0050cf50(void* obj, int n);
int __cdecl fcn_00526010(void* slot, int value, unsigned char flag);
int __cdecl fcn_004fa5b0(int cmd, void* slot, unsigned int* list);
void* __cdecl he_StartHandlungSearch(int a, int b, int c, int d, int e);
void* __cdecl he_fn_Handlung(void);
int __cdecl fcn_0055c0f0(void* a, void* b);
int __cdecl fcn_0055c0a0(void* a, void* b);
int __cdecl fcn_0055c050(void* a);
int __cdecl fcn_00579640(void* a, void* b);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
void __cdecl fcn_00526120(char* buf, int flag);
int __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl d2_CenterDialogWindows(int dlg);
void __cdecl d2_SetForm(int dlg, int flag);
void __cdecl d2_SetOverlayAnimation(int a, int b);
int __cdecl io_AppendText(int id, ...);
int __cdecl fcn_00472250(int dlg, int a, int b);
int __cdecl fcn_005c9220(unsigned int* ids);
int __cdecl fcn_005373e0(void* fn, int key);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c4ef0(char* s);
void __cdecl fcn_00471e30(int dlg);

/* ADDRESS: GOLDTL 0x005bf0d0 */
int __cdecl fcn_005bf0d0(unsigned short* obj, unsigned char* record)
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
		+ (float) fcn_0050cf50(record, 100) * *(float*) 0x662b10);
	if (fcn_004fa5b0(0x1b, (void*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c), slots) & 2) {
		value = value / 2;
	}
	if (fcn_00526010((void*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c), value, g_773d75) == 0) {
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
	if (fcn_0055c0f0(obj, (void*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c)) == 0) {
		io_FormatTextBuffer(text, 0x1703, *(unsigned short*) (record + 0x27), record);
		fcn_00526120(text, 0);
		return 0;
	}
	if (fcn_0055c0a0(obj, (void*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c)) == 0) {
		io_FormatTextBuffer(text, 0x1704, *(unsigned short*) obj);
		fcn_00526120(text, 0);
		return 0;
	}
	if (fcn_0055c050(record) == 0) {
		io_FormatTextBuffer(ev, 0x1705, record);
		fcn_00526120(ev, 0);
		return 0;
	}
	if (fcn_00579640(obj, (void*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c)) == 0) {
		io_FormatTextBuffer(text, 0x409f, *(unsigned short*) obj);
		fcn_00526120(text, 0);
		return 0;
	}
	dlg = fcn_00470820(0, 0, (char*) 0x6ac494);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	evid = fcn_00472250(dlg, 1,
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
	while (fcn_005373e0((void*) fcn_005bf0d0, 0x677c7) != 0) {
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
			fcn_004c4eb0((char*) 0x67eac4);
			fcn_004c5530(ev);
			fcn_004c4ef0((char*) 0x67eac4);
			io_FormatTextBuffer(text2, 0x1701, *(unsigned short*) (record + 0x25),
				*(unsigned char*) record * 0xe + 0x48e);
			fcn_00526120(text2, 0);
			g_774654 = 1;
			count = 1;
		}
	}
	fcn_00471e30(dlg);
	return count;
}
