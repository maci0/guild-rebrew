#include "client_types.h"

extern char* g_1007cd4;
extern Card_1007ce0 g_1007ce0[24];

int __cdecl gm_RandomMod(int);
void __cdecl fcn_004a7af0(void*, int);

/* ADDRESS: GOLDTL 0x004a7900 */
void __cdecl fcn_004a7900(void)
{
	char* p;
	char* q;
	char* seat;
	int best_row;
	int best_row2;
	int best_col;
	int move;
	int off;
	int cnt[6];
	int count;
	int max_row;
	int max_col;
	int pairs;
	int i;
	int j;
	int k;

	best_row = 0;
	best_row2 = 0;
	best_col = 0;
	move = -1;
	k = 1;
	off = 0x34;
	do {
		i = 0;
		max_row = 0;
		pairs = 0;
		max_col = 0;
		for (i = 0; i < 6; i++) {
			count = 0;
			for (j = 0; j < 4; j++) {
				if (g_1007ce0[i * 4 + j].count == k) {
					count++;
				}
			}
			if (count > 1) {
				pairs++;
			}
			if (count > max_row) {
				best_row2 = best_row;
				max_row = count;
				best_row = i;
			}
			cnt[i] = count;
		}
		for (j = 0; j < 4; j++) {
			count = 0;
			for (i = 0; i < 6; i++) {
				if (g_1007ce0[i * 4 + j].count == k) {
					count++;
				}
			}
			if (count > max_col) {
				max_col = count;
				best_col = j;
			}
			cnt[j] = count;
		}
		seat = (char*) (off + (int) g_1007cd4 + 4);
		switch (*(int*) (off + (int) g_1007cd4 + 0x30)) {
		case 0:
			move = gm_RandomMod(3) & 0xffff;
			break;
		case 1:
			if (pairs == 1) {
				if (g_1007ce0[*(int*) (seat + 8)].rank != best_row) {
					move = 0;
				} else if (g_1007ce0[*(int*) (seat + 0xc)].rank == best_row) {
					break;
				} else {
					move = 1;
				}
			} else if (pairs == 2) {
				if (g_1007ce0[*(int*) (seat + 8)].rank == best_row
				    || g_1007ce0[*(int*) (seat + 8)].rank == best_row2) {
					if (g_1007ce0[*(int*) (seat + 0xc)].rank == best_row
					    || g_1007ce0[*(int*) (seat + 0xc)].rank == best_row2) {
						break;
					}
					move = 1;
				} else {
					move = 0;
				}
			}
			break;
		case 2:
			if (g_1007ce0[*(int*) (seat + 8)].suit != best_col) {
				move = 0;
			} else if (g_1007ce0[*(int*) (seat + 0xc)].suit == best_col) {
				break;
			} else {
				move = 1;
			}
			break;
		case 3:
			if (pairs == 1) {
				if (g_1007ce0[*(int*) (seat + 8)].rank != best_row) {
					if (g_1007ce0[*(int*) (seat + 0xc)].rank == best_row) {
						break;
					}
					move = 1;
				} else {
					move = 0;
				}
			}
			break;
		}
		if (move >= 0) {
			fcn_004a7af0(seat, move);
		}
		off += 0x34;
		k++;
	} while (off < 0x9c);
}
