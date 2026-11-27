#include "client_types.h"
void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)
#include "Develop/DieGildeAddOn/game/building_prototype.h"




/* SIZE 0xe */

typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	int xc;
	char pad10[0x18];
	pos14_7f4c00 name;
	unsigned char x36;
	char pad37[0x21];
	int x58;
	int x5c;
	int x60;
	char pad64[0xc];
	int x70;
	char pad74[0x84];
} Packet;
/* SIZE 0xf8 */

typedef struct
{
	unsigned char x0;
	char pad1[0x24c];
} Shop;
/* SIZE 0x24d */

typedef struct
{
	unsigned short x0;
	char pad2[2];
	int x4;
	char pad8[0x174];
	char* x17c;
	char pad180[8];
	unsigned char x188;
	char pad189[0x93];
} Player;
/* SIZE 0x21c */

extern unsigned char* lpGebaeudePROT;
extern char* g_77255c;
extern int d2_CurrentWindowId;
extern int g_6b7fac;
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern int g_14ce8e0;
extern int g_14abc44;
#include "client_dialog_state.h"
extern int g_7746c0;
extern char* g_7746cc;
extern int g_7746f0;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_7ea360;

extern char g_7f4ca0[];
extern char g_7f4ca4[];
extern char s_6aa194[];
extern char s_6ac79c[];
extern char s_6ac7dc[];
extern char s_6ac7ec[];
extern char s_6ac7fc[];
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

void __cdecl d2_SetBackgroundTexture(const char*, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_SetElementEnabled(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl CountDisplayCounters(void);
void __cdecl d3snd_PlayWorkerOrderVoice(void);
int __cdecl cm_SendCopyEntityData(Packet*);
int __cdecl main_RunFrameLoop(void*, int);
char* __cdecl he_fn_Handlung(void);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
unsigned char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl io_AppendText(int, ...);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl d2_ShowModalMessageBox(char*, int);
void __cdecl d2_InitPlayerBar(unsigned char*, int);
void __cdecl d2_RestoreHudAfterDialog(void);
int __cdecl sv_ClearObjectSelection(void);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_DrawPanelFrame(int, int, int);
int __cdecl d2_CreateItemRowControls(int, int, int*, int);

/* ADDRESS: GOLDTL 0x005c79a0 */
void __cdecl d2_RunWorkerTrainingDialog(unsigned char* obj)
{
	char buf[0x800];
	Packet pkt;
	int out[9];


	int btnA;
	int btnB;
	int btnC;
	int dlg;
	int start;
	int cnt2;
	int cnt3;
	int cnt6c;
	int sum;
	int i; double alpha;
	int hwnd;
	BUILDING_PROTOTYPE* t;
	int j;
	char* p;
	unsigned char* e;

	btnB = 0;
	btnA = 0;
	btnC = 0;
	t = &((BUILDING_PROTOTYPE*) lpGebaeudePROT)[obj[0]];
	dlg = d2_LoadForm(0, 0, s_6ac79c);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_DrawPanelFrame(d2_CurrentWindowId, 0x72f, 0);
	d2_SetForm(dlg, 3);
	io_AppendText(0x1a46);
	d2_InitPlayerBar(obj, 1);
	d2_SetForm(dlg, 2);
	hwnd = d2_CurrentWindowId;
	d2_CreateItemRowControls(0, 0x762, out, hwnd);
	d2_CreateItemRowControls(1, 0x763, out + 3, hwnd);
	d2_CreateItemRowControls(2, 0x764, out + 6, hwnd);
	d2_SetForm(dlg, 1);
	if (t->category != 4 && t->category != 0x10) {
		d2_SetBackgroundTexture(s_6ac7fc, *(int*) g_77255c);
	}
	else {
		d2_SetBackgroundTexture(s_6ac7ec, *(int*) g_77255c);
	}
	*(int*) (g_77255c + 0x3a4) = 0;
	start = g_6b7fac;
	if (fcn_00502cd0(*(int*) (obj + 0x5d), 2, 6, 0, 0x35) != 0) {
		btnA = 1;
	}
	if (fcn_00502cd0(*(int*) (obj + 0x5d), 2, 6, 0, 0x34) != 0) {
		btnB = 1;
	}
	if (t->category == 4) {
		if (fcn_00502cd0(*(int*) (obj + 0x5d), 2, 6, 0, 0x5d) != 0) {
			btnC = 1;
		}
	}
	else if (t->category == 0x10) {
		if (fcn_00502cd0(*(int*) (obj + 0x5d), 2, 6, 0, 0x5e) != 0) {
			btnC = 1;
		}
	} else { btnC = 1; }
	if (btnA) d2_SetElementEnabled(out[0], 1);
	else d2_SetElementEnabled(out[0], 0);
	if (btnB) d2_SetElementEnabled(out[3], 1);
	else d2_SetElementEnabled(out[3], 0);
	if (btnC) d2_SetElementEnabled(out[6], 1);
	else d2_SetElementEnabled(out[6], 0);
	for (;;) {
		d2_SetForm(dlg, 1);
		i = g_6b7fac - start;
		alpha = (double) (unsigned int) i * 0.0013333333333333333;
		if (!(alpha < 0.4)) { alpha = 0.4; }
		*(float*) (g_77255c + 0x3a4) = (float) alpha;


		if (g_14ce8e0 != 0) {
			if (CountDisplayCounters() == 0) {
				g_774654 = 1;
			} else {
				sv_ClearObjectSelection();
			}
		}
		cnt2 = 0;
		cnt3 = 0;
		p = he_StartHandlungSearch(2, 0, 0x16, 3, *(int*) (obj + 1));
		if (p != 0) {
			while (p != 0) {
				if (*(char*) (p + 0xac) == 2) {
					cnt2++;
				}
				else if (*(char*) (p + 0xac) == 3) {
					cnt3++;
				}
				p = he_fn_Handlung();
			}
		}
		cnt6c = 0;
		p = he_StartHandlungSearch(2, 0, 0x6c, 3, *(int*) (obj + 1));
		while (p != 0) {
			cnt6c++;
			p = he_fn_Handlung();
		}
		hwnd = d2_CurrentWindowId;
		d2_CurrentWindowId = out[2];
		io_AppendText(s_6aa194, cnt2, 0x51e, 0x1a47, 0x16b9);
		d2_CurrentWindowId = out[5];
		io_AppendText(s_6aa194, cnt3, 0x51e, 0x1a47, 0x16ba);
		d2_CurrentWindowId = out[8];
		io_AppendText(s_6ac7dc, cnt6c, 0x51e, 0x1a48);
		if (g_100f1dc != -1 && CountDisplayCounters() != 0) {
			for (i = 0; i < 3; i++) {
				if (out[i * 3] != -1 && d2_CurrentElementId == out[i * 3]) {
					sum = cnt2 + cnt3;
					if (i == 0 || i == 1) {
						for (j = 0; j < 0x300; j++) {
							if (((Player*) g_7f4ca0)[j].x188 != 0) {
								memset(&pkt, 0, sizeof(pkt));
								if (((Player*) g_7f4ca0)[j].x17c != 0 && *((Player*) g_7f4ca0)[j].x17c == 0x16) {
									sum--;
								}
								if (sum >= 3) {
									sum = 4;
									break;
								}
								pkt.type = 0x16;
								pkt.x8 = *(int*) (g_7f4ca4 + g_774970 * 0x21c);
								pkt.xc = *(int*) (obj + 1);
								pkt.name = *(pos14_7f4c00*) &gm_GameTime;
								pkt.x36 = 1;
								if (g_7746cc != 0) {
									pkt.x60 = *(int*) (g_7746cc + 2);
								}
								else {
									pkt.x60 = -1;
								}
								pkt.x5c = ((Player*) g_7f4ca0)[j].x4;
								*(char*) &pkt.x58 = (i != 0) + 2;
								he_AssignActionSlot(obj, 0, ((Player*) g_7f4ca0)[j].x0, 0);
								cm_SendCopyEntityData(&pkt);
								sum++;
							}
						}
					}
					else {
						for (j = 0; j < 0x300; j++) {
							if (sum >= 3) {
								break;
							}
							if (((Player*) g_7f4ca0)[j].x188 != 0) {
								pkt.type = 0x6c;
								pkt.x8 = *(int*) (g_7f4ca4 + *(unsigned short*) (obj + 0x27) * 0x21c);
								pkt.xc = *(int*) (obj + 1);
								pkt.name = *(pos14_7f4c00*) &gm_GameTime;
								pkt.x36 = 1;
								pkt.x58 = ((Player*) g_7f4ca0)[j].x4;
								if (g_7746cc != 0 && *(unsigned short*) g_7746cc != 0xfd) {
									pkt.x70 = *(int*) (g_7746cc + 2);
								}
								else {
									pkt.x70 = -1;
								}
								he_AssignActionSlot(obj, 0, ((Player*) g_7f4ca0)[j].x0, 0);
								cm_SendCopyEntityData(&pkt);
								sum++;
							}
						}
					}
					if (sum == 0) {
						d2_ShowModalMessageBox((char*) g_14abc44, 0);
					}
					else {
						d3snd_PlayWorkerOrderVoice();
						sv_ClearObjectSelection();
						if (sum > 3) {
							io_FormatTextBuffer(buf, 0x1a4a, 3);
							d2_ShowModalMessageBox(buf, 0);
						}
						i = 3;
					}
				}
			}
		}
		else if (g_100f1dc != -1 && CountDisplayCounters() == 0) {
			for (i = 0; i < 3; i++) {
				if (out[i * 3] != -1 && d2_CurrentElementId == out[i * 3]) {
					if (i != 2) {
						int target = (i != 0) + 2;
						for (p = he_StartHandlungSearch(2, 0, 0x16, 3, *(int*) (obj + 1)); p != 0; p = he_fn_Handlung()) {
							if (*(unsigned char*) (p + 0xac) == target) {
								e = gm_LookupEntityRecordById(*(int*) (p + 0xb0));
								if (e != 0) {
									*(char*) (e + 0x188) = 1;
								}
							}
						}
					}
					else {
						for (p = he_StartHandlungSearch(2, 0, 0x6c, 3, *(int*) (obj + 1)); p != 0; p = he_fn_Handlung()) {
							e = gm_LookupEntityRecordById(*(int*) (p + 0xac));
							if (e != 0) {
								*(char*) (e + 0x188) = 1;
							}
						}
					}
					break;
				}
			}
		}
		if (main_RunFrameLoop((void*) d2_RunWorkerTrainingDialog, 0x677c7) == 0) {
			d2_RestoreHudAfterDialog();
			d2_DestroyForm(dlg);
			d3_EndCameraAndUiMode();
			sv_ClearObjectSelection();
			return;
		}
	}
}
