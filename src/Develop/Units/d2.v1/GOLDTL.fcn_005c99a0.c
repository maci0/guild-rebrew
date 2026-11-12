/* Item cell used by the gold-trade grid. */
typedef struct Item_5c99a0 {
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
} Item_5c99a0;			/* SIZE 0x38 */

int __cdecl fcn_0046f740();
int __cdecl io_FormatTextBuffer();
int __cdecl fcn_005c9090();
int __cdecl fcn_004677e0();
int __cdecl fcn_00472380();
float __cdecl fcn_0050f980(unsigned int, unsigned int, unsigned int);
int __cdecl fcn_00472640();
int __cdecl fcn_005cf720();
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x005c99a0 */
int __cdecl fcn_005c99a0(int a0, int mode, int filter, int itemCount, int cells, int owner)
{
	Item_5c99a0* items;
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
	int v;
	int* obj;
	int t;
	char buf[256];

	items = (Item_5c99a0*) cells;
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
	if (rows > 0) {
		for (row = 0; row < rows; row++) {
			n = counts[row];
			for (col = 0; col < n; col++) {
				if (idx >= itemCount) {
					break;
				}
				items[idx].y = ybase;
				if (n == 3) {
					items[idx].x = col * 0xca;
				} else if (n == 2) {
					items[idx].x = col * 0xca + 0x65;
				} else {
					items[idx].x = 0xca;
				}
				idx++;
			}
			ybase += 0x80;
		}
	}
	if (itemCount <= 0) {
		return 0;
	}
	t = itemCount;
	while (t != 0) {
		x = items->x + 0x65;
		y = items->y + 0x23;
		left = x - (int) *(short*) (*(int*) &g_772500 + 0x1ebd8) / 2;
		items->win = fcn_0046f740(left, y, 0x5da, *(int*) &g_772514);
		obj = items->obj;
		if (obj != 0) {
			if (*(char*) ((int) obj + 2) == 6 || *(char*) ((int) obj + 2) == 7 || *(char*) ((int) obj + 2) == 5) {
				fcn_0046f740(left - 0x20, y, *(int*) ((int) obj + 0x54), *(int*) &g_772514);
			}
			obj = items->obj;
			v = (int) *(short*) (*(int*) &g_772500 + 0x50 + *(int*) ((int) obj + 0x18c) * 0x54) / 2;
			items->cw18 = fcn_0046f740(x - v - 3, y + 1, *(int*) ((int) obj + 0x18c), *(int*) &g_772514);
			fcn_0046f740(left + 3, y + 3, items->cw1c, *(int*) &g_772514);
			if (items->cw20 != 0) {
				fcn_0046f740(left + 3, (int) *(short*) (*(int*) &g_772500 + 0x1ebda) - 0x13 + y, items->cw20, *(int*) &g_772514);
			}
			if (items->cw24 != 0) {
				fcn_0046f740((int) *(short*) (*(int*) &g_772500 + 0x1ebd8) - 0x10 + (left), y + 3, items->cw24, *(int*) &g_772514);
			}
			fcn_0046f740((int) *(short*) (*(int*) &g_772500 + 0x1ebd8) - 0x10 + (left), (int) *(short*) (*(int*) &g_772500 + 0x1ebda) - 0x13 + y, items->cw28, *(int*) &g_772514);
			obj = items->obj;
			if (mode != 7) {
				io_FormatTextBuffer(buf, 0x6ac964, (-(unsigned int) (*(char*) ((int) obj + 9) != 0) & 10) + 0x114 + (unsigned int) *(unsigned char*) ((int) obj + 0xd), *(unsigned short*) obj);
				fcn_005c9090(buf, x, items->y, 0xca, 0x56);
				io_FormatTextBuffer(buf, 0x6ac95c, *(unsigned short*) items->obj);
			} else {
				io_FormatTextBuffer(buf, 0x6ac964, (-(unsigned int) (*(char*) ((int) obj + 9) != 0) & 10) + 0x114 + (unsigned int) *(unsigned char*) ((int) obj + 0xd), *(unsigned short*) obj);
				fcn_005c9090(buf, x, items->y, 0xca, 0x56);
				obj = items->obj;
				v = (-(unsigned int) (*(char*) ((int) obj + 9) != 0) & 0x28) + 0x253 + (unsigned int) *(unsigned char*) ((int) obj + 0x169);
				io_FormatTextBuffer(buf, 0x679060, v);
			}
			fcn_005c9090(buf, x, items->y + 0xf, 0xca, 0x56);
			if (items->obj != (int*) owner && *(char*) ((int) items->obj + 2) != 6) {
				items->win2 = fcn_004677e0(x - 0x23, (int) *(short*) (*(int*) &g_772500 + 0x1ebda) + 5 + y, 0x40, 0, 100, 0x75, 0x442, *(int*) &g_772514);
				if (*(char*) ((int) items->obj + 2) != 7) {
					v = (int) fcn_0050f980(*(unsigned short*) owner,
					    *(unsigned short*) items->obj, 1);
					fcn_00472380(items->win2, 0, 100, v);
				} else {
					fcn_00472380(items->win2, 0, 100, 0);
				}
				fcn_00472640(items->win2, 1);
				*(int*) (*(int*) &g_1015ea0 + 0x5c + items->win2 * 0x2f4) = 1;
			}
			if (owner != 0 && *(char*) (owner + 2) == 6 && *(int*) ((int) items->obj + 0x210) == *(int*) (owner + 4)) {
				fcn_0046f740((int) *(short*) (*(int*) &g_772500 + 0x1ebd8) + (left), y, 0x6d3, *(int*) &g_772514);
			}
			if (filter == 0 || fcn_005cf720(*(unsigned short*) &g_774970, *(unsigned short*) items->obj, filter, 0) != 0) {
				*(int*) (*(int*) &g_1015ea0 + 0x5c + items->win * 0x2f4) = 1;
				*(int*) (*(int*) &g_1015ea0 + 0x1d0 + items->win * 0x2f4) = 3;
				*(int*) (*(int*) &g_1015ea0 + 0x2f0 + items->win * 0x2f4) = (int) items->obj;
			}
		}
		items++;
		t--;
	}
	return 0;
}
