#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl gm_EvaluateCardHand(int, int*, int*, int*, int*);
int __cdecl gm_GetHighestCard(int*, int);

/* ADDRESS: GOLDTL 0x004a82b0 */
/* ADDRESS: GOLDDE 0x00496600 */
int __cdecl gm_ResolveCardGameWinner(void)
{
	int a[3];
	int b[3];
	int res[3] = { 0 };
	int flag[3] = { 0 };
	int c[3];
	int d[3];
	char* tbl;
	int sel;
	int i;
	int x;
	int y;

	tbl = g_1007cd4;
	for (i = 0; i < 3; i++) {
		if (*(int*) (tbl + i * 0x34 + 0x2c) < 0) {
			res[i] = gm_EvaluateCardHand(i, &a[i], &c[i], &b[i], &d[i]);
			*(int*) (tbl + i * 0x34 + 0x34) = res[i];
			tbl = g_1007cd4;
		} else {
			flag[i] = 1;
		}
	}
	sel = 0;
	if (flag[0] != 0) {
		sel = 1;
	} else if (flag[1] != 0) {
		sel = 0;
	} else if (res[0] == 0) {
		if (res[1] == 0) {
			x = gm_GetHighestCard((int*) (tbl + 0x40), 0);
			y = gm_GetHighestCard((int*) (tbl + 0xc), 0);
			sel = y <= x;
		} else {
			sel = 1;
		}
	} else {
		if (res[1] == 0) {
			sel = 0;
		} else if (res[1] < res[0]) {
			sel = 0;
		} else if (res[1] > res[0]) {
			sel = 1;
		} else {
			switch (res[0]) {
			case 1:
				if (a[1] < a[0]) {
					sel = 0;
				} else if (a[1] > a[0]) {
					sel = 1;
				} else {
					sel = b[0] <= b[1];
				}
				break;
			case 2:
				if (a[1] < a[0]) {
					sel = 0;
				} else if (a[1] > a[0]) {
					sel = 1;
				} else if (c[1] < c[0]) {
					sel = 0;
				} else if (c[1] > c[0]) {
					sel = 1;
				} else {
					sel = b[0] <= b[1];
				}
				break;
			case 3:
			case 5:
			case 7:
				sel = a[0] <= a[1];
				break;
			case 4:
				x = gm_GetHighestCard((int*) (tbl + 0x40), 0);
				y = gm_GetHighestCard((int*) (tbl + 0xc), 0);
				sel = y <= x;
				break;
			case 6:
			case 8:
				sel = b[0] <= b[1];
				break;
			}
		}
	}
	if (flag[2] != 0) {
		*(int*) (tbl + 0xbc) = res[sel];
		return sel;
	}
	if (res[sel] == 0 && res[2] == 0) {
		x = gm_GetHighestCard((int*) (tbl + sel * 0x34 + 0xc), 0);
		y = gm_GetHighestCard((int*) (tbl + 0x40), 0);
		if (x > y) {
			return sel;
		}
		return 1;
	}
	if (res[sel] == 0) {
		*(int*) (tbl + 0xbc) = res[2];
		return 2;
	}
	if (res[2] == 0 || res[2] < res[sel]) {
		*(int*) (tbl + 0xbc) = res[sel];
		return sel;
	}
	if (res[2] > res[sel]) {
		*(int*) (tbl + 0xbc) = res[2];
		return 2;
	}
	switch (res[sel]) {
	case 1:
		if (a[2] < a[sel]) {
			*(int*) (tbl + 0xbc) = res[sel];
		return sel;
		}
		if (a[2] > a[sel]) {
			*(int*) (tbl + 0xbc) = res[2];
			return 2;
		}
		if (b[sel] <= b[2]) {
			*(int*) (tbl + 0xbc) = res[2];
			return 2;
		}
		*(int*) (tbl + 0xbc) = res[sel];
		return sel;
	case 2:
		if (a[2] < a[sel]) {
			*(int*) (tbl + 0xbc) = res[sel];
		return sel;
		}
		if (a[2] > a[sel]) {
			*(int*) (tbl + 0xbc) = res[2];
			return 2;
		}
		if (c[2] < c[sel]) {
			*(int*) (tbl + 0xbc) = res[sel];
		return sel;
		}
		if (c[2] > c[sel]) {
			*(int*) (tbl + 0xbc) = res[2];
			return 2;
		}
		if (b[sel] <= b[2]) {
			*(int*) (tbl + 0xbc) = res[2];
			return 2;
		}
		*(int*) (tbl + 0xbc) = res[sel];
		return sel;
	case 3:
	case 5:
	case 7:
		if (a[sel] <= a[2]) {
			*(int*) (tbl + 0xbc) = res[2];
			return 2;
		}
		*(int*) (tbl + 0xbc) = res[sel];
		return sel;
	case 4:
		x = gm_GetHighestCard((int*) (tbl + sel * 0x34 + 0xc), 0);
		y = gm_GetHighestCard((int*) (tbl + 0x74), 0);
		if (x <= y) {
			sel = 2;
		}
		*(int*) (tbl + 0xbc) = res[sel];
		return sel;
	case 6:
	case 8:
		if (b[sel] <= b[2]) {
			*(int*) (tbl + 0xbc) = res[2];
			return 2;
		}
		*(int*) (tbl + 0xbc) = res[sel];
		return sel;
	}
	*(int*) (tbl + 0xbc) = res[sel];
	return sel;
}
