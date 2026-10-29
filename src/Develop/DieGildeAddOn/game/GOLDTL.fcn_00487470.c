#include <string.h>

extern int lpGebaeudePROT;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;
extern char g_7f4ca0[];
extern char g_7f4ca2[];
extern unsigned char g_773d75;

int __cdecl gm_RandomMod(int);
int __cdecl fcn_00508da0(unsigned char* e);
int __cdecl fcn_0050cf50(int, int);
char* __cdecl fcn_00502cd0(int, int, int, int, ...);
float __cdecl eval_ObjektPreis2Credits(int id, int pct);
char* __cdecl gm_GetEntityTableEntry(char*);
void __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c4ef0(char*);
void __cdecl fcn_004c5150(int, int, char, int);
void __cdecl fcn_004c5530(void*);

/* Picks a trade partner for the selected market stall and sends the offer.
 * The candidate list of the stall belongs to the entity table row of the
 * current shop; the first pass prefers a partner that the guild filter does
 * not already lock out, the fallback pass only accepts the first free one. */
/* ADDRESS: GOLDTL 0x00487470 */
void __cdecl fcn_00487470(char* a0)
{
	int found;
	int cand;
	float amountf;
	unsigned char pkt2[0xf8];
	unsigned char pkt1[0xf8];
	char* p;
	char* row;
	char* other;
	int i;
	int id;
	int amount;
	char kind;
	unsigned short w;

	found = 0;
	cand = 0xfd;
	if (*(unsigned char*) (a0 + 0x1c8) & 8) {
		return;
	}
	if ((short) g_7f4c04 != 7 && (short) g_7f4c04 != 0xc && (short) g_7f4c04 != 0x12) {
		*(int*) (a0 + 0x1b4) &= ~0x400;
		return;
	}
	if (*(int*) (a0 + 0x1b4) & 0x400) {
		return;
	}
	p = (char*) *(int*) (a0 + 0x16c);
	*(int*) (a0 + 0x1b4) |= 0x400;
	kind = g_7f4ca2[*(unsigned short*) (p + 0x27) * 0x21c];
	if (kind != 6 && kind != 7) {
		return;
	}
	if (!(*(int*) (a0 + 0x1b4) & 8)) {
		return;
	}
	if (fcn_00508da0((unsigned char*) p) < (gm_RandomMod(0x14) & 0xffff) + 0x4b) {
		amountf = (float) fcn_0050cf50((int) p, 100) * *(float*) 0x664138 * *(float*) 0x664138;
		if (amountf < *(float*) 0x662a7c) {
			amountf = 128.0f;
		}
		if (amountf < (float) *(int*) (a0 + 0x1b8) * *(float*) 0x662a6c) {
			memset(pkt1, 0, 0xf8);
			pkt1[4] = 0x1c;
			*(int*) (pkt1 + 8) = *(int*) (0x7f4ca4 + *(unsigned short*) (p + 0x27) * 0x21c);
			*(int*) (pkt1 + 0xc) = -1;
			pkt1[0x36] = 1;
			*(int*) (pkt1 + 0x58) = *(int*) (p + 1);
			*(int*) (pkt1 + 0x5c) = 100 - *(char*) (p + 0x5c);
			fcn_004c4eb0((char*) 0x67e330);
			fcn_004c5150(-1,
						 *(int*) (0x7f4ca4 + *(unsigned short*) (p + 0x27) * 0x21c),
						 (char) g_773d75,
						 (int) amountf);
			fcn_004c5530(pkt1);
			fcn_004c4ef0((char*) 0x67e330);
			other = gm_GetEntityTableEntry(g_7f4ca0 + *(unsigned short*) (p + 0x27) * 0x21c);
			if (other != 0) {
				*(int*) (other + 0x44) = (int) ((float) *(int*) (other + 0x44) + amountf);
			}
			*(int*) (a0 + 0x1b8) = (int) ((float) *(int*) (a0 + 0x1b8) - amountf);
		}
	}
	p = (char*) *(int*) (a0 + 0x16c);
	id = *(unsigned char*) p;
	row = (char*) (lpGebaeudePROT + id + id * 0x24c);
	if (*(unsigned char*) (row + 0x22) != 0) {
		i = 0;
		do {
			if (found != 0) {
				goto have;
			}
			w = *(unsigned short*) (row + 0x23 + i * 2);
			if (w & 0x7fff) {
				id = w & 0x7fff;
				kind = *(char*) (0x99ec10 + id * 0x41);
				if (kind != 2 && kind != 6) {
					if (cand != 0xfd && fcn_00502cd0(*(int*) (*(int*) (a0 + 0x16c) + 0x5d), 2, 6, 0, id) == 0) {
						found = id;
					}
				} else {
					cand = id;
				}
			}
			i++;
		} while (i < *(unsigned char*) (row + 0x22));
		if (found != 0) {
			goto have;
		}
	}
	i = 0;
	cand = 0;
	if (*(unsigned char*) (row + 0x22) == 0) {
		return;
	}
	do {
		if (found != 0) {
			goto have;
		}
		w = *(unsigned short*) (row + 0x23 + i * 2);
		if (w & 0x7fff) {
			id = w & 0x7fff;
			kind = *(char*) (0x99ec10 + id * 0x41);
			if (kind != 2 && kind != 6) {
				if (cand == 0xfd && fcn_00502cd0(*(int*) (*(int*) (a0 + 0x16c) + 0x5d), 2, 6, 0, id) == 0) {
					found = id;
				}
			} else {
				cand = id;
			}
		}
		i++;
	} while (i < *(unsigned char*) (row + 0x22));
	if (found == 0) {
		return;
	}

have:
	p = fcn_00502cd0(*(int*) (*(int*) (a0 + 0x16c) + 0x5d), 1, 0, cand);
	if (p != 0) {
		amount = (int) eval_ObjektPreis2Credits(found, 100);
		if (*(int*) (a0 + 0x1b8) > amount * 3) {
			memset(pkt2, 0, 0xf8);
			pkt2[0x2c] = 2;
			*(int*) (pkt2 + 8) = *(int*) (0x7f4ca4 + *(unsigned short*) (p + 0x25) * 0x21c);
			*(int*) (pkt2 + 0xc) = *(int*) (p + 1);
			*(int*) (pkt2 + 0x28) = g_7f4c00;
			*(int*) (pkt2 + 0x2c) = g_7f4c04;
			*(int*) (pkt2 + 0x30) = g_7f4c08;
			*(unsigned short*) (pkt2 + 0x34) = g_7f4c0c;
			pkt2[0x36] = 1;
			*(unsigned short*) (pkt2 + 0x58) = (unsigned short) found;
			*(int*) (pkt2 + 0x5c) = *(int*) (p + 2);
			*(int*) (pkt2 + 0x64) = 1;
			other = gm_GetEntityTableEntry(g_7f4ca0 + *(unsigned short*) (p + 0x25) * 0x21c);
			if (other != 0) {
				*(int*) (other + 0x40) = *(int*) (other + 0x40) + amount;
			}
			fcn_004c4eb0((char*) 0x67e31c);
			fcn_004c5150(-1,
						 *(int*) (0x7f4ca4 + *(unsigned short*) (p + 0x25) * 0x21c),
						 (char) g_773d75,
						 amount);
			fcn_004c5530(pkt2);
			fcn_004c4ef0((char*) 0x67e31c);
			*(int*) (a0 + 0x1b8) = *(int*) (a0 + 0x1b8) - amount;
		}
	}
	*(int*) (a0 + 0x1c8) |= 8;
}
