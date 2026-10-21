#include <stdio.h>
#include <string.h>

#include "client_types.h"

typedef struct {
	unsigned short demand;
	unsigned short supply;
	char pad4[0x14];
} Cell99ef80;


extern char g_7f4ca0[];
extern char g_7f4ca4[];
extern char g_7f4ca2[];
extern pos14_7f4c00 g_7f4c00;
extern unsigned char* g_868050;
extern unsigned char* g_90e094;
extern char* g_773da8;
extern int g_7747b4;
extern int g_100b0a8;
extern int g_100b0ac;
extern int g_100dc20;
extern int g_100dc24;
extern int g_100dc34;

unsigned short __cdecl gm_RandomMod(int);
double __cdecl gm_RandomFloat01(void);
int __cdecl gm_AccumulateTyped2(char*);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_004fa6f0(int, int*, int*);
int __cdecl fcn_0050d2a0(char*);
int __cdecl gm_CheckEntityType(unsigned char*);
char* __cdecl gm_SetupEntityQuery(char*);
void __cdecl fcn_004c5530(char*);
void __cdecl fcn_00485650(char*, char*);
void __cdecl fcn_00486c40(char*, char*, int);
void __cdecl fcn_00489010(char*, char*);
void __cdecl fcn_00489250(char*);
void __cdecl fcn_00489a70(char*, char*);
void __cdecl fcn_00487000(char*);
void __cdecl fcn_00487970(char*, char*, int);
void __cdecl fcn_00487c00(char*, char*, int);
void __cdecl fcn_00487470(char*);
void __cdecl fcn_004888a0(char*);
void __cdecl fcn_00488c00(char*);
void __cdecl ai_CalcAngriff(char*, int);

/* ADDRESS: GOLDTL 0x004823c0 */
void __cdecl fcn_004823c0(char* e)
{
	char buf[0x400];
	char msg[0xf8];
	char* bld;
	char* res;
	char* p;
	char* cand;
	char* query;
	Cell99ef80* cell;
	float weight;
	int n;
	int r;
	float fmax;
	int a;
	float best;
	int b;
	float v;
	int cnt = 0;
	unsigned short action;
	unsigned char kind;
	int hits;
	int freehits;
	int half;
	int i;
	int j;
	int limit;
	int found;
	int idx;
	int scanned;
	float w;
	double rnd;

	res = fcn_00502cd0(*(int*) (*(char**) (e + 0x16c) + 0x5d), 2, 6, 0, 0x116);
	if (res != 0) {
		g_100b0ac = 0;
		g_100b0a8 = 0;
		fcn_00485650(e, res);
		fcn_00486c40(e, res, *(int*) (*(char**) (e + 0x16c) + 0x39));
		fcn_00489010(e, res);
		fcn_00489250(e);
		fcn_00489a70(e, res);
	}
	fcn_00487000(e);
	fcn_00487970(res, e, 10);
	fcn_00487c00(res, e, 10);
	fcn_00487470(e);
	fcn_004888a0(e);
	fcn_00488c00(e);
	if ((unsigned short) g_7f4c00.b > 6 && (*(unsigned int*) (e + 4) + (unsigned short) g_7f4c00.b) % 3 == 0) {
		if (*(int*) (e + 0x1b4) & 0x20) {
			return;
		}
		*(int*) (e + 0x1b4) |= 0x20;
		hits = 0;
		freehits = 0;
		for (p = g_7f4ca0; (int) p < 0x85a0a0; p += 0x21c) {
			if (*(unsigned char*) (p + 8) == 0) {
				continue;
			}
			if (*(unsigned short*) p == 0xffff) {
				continue;
			}
			if (*(unsigned char*) (p + 2) == 0x0a) {
				continue;
			}
			if (*(int*) (p + 0x16c) != *(int*) (e + 0x16c)) {
				continue;
			}
			if (*(unsigned char*) (p + 0x165) == 0) {
				continue;
			}
			if (*(int*) (p + 0x184) == 0) {
				continue;
			}
			if (*(int*) (*(int*) (p + 0x184) + 0x2c) != *(int*) (*(int*) (e + 0x16c) + 1)) {
				continue;
			}
			hits++;
			if (*(int*) (p + 0x17c) == 0) {
				freehits++;
			}
		}
		if (g_100dc20 == *(int*) (e + 0x16c)) {
			g_100dc34 = freehits;
			if (*(int*) (e + 0x1c0) != -1) {
				g_100dc24 = gm_AccumulateTyped2((char*) *(int*) (e + 0x1c0));
			}
		}
		half = hits >> 1;
		if (half >= hits - half) {
			half = hits - half;
		}
		if (freehits < half) {
			sprintf(buf, "ai_CalcMeisterR\xe4uber(): Meister %s hat gerade keine Leute...", e + 0x30);
			return;
		}
		bld = *(char**) (e + 0x16c);
		kind = *(unsigned char*) (g_7f4ca2 + *(unsigned short*) (bld + 0x27) * 0x21c);
		if (kind != 6 && kind != 7) {
			if (gm_RandomFloat01() > 0.85) {
				if (freehits >= 3 && *(int*) &g_7f4c00 >= 7 - g_7747b4) {
					goto attack;
				}
			}
			action = gm_RandomMod(4);
		} else {
			action = gm_RandomMod(2);
			if (action != 0 && *(int*) (e + 0x1c0) != -1 && gm_RandomMod(2) != 0) {
				goto send48;
			}
		}
		if (action == 3) {
attack:
			ai_CalcAngriff(e, freehits);
			goto send48;
		}
		if (action == 0) {
			if (gm_RandomFloat01() < 0.75) {
				goto send48;
			}
			sprintf(buf, "ai_CalcMeisterR\xe4uber(): Meister %s m\xf6" "chte Geld sch\xfctzen", e + 0x30);
			fmax = 0.0f;
			for (i = 0; i < 8; i++) {
				for (j = 0; j < 8; j++) {
					cell = (Cell99ef80*) ((char*) 0x99ef80 + (i + j * 8) * 0x18);
					v = (float) cell->demand * 0.125f + (float) cell->supply;
					if (fmax <= v) {
						fmax = v;
					}
				}
			}
			if (fmax == 0.0f) {
				fmax = 1.0f;
			}
			cand = 0;
			best = 0.0f;
			n = 0x100;
			for (p = (char*) g_90e094; n != 0; n--, p += 0xa9) {
				if (*(unsigned char*) p == 0) {
					continue;
				}
				bld = *(char**) (e + 0x16c);
				if (*(unsigned short*) (p + 0x27) == *(unsigned short*) (bld + 0x27)) {
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
				if (gm_CheckEntityType((unsigned char*) p) != 0) {
					continue;
				}
				if (((unsigned char*) g_868050)[*(unsigned char*) p + *(unsigned char*) p * 0x24c] == 0x21) {
					continue;
				}
				if (*(int*) (p + 0x61) != 0 && fcn_004fa6f0(*(int*) (p + 0x61) + 0x4c, &a, &b) != 0) {
					r = (b + a * 8) * 0x18;
					weight = 1.0f - ((float) (*(unsigned short*) ((char*) 0x99ef80 + r)) * 0.125f + (float) (*(unsigned short*) ((char*) 0x99ef80 + r + 2))) / fmax;
				} else {
					weight = 0.0f;
				}
				r = gm_RandomMod(100);
				w = (float) r * weight * 0.01;
				if (cand == 0) {
					best = w;
				} else {
					v = (float) fcn_0050d2a0(g_7f4ca0 + *(unsigned short*) (p + 0x27) * 0x21c) * w;
					if ((float) fcn_0050d2a0(g_7f4ca0 + *(unsigned short*) (cand + 0x27) * 0x21c) * best < v) {
						best = w;
					} else {
						continue;
					}
				}
				cand = p;
			}
			*(int*) (e + 0x1c0) = *(int*) (cand + 1);
			sprintf(buf, "ai_CalcMeisterR\xe4uber(): Meister %s sch\xfctzt Geld bei '%s'", e + 0x30, cand + 5);
			memset(msg, 0, sizeof(msg));
			msg[4] = 0x62;
			bld = *(char**) (e + 0x16c);
			idx = *(unsigned short*) (bld + 0x27);
			*(int*) (msg + 8) = *(int*) (g_7f4ca4 + idx * 0x21c);
			*(int*) (msg + 0xc) = *(int*) (bld + 1);
			*(int*) (msg + 0x28) = *(int*) &g_7f4c00;
			*(int*) (msg + 0x2c) = g_7f4c00.b;
			*(int*) (msg + 0x30) = g_7f4c00.c;
			*(short*) (msg + 0x34) = g_7f4c00.d;
			msg[0x36] = 2;
			*(int*) (msg + 0x58) = -1;
			*(int*) (msg + 0x5c) = *(int*) (cand + 1);
			*(int*) (msg + 0x68) = *(int*) (bld + 1);
			query = gm_SetupEntityQuery(bld);
			if (query == 0) {
				sprintf(buf, "ai_CalcMeisterWache() : gm_GetGebaeudeHauptraum() failed !!!");
				return;
			}
			*(int*) (msg + 0x6c) = *(int*) (query + 2);
			for (p = g_7f4ca0 + 0x165; (int) p < 0x85a205; p += 0x21c) {
				if (*(short*) (p - 0x165) != -1 && *(int*) (p + 7) == *(int*) (e + 0x16c) && *(unsigned char*) p != 0 && *(int*) (p + 0x17) == 0 && *(int*) (p + 0x1f) != 0 &&
				    *(int*) (*(int*) (p + 0x1f) + 0x2c) == *(int*) (*(int*) (p + 7) + 1)) {
					*(int*) (msg + 0x58) = *(int*) (p - 0x161);
					cnt++;
				}
				if (cnt != 0) {
					break;
				}
			}
			if (*(int*) (msg + 0x58) == -1) {
				return;
			}
			fcn_004c5530(msg);
			return;
		}
		if (action < 1) {
			return;
		}
send48:
		sprintf(buf, "ai_CalcMeisterR\xe4uber(): Meister %s m\xf6" "chte sich auf die Lauer legen", e + 0x30);
		memset(msg, 0, sizeof(msg));
		msg[4] = 0x48;
		bld = *(char**) (e + 0x16c);
		idx = *(unsigned short*) (bld + 0x27);
		*(int*) (msg + 8) = *(int*) (g_7f4ca4 + idx * 0x21c);
		*(int*) (msg + 0xc) = *(int*) (bld + 1);
		*(int*) (msg + 0x28) = *(int*) &g_7f4c00;
		*(int*) (msg + 0x2c) = g_7f4c00.b;
		*(int*) (msg + 0x30) = g_7f4c00.c;
		*(short*) (msg + 0x34) = g_7f4c00.d;
		msg[0x36] = 2;
		r = gm_RandomMod(8);
		strcpy(msg + 0x58, (char*) 0x6a4770 + r * 0x20);
		limit = freehits;
		if (limit >= 8) {
			limit = 8;
		}
		scanned = 0;
		found = 0;
		if (limit > 0) {
			p = g_7f4ca0 + 0x165;
			do {
				if (scanned >= 4) {
					break;
				}
				if ((int) p >= 0x85a205) {
					break;
				}
				if (*(short*) (p - 0x165) != -1 && *(int*) (p + 7) == *(int*) (e + 0x16c) && *(unsigned char*) p != 0 && *(int*) (p + 0x17) == 0 && *(int*) (p + 0x1f) != 0 &&
				    *(int*) (*(int*) (p + 0x1f) + 0x2c) == *(int*) (*(int*) (p + 7) + 1)) {
					*(int*) (msg + 0x38 + found * 4) = *(int*) (p - 0x161);
					found++;
					scanned++;
				}
				p += 0x21c;
			} while (scanned < limit);
		}
		if (found < 8) {
			for (i = found; i < 8; i++) {
				*(int*) (msg + 0x38 + i * 4) = -1;
			}
		}
		if (*(int*) (msg + 0x38) == -1) {
			return;
		}
		if (scanned < 2) {
			return;
		}
		fcn_004c5530(msg);
	} else {
		*(int*) (e + 0x1b4) &= ~0x20;
	}
}
