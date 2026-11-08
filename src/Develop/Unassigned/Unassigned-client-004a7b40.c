extern char* g_1007cd4;
extern unsigned char g_773d75;

void __cdecl fcn_0050b750(int amount, unsigned char k);
void __cdecl fcn_004c51a0(int a, int b, unsigned char k, int amount);
#include "client_types.h"
typedef Card_1007ce0 Card;

extern Card_1007ce0 g_1007ce0[24];

/* ADDRESS: GOLDTL 0x004a7b40 */
void __cdecl fcn_004a7b40(void)
{
	int i;

	for (i = 0; i < 3; i++) {
		if (*(int*) (g_1007cd4 + 0x2c + i * 0x34) < 0) {
			*(int*) (g_1007cd4 + 0xa0) += *(int*) (g_1007cd4 + 0xac);
			if (i == 0) {
				fcn_0050b750(*(int*) (g_1007cd4 + 0xac), g_773d75);
				fcn_004c51a0(-1, *(int*) (*(char**) (g_1007cd4 + 4) + 4), g_773d75, *(int*) (g_1007cd4 + 0xac));
			}
			*(int*) (g_1007cd4 + 0x20 + i * 0x34) += *(int*) (g_1007cd4 + 0xac);
		}
	}
}

/* The 0x180-byte native table is addressed literally; no data row owns it. */
/* ADDRESS: GOLDTL 0x004a7be0 */
void __cdecl fcn_004a7be0(void)
{
	int counts[6];
	int off;
	int v13;
	int v11;
	int v14;
	int i;
	int g;
	int j;
	int c;
	int best;

	v14 = 0;
	i = 1;
	off = 0x34;
	do {
		v13 = 0;
		v11 = 0;
		best = 0;
		for (g = 0; g < 6; g++) {
			c = 0;
			for (j = 0; j < 4; j++) {
				if (((int*) 0x01007ce8)[(g * 4 + j) * 4] == i) {
					c++;
				}
			}
			if (c > 1) {
				v13++;
			}
			if (c > v11) {
				v11 = c;
			}
			counts[g] = c;
		}
		for (g = 0; g < 4; g++) {
			c = 0;
			for (j = 0; j < 6; j++) {
				if (((int*) 0x01007ce8)[g * 4 + j * 16] == i) {
					c++;
				}
			}
			if (c > best) {
				best = c;
				v14 = g;
			}
			counts[g] = c;
		}
		if ((unsigned char) g_1007cd4[0xb5] < 5 && v13 <= 1 && v11 < 2) {
			*(int*) (g_1007cd4 + 0x30 + off) = 3;
		} else if ((unsigned char) g_1007cd4[0xb5] == best) {
			*(int*) (g_1007cd4 + 0x30 + off) = 2;
		} else if (*(int*) g_1007cd4 < 6 && (unsigned char) g_1007cd4[0xb5] - best <= 1) {
			for (c = 0; c < 6; c++) {
				if (((int*) 0x01007cec)[v14 * 4 + c * 16 - 1] != i &&
				    ((int*) 0x01007cec)[v14 * 4 + c * 16] == 0) {
					break;
				}
			}
			if (c == 6) {
				*(int*) (g_1007cd4 + 0x30 + off) = 2;
			} else if ((unsigned char) g_1007cd4[0xb5] == 5 && v11 < 2) {
				*(int*) (g_1007cd4 + 0x30 + off) = 0;
			} else {
				*(int*) (g_1007cd4 + 0x30 + off) = 1;
			}
		} else if ((unsigned char) g_1007cd4[0xb5] == 5 && v11 < 2) {
			*(int*) (g_1007cd4 + 0x30 + off) = 0;
		} else {
			*(int*) (g_1007cd4 + 0x30 + off) = 1;
		}
		off += 0x34;
		i++;
	} while (off < 0x9c);
}

/* ADDRESS: GOLDTL 0x004a7f90 */
void __cdecl fcn_004a7f90(int* h, int* rank_n, int* rank, int* suit_n, int* suit)
{
	int suits[4] = { 0 };
	int ranks[6] = { 0 };
	int n;
	int i;

	n = ((unsigned char*)g_1007cd4)[0xb5];
	for (i = 2; i < n; i++) {
		suits[g_1007ce0[h[i + 2]].suit]++;
		ranks[g_1007ce0[h[i + 2]].rank]++;
	}
	*rank_n = ranks[0];
	*rank = 0;
	for (i = 1; i < 6; i++) {
		if (ranks[i] > *rank_n) {
			*rank_n = ranks[i];
			*rank = i;
		}
	}
	*suit_n = suits[0];
	*suit = 0;
	for (i = 1; i < 4; i++) {
		if (suits[i] > *suit_n) {
			*suit_n = suits[i];
			*suit = i;
		}
	}
}
