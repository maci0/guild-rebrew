#include <string.h>
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime; extern char g_7f4ca4[];
extern int g_100f1dc, d2_CurrentElementId, g_14ce8e0, g_774654;

#include "Develop/Units/d2.v1/d2_gui.h"
extern int d2_CurrentWindowId;
extern s_1015f4c g_1015f4c[];
extern int g_14a79c0[];

typedef struct Req_59ecc0 {
	int f00;                    /* 0x00 */
	unsigned char kind;         /* 0x04 */
	unsigned char pad05[3];
	int f08;                    /* 0x08 */
	int f0c;                    /* 0x0c */
	unsigned char pad10[0x18];   /* 0x10 */
	int f28;                    /* 0x28 */
	int f2c;                    /* 0x2c */
	int f30;                    /* 0x30 */
	unsigned short f34;         /* 0x34 */
	unsigned char f36;          /* 0x36 */
	unsigned char pad37;
	unsigned int list[6];
	unsigned char pad50[8];
	unsigned char f58;          /* 0x58 */
	unsigned char pad59;
	unsigned short f5a;         /* 0x5a */
	unsigned char pad5c[4];
	int f60;                    /* 0x60 */
	unsigned char pad64[0x94];
} Req_59ecc0;

int __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_00525fb0(int);
int __cdecl he_StartHandlungSearch(int, int, int, int, int);
int __cdecl he_fn_Handlung(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_DrawPanelFrame(int, int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_0052a0c0(int, int);
void __cdecl fcn_00594340(void);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_0046f9b0(int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00595e20(int, int);
void __cdecl fcn_005963f0(int, int, int, int);
int __cdecl fcn_005373e0(int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_004c35f0(void);
void __cdecl sv_ClearObjectSelection(void);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_004c4480(int);
void __cdecl fcn_00526120(int, int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x0059ecc0 */
void __cdecl fcn_0059ecc0(int gebaeude, int a1)
{
	int i;
	int h;
	int x;
	int sel;
	int cnt;
	char* p;
	unsigned int ids[7];
	int y;
	int total;
	int handles[3];
	Req_59ecc0 req;
	char text[256];

	ids[0] = 0x1c1;
	ids[1] = 0x1c2;
	ids[2] = 0x1c3;
	ids[6] = fcn_00502cd0(*(int*) (gebaeude + 0x5d), 2, 6, 0, 0x2a);
	if (fcn_00525fb0(gebaeude))
		return;
	for (i = 3; i < 6; i++) {
		ids[i] = 0;
	}
	h = he_StartHandlungSearch(2, 0, 0x15, 3, *(int*) (gebaeude + 1));
	while (h) {
		i = 0;
		do {
			if (*(unsigned short*) (h + 0xae) == ids[i]) {
				ids[i + 3] += *(unsigned char*) (h + 0xac);
				break;
			}
			i++;
		} while (i < 3);
		h = he_fn_Handlung();
	}
	total = fcn_00470820(0, 0, (char*) 0x6a9750);
	d2_CenterDialogWindows(total);
	d2_SetForm(total, 0);
	d2_DrawPanelFrame(d2_CurrentWindowId, 0x70f, 0x741);
	d2_SetForm(total, 3);
	io_AppendText(0x1806);
	fcn_0052a0c0(gebaeude, 0);
	fcn_00594340();
	d2_CenterDialogWindows(total);
	d2_SetForm(total, 2);
	y = -0x80 + *(int*) ((char*) g_1015f4c + d2_CurrentWindowId * 0x3cc) / 2;
	for (x = 0x19, cnt = 0; x < 0x109; x += 0x50, cnt++) {
		h = fcn_0046f740(y, x, (int) ids[cnt] + 0xdf, d2_CurrentWindowId);
		*(unsigned int*)&((D2_CONTROL_TL*)g_1015ea0)[h].value_05c = 1;
		*(unsigned int*)&((D2_CONTROL_TL*)g_1015ea0)[h].flags_1d0 = 3;
		*(unsigned int*)&((D2_CONTROL_TL*)g_1015ea0)[h].value_1dc = 100;
		*(unsigned int*)&((D2_CONTROL_TL*)g_1015ea0)[h].value_1e0 = 0x10;
		*(unsigned int*)&((D2_CONTROL_TL*)g_1015ea0)[h].font = 0x54;
		fcn_0046f9b0(h, g_14a79c0[(int) ids[cnt] * 2]);
		handles[cnt] = h;
		fcn_00472640(h, 1);
	}
	d2_SetOverlayAnimation(0, 0);
	fcn_00595e20(gebaeude, ids[6]);
	fcn_005963f0(total, 1, 0, gebaeude);
	sel = fcn_005373e0(0x59ecc0, 0x677c7);
	while (sel) {
		fcn_00595e20(gebaeude, ids[6]);
		fcn_005963f0(total, 1, 0, gebaeude);
		for (i = 3; i < 6; i++) {
			ids[i] = 0;
		}
		h = he_StartHandlungSearch(2, 0, 0x15, 3, *(int*) (gebaeude + 1));
		while (h) {
			i = 0;
			do {
				if (*(unsigned short*) (h + 0xae) == ids[i]) {
					ids[i + 3] += *(unsigned char*) (h + 0xac);
					break;
				}
				i++;
			} while (i < 3);
			h = he_fn_Handlung();
		}
		d2_SetForm(total, 2);
		for (i = 0; i < 3; i++) {
			fcn_00472640(handles[i], 1);
			if (ids[i + 3] == 1) {
				io_FormatTextBuffer(text, 0x1807, ids[i + 3], (int)ids[i] * 2 + 0x9a8);
			}
			else if ((int)ids[i + 3] > 1) {
				io_FormatTextBuffer(text, 0x1808, ids[i + 3], (int)ids[i] * 2 + 0x9a8);
			}
			else {
				io_FormatTextBuffer(text, 0x679060,
					(int) ids[i] * 2 + 0x9a8);
			}
			fcn_0046f9b0(handles[i], text);
		}
		if (g_100f1dc != -1) {
			for (sel = 0; sel < 3; sel++) {
				if (handles[sel] == d2_CurrentElementId)
					goto found;
			}
			goto skip_req;
		found:
			if (sel != -1) {
				memset(&req, 0, 0xf8);
				req.kind = 0x15;
				req.f36 = 1;
				req.f08 = *(int*) (*(unsigned short*) (gebaeude + 0x27) * 0x21c
					+ g_7f4ca4);
				req.f0c = *(int*) (gebaeude + 1);
				*(pos14_7f4c00*)&req.f28 = gm_GameTime;

				req.f5a = (unsigned short) ids[sel];
				req.f60 = *(int*) (a1 + 2);
				cnt = 0;
				p = g_7f4ca4;
				do {
					if (cnt >= 6)
						break;
					if (p[0x184] != 0) {
						req.list[cnt] = *(unsigned int*) p;
						cnt++;
					}
					p += 0x21c;
				} while ((int) p < 0x85a0a4);
				for (i = cnt; i < 6; i++) {
					req.list[i] = -1;
				}
				req.f58 = (unsigned char) cnt;
				if (cnt != 0) {
					fcn_004c35f0();
					sv_ClearObjectSelection();
					sel = fcn_004c5530(&req);
					while (!fcn_004c4450(sel)) {
						fcn_005373e0(0, 0x20007);
					}
					fcn_004c4480(sel);
				}
				else {
					fcn_00526120(*(int*) 0x14ab324, 4);
				}
			}
		skip_req: ;
		}
		else if (g_14ce8e0 != 0)
			g_774654 = 1;
		sel = fcn_005373e0(0x59ecc0, 0x677c7);
	}
	sv_ClearObjectSelection();
	fcn_0052a2d0();
	fcn_00471e30(total);
	return fcn_00532ef0();
}
