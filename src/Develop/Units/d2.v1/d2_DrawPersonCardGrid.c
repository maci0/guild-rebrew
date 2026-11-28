/* Item cell used by the gold-trade grid. */
typedef struct D2_PERSON_CARD_ITEM {
	int* obj;		/* +0x00 */
	int win;		/* +0x04 */
	int win2;		/* +0x08 */
	int pad0c;		/* +0x0c */
	int x;			/* +0x10 */
	int y;			/* +0x14 */
	int cw18;		/* +0x18 */
	int cw1c;		/* +0x1c */
	int cw20;		/* +0x20 */
	int cw24;		/* +0x24 */
	int cw28;		/* +0x28 */
	int pad2c[3];		/* +0x2c */
} D2_PERSON_CARD_ITEM;			/* SIZE 0x38 */
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_AddElementToWindow();
int __cdecl io_FormatTextBuffer();
int __cdecl d2_ShowCenteredText();
int __cdecl d2_AddWindowValueGauge();
int __cdecl d2_CreateGuiWindow();
float __cdecl gm_CalcEntityFavor(unsigned int, unsigned int, unsigned int);
int __cdecl d2_SetElementEnabled();
int __cdecl gm_MatchesTargetFilter(unsigned short, unsigned short, int, int);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x005c99a0 */
int __cdecl d2_DrawPersonCardGrid(int a0, int mode, int filter, int itemCount, D2_PERSON_CARD_ITEM* items, int owner)
{
	D2_PERSON_CARD_ITEM* item;
	int counts[3];
	int rows;
	int row;
	int col;
	int idx;
	int n;
	int ybase;
	int x;
	int y;
	int left;
	char buf[256];

	counts[0] = -1;
	counts[1] = -1;
	counts[2] = -1;
	rows = 0;
	ybase = 0;
	switch (itemCount) {
	case 1:
		rows = 1;
		ybase = 0x80;
		counts[0] = 1;
		break;
	case 2:
		rows = 1;
		ybase = 0x80;
		counts[0] = 2;
		break;
	case 3:
		rows = 1;
		ybase = 0x80;
		counts[0] = 3;
		break;
	case 4:
		rows = 2;
		ybase = 0x40;
		counts[0] = 2;
		counts[1] = 2;
		break;
	case 5:
		rows = 2;
		ybase = 0x40;
		counts[0] = 3;
		counts[1] = 2;
		break;
	case 6:
		rows = 2;
		ybase = 0x40;
		counts[0] = 3;
		counts[1] = 3;
		break;
	case 7:
		rows = 3;
		counts[0] = 3;
		counts[1] = 2;
		counts[2] = 2;
		break;
	case 8:
		rows = 3;
		counts[0] = 3;
		counts[1] = 2;
		counts[2] = 3;
		break;
	}
	idx = 0;
	for (row = 0; row < rows; row++) {
		n = counts[row];
		for (col = 0; col < n; col++, idx++) {
			if (idx >= itemCount) {
				break;
			}
			items[idx].y = row * 0x80 + ybase;
			if (n == 3) {
				items[idx].x = col * 0xca;
			} else if (n == 2) {
				items[idx].x = col * 0xca + 0x65;
			} else {
				items[idx].x = 0xca;
			}
		}
	}
	for (row = 0; row < itemCount; row++) {
		item = &items[row];
		x = item->x + 0x65;
		y = item->y + 0x23;
		left = x - (int) *(short*) (d2_FileObjTable + 0x1ebd8) / 2;
		item->win = d2_AddElementToWindow(left, y, 0x5da, d2_CurrentWindowId);
		if (item->obj != 0) {
			if (*(char*) ((int) item->obj + 2) == 6 || *(char*) ((int) item->obj + 2) == 7 || *(char*) ((int) item->obj + 2) == 5) {
				d2_AddElementToWindow(left - 0x20, y, *(int*) ((int) item->obj + 0x54), d2_CurrentWindowId);
			}
			item->cw18 = d2_AddElementToWindow(x - (int) *(short*) (d2_FileObjTable + 0x50 + *(int*) ((int) item->obj + 0x18c) * 0x54) / 2 - 3, y + 1, *(int*) ((int) item->obj + 0x18c), d2_CurrentWindowId);
			d2_AddElementToWindow(left + 3, y + 3, item->cw1c, d2_CurrentWindowId);
			if (item->cw20 != 0) {
				d2_AddElementToWindow(left + 3, (int) *(short*) (d2_FileObjTable + 0x1ebda) - 0x13 + y, item->cw20, d2_CurrentWindowId);
			}
			if (item->cw24 != 0) {
				d2_AddElementToWindow((int) *(short*) (d2_FileObjTable + 0x1ebd8) - 0x10 + (left), y + 3, item->cw24, d2_CurrentWindowId);
			}
			d2_AddElementToWindow((int) *(short*) (d2_FileObjTable + 0x1ebd8) - 0x10 + (left), (int) *(short*) (d2_FileObjTable + 0x1ebda) - 0x13 + y, item->cw28, d2_CurrentWindowId);
			if (mode == 7) {
				io_FormatTextBuffer(buf, 0x6ac964, (*(char*) ((int) item->obj + 9) ? 0x11e : 0x114) + (unsigned int) *(unsigned char*) ((int) item->obj + 0xd), *(unsigned short*) item->obj);
				d2_ShowCenteredText(buf, x, item->y, 0xca, 0x56);
				io_FormatTextBuffer(buf, 0x679060, (*(char*) ((int) item->obj + 9) ? 0x27b : 0x253) + (unsigned int) *(unsigned char*) ((int) item->obj + 0x169));
				d2_ShowCenteredText(buf, x, item->y + 0xf, 0xca, 0x56);
			} else {
				io_FormatTextBuffer(buf, 0x6ac964, (*(char*) ((int) item->obj + 9) ? 0x11e : 0x114) + (unsigned int) *(unsigned char*) ((int) item->obj + 0xd), *(unsigned short*) item->obj);
				d2_ShowCenteredText(buf, x, item->y, 0xca, 0x56);
				io_FormatTextBuffer(buf, 0x6ac95c, *(unsigned short*) item->obj);
				d2_ShowCenteredText(buf, x, item->y + 0xf, 0xca, 0x56);
			}
			if (item->obj != (int*) owner && *(char*) ((int) item->obj + 2) != 6) {
				item->win2 = d2_AddWindowValueGauge(x - 0x23, (int) *(short*) (d2_FileObjTable + 0x1ebda) + 5 + y, 0x40, 0, 100, 0x75, 0x442, d2_CurrentWindowId);
				if (*(char*) ((int) item->obj + 2) == 7) {
					d2_CreateGuiWindow(item->win2, 0, 100, 0, 1);
				} else {
					d2_CreateGuiWindow(item->win2, 0, 100, (int) gm_CalcEntityFavor(*(unsigned short*) owner, *(unsigned short*) item->obj, 1));
				}
				d2_SetElementEnabled(item->win2, 1);
				((D2_CONTROL_TL*)(*(int*)&d2_Controls))[item->win2].value_05c = 1;
			}
			if (owner != 0 && *(char*) (owner + 2) == 6 && *(int*) ((int) item->obj + 0x210) == *(int*) (owner + 4)) {
				d2_AddElementToWindow((int) *(short*) (d2_FileObjTable + 0x1ebd8) + (left), y, 0x6d3, d2_CurrentWindowId);
			}
			if (filter == 0 || gm_MatchesTargetFilter(*(unsigned short*) &gm_LocalPlayerSlot, *(unsigned short*) item->obj, filter, 0) != 0) {
				((D2_CONTROL_TL*)(*(int*)&d2_Controls))[item->win].value_05c = 1;
				((D2_CONTROL_TL*)(*(int*)&d2_Controls))[item->win].flags_1d0 = 3;
				*(int*)&((D2_CONTROL_TL*)(*(int*)&d2_Controls))[item->win].associated_object = (int) item->obj;
			}
		}
	}
	return 0;
}
