

#include <string.h>
#pragma intrinsic(memset)

#include "Develop/DieGildeAddOn/game/entity_record.h"






typedef struct {
	char b[0x2f4];
} D2_GOODS_PROTO_ROW;
// SIZE 0x2f4


extern char g_868060[];
extern char g_6aacdc[];
extern int g_14ce8e0;
extern int g_100f1dc;
#include "client_dialog_state.h"
extern double g_665fb0;
extern unsigned char g_773d75;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl gm_TradeUnitsToAmount(int, int);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
void __cdecl cm_SendCopyEntityData(char*);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_ConfirmExchangeGoods(char* who, int n, int w, unsigned char k)
{
	int res;
	int h;
	int a;
	int b;
	float fa;
	char msg[0xf8];

	res = 0;
	h = d2_LoadForm(0, 0, g_6aacdc);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	io_AppendText(0x1909, w, n * 2 + 0x9a8, &((D2_GOODS_PROTO_ROW*)g_868060)[k], k);
	if (main_RunFrameLoop(d2_ConfirmExchangeGoods, 0x677c7) != 0) {
		do {
			if (g_14ce8e0 != 0 || g_100f1dc == 1) {
				g_774654 = 1;
			}
			if (g_100f1dc == 2) {
				a = gm_TradeUnitsToAmount(w, n);
				fa = (float) (a * g_665fb0);
				b = gm_TradeUnitsToAmount(1, n);
				if (!((float) b < fa)) {
					b = gm_TradeUnitsToAmount(1, n);
					fa = (float) b;
				}
				cm_SendSellObjekt(-1, *(int*) (who + 1), n, a, g_773d75, 0);
				memset(msg, 0, sizeof(msg));
				msg[4] = 0x27;
				*(int*) (msg + 0xc) = -1;
				msg[0x36] = 1;
				*(int*) (msg + 8) = ((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (who + 0x27)].entity_id;
				*(int*) (msg + 0x58) = *(int*) (who + 1);
				msg[0x5c] = k;
				*(int*) (msg + 0x60) = (int) (a - fa);
				cm_SendCopyEntityData(msg);
				res = 1;
				g_774654 = 1;
			} else if (g_100f1dc == 1) {
				g_774654 = 1;
			}
		} while (main_RunFrameLoop(d2_ConfirmExchangeGoods, 0x677c7) != 0);
	}
	d2_DestroyForm(h);
	return res;
}
