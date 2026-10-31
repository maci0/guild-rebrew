#include <string.h>

extern unsigned char g_773d75;
extern int g_67d370;
extern int g_100f1dc;
extern int g_14ce8e0;

int __cdecl gm_WalkEntityChain(unsigned short id);
int __cdecl fcn_0050cf50(void* obj, int n);
int __cdecl fcn_00526010(void* slot, int value, unsigned char flag);
int __cdecl fcn_004fa5b0(int cmd, void* slot, unsigned int* list);
void* __cdecl fcn_005463a0(int a, int b, int c, int d, int e);
void* __cdecl he_fn_Handlung(void);
int __cdecl fcn_0055c0f0(void* a, void* b);
int __cdecl fcn_0055c0a0(void* a, void* b);
int __cdecl fcn_0055c050(void* a);
int __cdecl fcn_00579640(void* a, void* b);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
void __cdecl fcn_00526120(char* buf, int flag);
int __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl fcn_00471b60(int dlg);
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
int __cdecl fcn_005bf0d0(unsigned short* a0, unsigned char* a1)
{
	unsigned int count;
	unsigned int ids[7];
	char ev[0xfc];
	char text2[0x80];
	char text[0x400];
	unsigned int slots[0x88];
	unsigned int idx;
	int value;
	int evid;
	int flag;
	int dlg;
	void* entity;

	count = 0;
	if (a1 == 0 || *(unsigned short*) (a1 + 0x27) == 0xffff) {
		return 0;
	}
	memset(slots, 0, sizeof(slots));
	idx = *(unsigned short*) 0x774970;
	slots[0] = 1;
	value = (int) ((float) gm_WalkEntityChain(*(unsigned short*) (0x7f4ca0 + idx * 0x21c)) * *(float*) 0x6628ac
		+ (float) fcn_0050cf50(a1, 100) * *(float*) 0x662b10);
	if (fcn_004fa5b0(0x1b, (void*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c), slots) & 2) {
		value = value / 2;
	}
	if (fcn_00526010((void*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c), value, g_773d75) == 0) {
		return 0;
	}
	entity = fcn_005463a0(2, 2, *(unsigned short*) 0x774970, 0, 0x19);
	while (entity != 0) {
		if (*(int*) ((char*) entity + 0xac) == *(int*) (a1 + 1)) {
			io_FormatTextBuffer(text, 0x1702, *(unsigned short*) (a1 + 0x27), a1);
			fcn_00526120(text, 0);
			return 0;
		}
		entity = he_fn_Handlung();
	}
	if (fcn_0055c0f0(a0, (void*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c)) == 0) {
		io_FormatTextBuffer(text, 0x1703, *(unsigned short*) (a1 + 0x27), a1);
		fcn_00526120(text, 0);
		return 0;
	}
	if (fcn_0055c0a0(a0, (void*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c)) == 0) {
		io_FormatTextBuffer(text, 0x1704, *(unsigned short*) a0);
		fcn_00526120(text, 0);
		return 0;
	}
	if (fcn_0055c050(a1) == 0) {
		io_FormatTextBuffer((char*) &ids[6], 0x1705, a1);
		fcn_00526120((char*) &ids[6], 0);
		return 0;
	}
	if (fcn_00579640(a0, (void*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c)) == 0) {
		io_FormatTextBuffer(text, 0x409f, *(unsigned short*) a0);
		fcn_00526120(text, 0);
		return 0;
	}
	dlg = fcn_00470820(0, 0, (char*) 0x6ac494);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	evid = fcn_00472250(dlg, 1,
		io_AppendText(0x1700, 0x1711, value, *(unsigned short*) (a1 + 0x27),
			*(unsigned char*) a1 * 0xe + 0x48e));
	/* entries 0..5 are cleared; entry 6 is the 0x1705 message area */
	memset(ids, 0xff, 6 * sizeof(unsigned int));
	ids[0] = dlg;
	ids[1] = 2;
	ids[2] = 3;
	ids[3] = 4;
	ids[4] = 2;
	ids[5] = 0x18;
	fcn_005c9220(ids);
	while (fcn_005373e0((void*) fcn_005bf0d0, 0x677c7) != 0) {
		flag = g_100f1dc;
		if (g_14ce8e0 != 0 || flag == 1) {
			*(int*) 0x774654 = 1;
		}
		if (flag == 2 && evid != -1 && g_67d370 == evid) {
			*(int*) (ev + 8) = *(int*) (0x7f4ca4 + *(unsigned short*) 0x774970 * 0x21c);
			ev[0] = 0x19;
			*(int*) (ev + 0xc) = *(int*) (*(int*) 0x7746c4 + 1);
			ev[0x36] = 1;
			*(int*) (ev + 0x7c) = value;
			*(int*) (ev + 0x58) = *(int*) (a1 + 1);
			fcn_004c4eb0((char*) 0x67eac4);
			fcn_004c5530(ev);
			fcn_004c4ef0((char*) 0x67eac4);
			io_FormatTextBuffer(text2, 0x1701, *(unsigned short*) (a1 + 0x25),
				*(unsigned char*) a1 * 0xe + 0x48e);
			fcn_00526120(text2, 0);
			*(int*) 0x774654 = 1;
			count = 1;
		}
	}
	fcn_00471e30(dlg);
	return count;
}
