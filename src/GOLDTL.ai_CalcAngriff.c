#include <stdio.h>
#include <string.h>

#include "client_types.h"

typedef struct {
	unsigned short demand;
	unsigned short supply;
	char pad4[0x14];
} Cell99ef80;

extern pos14_7f4c00 g_7f4c00;
extern char* g_entity_type_table;
extern unsigned char* g_entity_ptr;
extern char* g_773da8;
extern char g_7f4ca0[];
extern char g_7f4ca4[];

unsigned short __cdecl gm_RandomMod(int);
char* __cdecl fcn_00504e70(int);
char* __cdecl fcn_00502cd0(int, int, int, int);
char* __cdecl gm_NextEntityQueryMatch(void);
char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl fcn_005462a0(void);
int __cdecl fcn_0055c050(char*);
int __cdecl fcn_004fa6f0(int, int*, int*);
int __cdecl fcn_0050c4e0(unsigned char*);
int __cdecl fcn_0050d0c0(char*, int);
void __cdecl fcn_004c5530(char*);

/* ADDRESS: GOLDTL 0x00480c60 */
int __cdecl ai_CalcAngriff(char* a1, int a2)
{
	char msg[0xf8];
	char buf[0x400];
	float w;
	float best;
	float fmax;
	char* nm;
	int r;
	float v;
	int b;
	int a;
	char* cand;
	char* p;
	char* q;
	char* t;
	Cell99ef80* cell;
	int n;
	int i;
	int kind;
	char* rec;

	nm = a1 + 0x30;
	sprintf(buf, "ai_CalcAngriff(): Meister %s m\xf6" "chte angreifen", nm);
	if (*(int*) (a1 + 0x1c0) != -1) {
		cand = fcn_00504e70(*(int*) (a1 + 0x1c0));
		if (cand == 0) {
			*(int*) (a1 + 0x1c0) = -1;
		} else if (*(unsigned short*) (cand + 0x27) == *(unsigned short*) (*(char**) (a1 + 0x16c) + 0x27)) {
			*(int*) (a1 + 0x1c0) = -1;
		}
	}
	if (*(int*) (a1 + 0x1c0) == -1) {
		fmax = 0.0f;
		a = 8;
		b = 8;
		for (i = 0; i < 8; i++) {
			for (n = 0; n < 8; n++) {
				cell = (Cell99ef80*) ((char*) 0x99ef80 + (i + n * 8) * 0x18);
				v = (float) cell->demand * *(float*) 0x662a34 + cell->supply;
				/* native compares as !(fmax > v) (C3|C0 test), not the
				   NaN-safe <= form */
				if (!(fmax > v)) {
					fmax = v;
				}
			}
		}
		if (fmax == 0.0f) {
			fmax = 1.0f;
		}
		cand = 0;
		n = 0x100;
		for (p = (char*) g_entity_ptr; n != 0; n--, p += 0xa9) {
			if (*(unsigned char*) p == 0) {
				continue;
			}
			if (*(unsigned short*) (p + 0x27) == *(unsigned short*) (*(char**) (a1 + 0x16c) + 0x27)) {
				continue;
			}
			if (*(unsigned short*) (p + 0x27) == 0xffff) {
				continue;
			}
			if (*(unsigned char*) (p + 0x5a) & 1) {
				continue;
			}
			if (*(unsigned short*) (p + 0x27) == *(unsigned short*) g_773da8) {
				continue;
			}
			kind = ((unsigned char*) g_entity_type_table)[*(unsigned char*) p + *(unsigned char*) p * 0x24c];
			if (kind != 0x13 && kind != 4 && kind != 0x10) {
				continue;
			}
			if (fcn_0055c050(p) == 0) {
				continue;
			}
			if (*(int*) (p + 0x61) != 0 && fcn_004fa6f0(*(int*) (p + 0x61) + 0x4c, &a, &b) != 0) {
				r = (b + a * 8) * 0x18;
				w = 1.0f - ((float) *(unsigned short*) ((char*) 0x99ef80 + r) * *(float*) 0x662a34 + *(unsigned short*) ((char*) 0x99ef80 + r + 2)) / fmax;
			} else {
				w = 0.0f;
			}
			w = (*(float*) 0x662924 - (float) fcn_0050c4e0((unsigned char*) p)) * w * *(double*) 0x662908;
			r = gm_RandomMod(0x64);
			w = (float) r * w * 0.01;
			if (cand == 0) {
				best = w;
			} else {
				v = (float) fcn_0050d0c0(p, 0) * w;
				if ((float) fcn_0050d0c0(cand, 0) * best < v) {
					best = w;
				} else {
					continue;
				}
			}
			cand = p;
		}
		*(int*) (a1 + 0x1c0) = *(int*) (cand + 1);
	}
	if (cand != 0) {
		kind = ((unsigned char*) g_entity_type_table)[*(unsigned char*) cand + *(unsigned char*) cand * 0x24c];
		if (kind == 0x13 || kind == 4 || kind == 0x10) {
	for (q = fcn_00502cd0(*(int*) (*(char**) (a1 + 0x16c) + 0x5d), 1, 0, 0xca); q != 0; q = gm_NextEntityQueryMatch()) {
		if (*(int*) (q + 0x2a) != *(int*) (cand + 1)) {
			continue;
		}
		if (*(unsigned char*) (q + 0x37) < gm_RandomMod(0x32) + 0x32) {
			break;
		}
		if (a2 < 3) {
			return 0;
		}
		for (t = fcn_005463a0(2, 0, 0x40, 3, *(int*) (*(char**) (a1 + 0x16c) + 1)); t != 0; t = fcn_005462a0()) {
			if (*(int*) (t + 0xac) == *(int*) (cand + 1)) {
				goto log2;
			}
		}
		for (t = fcn_005463a0(2, 0, 0x3f, 3, *(int*) (*(char**) (a1 + 0x16c) + 1)); t != 0; t = fcn_005462a0()) {
			if (*(int*) (t + 0xac) == *(int*) (cand + 1)) {
				goto log2;
			}
		}
		for (t = fcn_005463a0(2, 0, 0x49, 3, *(int*) (*(char**) (a1 + 0x16c) + 1)); t != 0; t = fcn_005462a0()) {
			if (*(int*) (t + 0xac) == *(int*) (cand + 1)) {
				goto log2;
			}
		}
		sprintf(buf, "ai_CalcAngriff(): Meister %s greift an '%s' ", nm, cand + 5);
		memset(msg, 0, sizeof(msg));
		msg[4] = 0x49;
		*(int*) (msg + 8) = *(int*) (g_7f4ca4 + *(unsigned short*) (*(char**) (a1 + 0x16c) + 0x27) * 0x21c);
		*(int*) (msg + 0xc) = *(int*) (*(char**) (a1 + 0x16c) + 1);
		*(int*) (msg + 0x28) = *(int*) &g_7f4c00;
		*(int*) (msg + 0x2c) = g_7f4c00.b;
		*(int*) (msg + 0x30) = g_7f4c00.c;
		*(short*) (msg + 0x34) = g_7f4c00.d;
		msg[0x36] = 1;
		*(int*) (msg + 0x58) = *(int*) (cand + 1);
		*(int*) (msg + 0x5c) = *(int*) (*(char**) (a1 + 0x16c) + 1);
		n = a2;
		if (n >= 8) {
			n = 8;
		}
		i = 0;
		if (n > 0) {
			rec = g_7f4ca0 + 0x165;
			do {
				if ((int) rec >= 0x85a205) {
					break;
				}
				if (*(short*) (rec - 0x165) != -1 && *(int*) (rec + 7) == *(int*) (a1 + 0x16c) && *(unsigned char*) rec != 0 && *(int*) (rec + 0x17) == 0 && *(int*) (rec + 0x1f) != 0 &&
				    *(int*) (*(int*) (rec + 0x1f) + 0x2c) == *(int*) (*(int*) (rec + 7) + 1)) {
					*(int*) (msg + 0x38 + i * 4) = *(int*) (rec - 0x161);
					i++;
				}
				rec += 0x21c;
			} while (i < n);
		}
		if (i < 8) {
			for (n = i; n < 8; n++) {
				*(int*) (msg + 0x38 + n * 4) = -1;
			}
		}
		if (*(int*) (msg + 0x38) == -1) {
			return 1;
		}
		fcn_004c5530(msg);
		*(int*) (a1 + 0x1c0) = -1;
		return 1;
	}
	for (t = fcn_005463a0(2, 0, 0x40, 3, *(int*) (*(char**) (a1 + 0x16c) + 1)); t != 0; t = fcn_005462a0()) {
		if (*(int*) (t + 0xac) == *(int*) (cand + 1)) {
			goto log1;
		}
	}
	for (t = fcn_005463a0(2, 0, 0x3f, 3, *(int*) (*(char**) (a1 + 0x16c) + 1)); t != 0; t = fcn_005462a0()) {
		if (*(int*) (t + 0xac) == *(int*) (cand + 1)) {
			goto log1;
		}
	}
	for (t = fcn_005463a0(2, 0, 0x49, 3, *(int*) (*(char**) (a1 + 0x16c) + 1)); t != 0; t = fcn_005462a0()) {
		if (*(int*) (t + 0xac) == *(int*) (cand + 1)) {
			goto log1;
		}
	}
	sprintf(buf, "ai_CalcAngriff(): Meister %s spioniert bei '%s'", nm, cand + 5);
	memset(msg, 0, sizeof(msg));
	msg[4] = 0x40;
	*(int*) (msg + 8) = *(int*) (g_7f4ca4 + *(unsigned short*) (*(char**) (a1 + 0x16c) + 0x27) * 0x21c);
	*(int*) (msg + 0xc) = *(int*) (*(char**) (a1 + 0x16c) + 1);
	*(int*) (msg + 0x28) = *(int*) &g_7f4c00;
	*(int*) (msg + 0x2c) = g_7f4c00.b;
	*(int*) (msg + 0x30) = g_7f4c00.c;
	*(short*) (msg + 0x34) = g_7f4c00.d;
	msg[0x36] = 1;
	*(int*) (msg + 0x58) = *(int*) (cand + 1);
	*(int*) (msg + 0x5c) = *(int*) (*(char**) (a1 + 0x16c) + 1);
	n = a2;
	if (n >= 8) {
		n = 8;
	}
	i = 0;
	if (n > 0) {
		rec = g_7f4ca0 + 0x165;
		do {
			if ((int) rec >= 0x85a205) {
				break;
			}
			if (*(short*) (rec - 0x165) != -1 && *(int*) (rec + 7) == *(int*) (a1 + 0x16c) && *(unsigned char*) rec != 0 && *(int*) (rec + 0x17) == 0 && *(int*) (rec + 0x1f) != 0 &&
			    *(int*) (*(int*) (rec + 0x1f) + 0x2c) == *(int*) (*(int*) (rec + 7) + 1)) {
				*(int*) (msg + 0x38 + i * 4) = *(int*) (rec - 0x161);
				i++;
			}
			rec += 0x21c;
		} while (i < n);
	}
	if (i < 8) {
		for (n = i; n < 8; n++) {
			*(int*) (msg + 0x38 + n * 4) = -1;
		}
	}
	fcn_004c5530(msg);
	return 1;
		}
	}
log2:
	sprintf(buf, "ai_CalcAngriff(): Meister %s hat aber noch eine Spionage bei '%s' nicht beendet", nm, cand + 5);
	return 1;
log1:
	sprintf(buf, "ai_CalcAngriff(): Meister %s hat schon eine Spionage bei '%s' laufen", nm, cand + 5);
	return 1;
	return 0;
}
