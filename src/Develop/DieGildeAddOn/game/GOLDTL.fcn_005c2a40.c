#include <string.h>

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char* g_entity_type_table;
extern char* g_item_def_table;
extern char* g_1015ea0;
extern char g_7f4ca0[];
extern char g_7f4ca4[];
extern int g_772514;
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_774654;
extern char g_6ac628[];
extern char g_6ac618[];

int __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl he_fn_Handlung(void);
unsigned short* __cdecl fcn_00502cd0(int, int, int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472830(int, int, int, int*, int*, int*);
void __cdecl fcn_00533f40(int, int, int, int);
float __cdecl eval_ObjektPreis2Credits(int, int);
int __cdecl fcn_0046f740(int, int, char*, int);
int __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_0046fac0(int, int, char*, int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00476b60(void);
char* __cdecl gm_SearchTable67(int);
int __cdecl fcn_00526120(int, int);
int __cdecl fcn_00526010(void*, int, int);
char* __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c5150(int, int, char, int);
void __cdecl fcn_004c4ef0(char*);
void __cdecl fcn_004c5530(char*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00500d20(char*, char*);
void __cdecl fcn_0046f940(int, int);

/* ADDRESS: GOLDTL 0x005c2a40 */
void __cdecl fcn_005c2a40(unsigned char* a0)
{
	int slots[96];
	int cbuf[16];
	char msg[0xf8];
	char* base;
	char* r;
	char* cur;
	unsigned short* p;
	int* ep;
	int nslots;
	int total;
	int others;
	int removed;
	int han;
	int cnt;
	int sel;
	int idx;
	int i;
	int k;
	int id;
	int handle;
	int val;
	float scale;
	float lo;
	float hi;

	ep = slots;
	for (i = 0x20; i != 0; i--) {
		ep[0] = 0;
		ep[1] = -1;
		ep[2] = -1;
		ep += 3;
	}
	total = 0;
	others = 0;
	removed = 0;
	if (fcn_005463a0(2, 0, 0x1f, 3, *(int*) (a0 + 1)) != 0) {
		do {
			total++;
		} while (he_fn_Handlung() != 0);
	}
	base = g_entity_type_table + (int) (*a0) * 0x24d;
	p = (unsigned short*) (base + 0x23);
	nslots = 0;
	for (i = 0; i < 0x40; i++) {
		if (nslots >= 0x20) {
			break;
		}
		if (*p != 0xffff) {
			id = *p & 0x7fff;
			k = *(char*) (g_item_def_table + id * 0x41);
			if ((k == 2 || k == 6) && id != 0xfd) {
				slots[nslots * 3] = id;
				nslots++;
			}
		}
		p++;
	}
	p = fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 5, 0);
	while (p != 0) {
		k = *(char*) (g_item_def_table + (int) (*p) * 0x41);
		if ((k == 2 || k == 6) && *p != 0xfd) {
			others++;
		}
		p = gm_NextEntityQueryMatch();
	}
	han = fcn_00470820(0, 0, g_6ac628);
	fcn_00471b60(han);
	d2_SetForm(han, 1);
	fcn_00519190(0x17ce);
	d2_SetForm(han, 0);
	cur = 0;
	if (nslots >= 5) {
		cnt = fcn_00472830(han, 2, 0x3c, &cbuf[1], &cbuf[0], &cbuf[2]);
		r = *(char**) 0x77255c;
		fcn_00533f40(*(int*) (r + 0x10) - 0x4c, *(int*) (r + 0xc) - 0x20,
		             g_772514, cnt);
		*(int*) (g_1015ea0 + 0x84 + cbuf[2] * 0x2f4) = 0x56;
	}
	d2_SetForm(han, 2);
	if (nslots >= 1) {
		k = nslots;
		cnt = 0;
		ep = slots;
		do {
			id = ep[0];
			scale = (float) ((double) *(int*) 0x7747b4 * *(double*) 0x662ad8 +
			                 *(double*) 0x662908);
			val = (int) (eval_ObjektPreis2Credits(id, 100) * scale);
			handle = fcn_0046f740(0x10, cnt, (char*) (id + 0xdf), g_772514);
			ep[1] = handle;
			r = g_1015ea0 + handle * 0x2f4;
			*(int*) (r + 0x5c) = 1;
			*(int*) (r + 0x1d0) = 3;
			*(int*) (r + 0x1e4) = 0x520;
			*(int*) (r + 0x1e8) = -2;
			*(int*) (r + 0x1ec) = -2;
			fcn_0051af00((char*) cbuf, 0x17d3,
			             *(int*) (id * 8 + 0x14a79c0), val);
			ep[2] = fcn_0046fac0(0x60, cnt + 10, (char*) cbuf, g_772514);
			cnt += 0x3c;
			ep += 3;
			k--;
		} while (k != 0);
	}
	fcn_00473a90(0, 0);
	fcn_00476b60();
	do {
		r = gm_SearchTable67(*(int*) (a0 + 1));
		if ((a0[0x5b] & 4) != 0 || r == 0) {
			g_774654 = 1;
		}
		if (g_14ce8e0 != 0 || g_100f1dc == 1) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1 && nslots >= 1) {
			ep = slots + 1;
			sel = 0;
			do {
				if (g_67d370 == *ep) {
					hi = eval_ObjektPreis2Credits(slots[sel * 3], 100);
					val = (int) hi;
					if ((int) (unsigned char) *(base + 0x21) <=
					    total + others) {
						fcn_00526120(*(int*) 0x14ab260, 0);
					} else if (fcn_00526010((void*) (g_7f4ca0 +
					                                 (int) g_774970 * 0x21c),
					                        val,
					                        (total + others) << 8 |
					                        g_773d75) != 0) {
						for (i = 0; i < 0x3e; i++) {
							cbuf[i] = 0;
						}
						cbuf[4] = 0x1f;
						*(int*) ((char*) cbuf + 8) =
						    *(int*) (g_7f4ca4 +
						             (int) g_774970 * 0x21c);
						*(int*) ((char*) cbuf + 0xc) = *(int*) (a0 + 1);
						*(int*) ((char*) cbuf + 0x28) = *(int*) &g_7f4c00;
						*(int*) ((char*) cbuf + 0x2c) = g_7f4c04;
						*(int*) ((char*) cbuf + 0x30) = g_7f4c08;
						*(short*) ((char*) cbuf + 0x34) = g_7f4c0c;
						*((char*) cbuf + 0x36) = 1;
						*(short*) ((char*) cbuf + 0x5c) =
						    (short) slots[sel * 3];
						*(int*) ((char*) cbuf + 0x58) = *(int*) (a0 + 1);
						fcn_004c5150(-1,
						             *(int*) (g_7f4ca4 +
						                     (int) g_774970 * 0x21c),
						             (char) g_773d75, val);
						fcn_004c5530((char*) cbuf);
						fcn_004c4ef0(g_6ac618);
					}
					break;
				}
				sel++;
				ep += 3;
			} while (sel < nslots);
		}
		total = 0;
		if (fcn_005463a0(2, 0, 0x1f, 3, *(int*) (a0 + 1)) != 0) {
			cur = 0;
			for (;;) {
				r = he_fn_Handlung();
				for (;;) {
					if (nslots <= 0) {
						break;
					}
					ep = slots;
					sel = 0;
					for (;;) {
						*(int*) (g_1015ea0 + ep[1] * 0x2f4 + 0x1f4) = 0;
						if ((unsigned short) *(short*) (r + 0xb0) ==
						    (unsigned short) ep[0]) {
							break;
						}
						sel++;
						ep += 3;
						if (sel >= nslots) {
							break;
						}
					}
					if (sel < nslots) {
						id = slots[sel * 3];
						handle = slots[sel * 3 + 1];
						*(int*) (g_1015ea0 + id * 0x2f4 + 0x5c) = 0;
						fcn_0046f940(handle, *(int*) 0x14ab264);
						lo = (float) fcn_00500d20(r + 0x44, r + 0x52);
						hi = (float) fcn_00500d20(r + 0x44,
						                          (char*) 0x7f4c00);
						*(float*) (g_1015ea0 + id * 0x2f4 + 0x1f4) =
						    hi / lo;
					}
					break;
				}
				total++;
				cur = he_fn_Handlung();
				if (cur == 0) {
					break;
				}
			}
		}
		removed = 0;
		if (nslots >= 1) {
			ep = slots;
			idx = nslots;
			do {
				if (fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 0, ep[0]) != 0) {
					*(int*) (g_1015ea0 + ep[1] * 0x2f4 + 0x5c) = 0;
					fcn_0046f940(ep[2], *(int*) 0x14ab268);
					removed++;
				}
				ep += 3;
				idx--;
			} while (idx != 0);
		}
		d2_SetForm(han, 3);
		fcn_00519190(0x17cf, a0,
		             (int) (unsigned char) *(cur + 0x21) - others - removed,
		             0x17d4);
	} while (fcn_005373e0((void*) 0x5c2a40, 0x657c7) != 0);
	fcn_00471e30(han);
}
