#include <string.h>
#pragma intrinsic(memset)

typedef struct {
	int sel;
	int pad4[2];
	int id;
	int idx;
	int ent;
	int count;
} ListRow;
/* SIZE 0x1c */

extern char g_868060[];
extern char g_6aac84[];
extern char* g_1015ea0;
extern int g_10162e8;
extern int g_10162ec;
extern int g_10162f0;
extern int g_10162f4;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_100f1dc;
#include "client_dialog_state.h"
extern char* g_77255c;
extern int g_772514;
extern int g_14ab738;
extern int g_14b5278;
extern char g_6b5c60[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_00533dc0(int, int, int);
int __cdecl fcn_0046fac0(int, int, void*, int);
void __cdecl fcn_00533a60(int, int, int*, int, ...);
int __cdecl fcn_0050d270(int);
void __cdecl fcn_005a5760(void*, int, int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_005463a0(int, int, int);
int __cdecl he_fn_Handlung(void);
void __cdecl ResetDisplayCounters(void);
int __cdecl fcn_005a5440(int, ListRow*, int, int, char);
int __cdecl fcn_005a5980(ListRow*);
int __cdecl fcn_005a66b0(char*, int, int, unsigned char);
void __cdecl fcn_00473fe0(void);
void __cdecl fcn_00472380(int, int, int, int);
int __cdecl fcn_0059c830(ListRow*);
void __cdecl fcn_00472170(int, int);
int __cdecl fcn_00657a73(int, void*, int);
void __cdecl fcn_0046f940(int, void*);
void __cdecl fcn_0046ed00(int, int, int);
void __cdecl fcn_005a6570(char*);
void __cdecl fcn_005a59d0(char*);

/* ADDRESS: GOLDTL 0x005a6880 */
void __cdecl fcn_005a6880(char* obj)
{
	ListRow list1[16];
	ListRow list2[16];
	int i;
	int h;
	int w1;
	int w2;
	int w3;
	int w4;
	int w0;
	int sel1;
	int sel2;
	int cur;
	int selected = -1;
	int cx;
	int cy;
	int cb;
	int d270;
	int label2;
	int buttons[2];
	char text[0x20];

	for (i = 0; i < 16; i++) {
		list2[i].sel = -1;
		list2[i].id = 0;
		list1[i].sel = -1;
		list1[i].id = 0;
	}
	for (i = 0; i < 4; i++) {
		if (g_868060[i * 0x2f4] != 0) {
			list1[i].id = *(unsigned short*) (g_868060 + i * 0x2f4 + 0x54);
			*(unsigned char*)&list1[i].idx = (unsigned char)i;
		}
	}
	h = fcn_00470820(0, 0, g_6aac84);
	fcn_00471b60(h);
	d2_SetForm(h, 0);
	fcn_00533dc0(g_772514, 0x73b, 0x73f);
	w2 = fcn_00472250(h, 0, 2);
	w3 = fcn_00472250(h, 0, 3);
	w1 = fcn_00472250(h, 0, 1);
	w0 = fcn_00472250(h, 0, 0);
	w4 = fcn_00472250(h, 0, 4);
	d2_SetForm(h, 0);
	cx = *(int*) (g_1015ea0 + w1 * 0x2f4 + 0x10) - *(int*) (g_77255c + 4) + 2;
	cy = *(int*) (g_1015ea0 + w1 * 0x2f4 + 0x1c) -
	     *(int*) (g_77255c + 8) + *(int*) (g_1015ea0 + w1 * 0x2f4 + 0x14) +
	     2;
	cb = fcn_0046fac0(cx, cy, g_6b5c60, g_772514);
	cx = *(int*) (g_1015ea0 + w2 * 0x2f4 + 0x10) - *(int*) (g_77255c + 4) + 2;
	cy = *(int*) (g_1015ea0 + w2 * 0x2f4 + 0x1c) -
	     *(int*) (g_77255c + 8) + *(int*) (g_1015ea0 + w2 * 0x2f4 + 0x14) +
	     2;
	label2 = fcn_0046fac0(cx, cy, g_6b5c60, g_772514);
	*(int*) (g_1015ea0 + cb * 0x2f4 + 0x84) = 0x54;
	*(int*) (g_1015ea0 + label2 * 0x2f4 + 0x84) = 0x54;
	d2_SetForm(h, 0);
	i = g_772514;
	*(int*) (0x10162e8 + i * 0x3cc) = 0xe;
	*(int*) (0x10162ec + i * 0x3cc) = 0x18;
	*(int*) (0x10162f0 + i * 0x3cc) = 0xe;
	*(int*) (0x10162f4 + i * 0x3cc) = 0xe;
	d2_SetForm(h, 1);
	io_AppendText(0x1900);
	d2_SetForm(h, 3);
	fcn_00533a60(g_772514, 0, buttons, 2, g_14ab738, g_14b5278);

	d270 = fcn_0050d270(*(int*) (obj + 0x5d));
	if (d270 <= 0) {
		d2_SetForm(h, 5);
		io_AppendText(0x190a, obj);
	}
	fcn_005a5760(list1, h, 4, 0);
	for (i = 0; i < 16; i++) {
		if (list1[i].sel != -1)
			fcn_00472640(list1[i].sel, 0);
	}
	while (fcn_005373e0((void*) 0x5a6880, 0x677c7) != 0) {
		cur = fcn_005463a0(1, 0, 0x27);
		if (cur != 0) {
			while (cur != 0 && *(int*) (cur + 0xac) != *(int*) (obj + 1))
				cur = he_fn_Handlung();
		}
		d2_SetForm(h, 2);
		io_AppendText(0x6811b0);
		io_AppendText(0x1902, *(int*) (obj + 0x69));
		if (cur == 0)
			io_AppendText(0x1903);
		else
			io_AppendText(0x1901, g_868060 + (unsigned char) ((char*) cur)[0xb0] * 0x2f4);
		if (g_14ce8e0 != 0)
			g_774654 = 1;
		ResetDisplayCounters();
		if (cur == 0) {
			selected = fcn_005a5440(*(int*) (obj + 0x5d), list2, h, 5, 1);
		}
		sel2 = fcn_005a5980(list1);
		if (cur == 0 && sel2 != -1 && selected != -1) {
			ResetDisplayCounters();
			if (fcn_005a66b0(obj, list2[selected].id, list2[selected].idx,
			             *(unsigned char*)&list1[sel2].idx)) {
				fcn_00473fe0();
				for (i = 0; i < 16; i++) {
					if (list2[i].sel != -1)
						fcn_00472380(list2[i].sel, 0, 0, 0);
				}
			}
		}
		for (i = 0; i < 16; i++) {
			if (list1[i].sel != -1)
				fcn_00472640(list1[i].sel,
				             selected != -1 ? 1 : 0);
		}
		sel1 = fcn_0059c830(list2);
		sel2 = fcn_0059c830(list1);
		if (sel1 <= 4) {
			fcn_00472170(w1, 0);
			fcn_00472170(w0, 0);
			fcn_00472170(cb, 0);
		} else {
			fcn_00472170(w1, 1);
			fcn_00472170(w0, 1);
			fcn_00472170(cb, 1);
			fcn_00657a73(sel1, text, 0xa);
			fcn_0046f940(cb, text);
		}
		if (sel2 <= 4) {
			fcn_00472170(w2, 0);
			fcn_00472170(w3, 0);
			fcn_00472170(label2, 0);
		} else {
			fcn_00472170(w2, 1);
			fcn_00472170(w3, 1);
			fcn_00472170(label2, 1);
			fcn_00657a73(sel2, text, 0xa);
			fcn_0046f940(label2, text);
		}
		if (g_100f1dc == 3 || g_100f1dc == 4) {
			cur = g_67d370;
			if (cur == w2) {
				d2_SetForm(h, 4);
				fcn_0046ed00(0, -0x4c, g_772514);
			} else if (cur == w3) {
				d2_SetForm(h, 4);
				fcn_0046ed00(0, 0x4c, g_772514);
			} else if (cur == w1) {
				d2_SetForm(h, 5);
				fcn_0046ed00(0, -0x4c, g_772514);
			} else if (cur == w0) {
				d2_SetForm(h, 5);
				fcn_0046ed00(0, 0x4c, g_772514);
			}
		}
		if (g_100f1dc == 2) {
			cur = g_67d370;
			if (cur == buttons[0])
				fcn_005a6570(obj);
			else if (cur == buttons[1])
				fcn_005a59d0(obj);
		}
	}
	ResetDisplayCounters();
	fcn_00471e30(h);
	fcn_00532ef0();
}
