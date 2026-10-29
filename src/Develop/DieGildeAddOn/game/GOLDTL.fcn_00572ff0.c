#include <string.h>

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern unsigned char g_773d75;
extern char* g_773da8;
extern char* lpGebaeudePROT;
extern char* lpObjektePROT;
extern double g_664108;
extern double g_664128;
extern double g_664ef8;

char* __cdecl fcn_00502cd0(int, int, ...);
int __cdecl gm_ResolveEntityById(void**, void**, void**, int);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
int __cdecl fcn_004c5530(char*);
void __cdecl fcn_00500bb0(char*, int, int, int);
void __cdecl fcn_00546190(char*);
char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl fcn_005ba020(char*, char*);
char* __cdecl fcn_00503d10(int);
float __cdecl fcn_0050bb50(int, unsigned char);
int __cdecl fcn_0050d320(char*, unsigned char);
int __cdecl gm_GetMsgField(char*, char*);
int __cdecl fcn_0050dfd0(char*, int);
int __cdecl gm_eval_SlotVoll(char*, int, int);
void __cdecl fcn_00549330(char*, int);
int __cdecl sprintf(char*, const char*, ...);

/* ADDRESS: GOLDTL 0x00572ff0 */
void __cdecl fcn_00572ff0(char* a)
{
	char msg[0xf8];
	char buf[0x70];
	char* pktA = 0;
	char* pktB = 0;
	char* itm = 0;
	char* ent;
	char* q;
	char* e2;
	char* r;
	char* r2;
	char* tmp;
	short* ps;
	int* pi;
	int n = 0;
	int i;
	int found;
	int cnt;
	int t;
	int m;
	int d;
	int left = 0;
	int amt = 0;
	int flag = 0;
	int k;
	int lim;
	int cand;

	if (*(int*) (a + 0x70) == -2) {
		*(int*) (a + 0x70) = 0;
		fcn_00549330(a, *(unsigned short*) g_773da8);
	}
	k = *(int*) (a + 0xe8);
	if (k != -1) {
		if (!fcn_004c4450(k)) {
			fcn_00500bb0(a + 0x52, 0, 1, 0);
			return;
		}
		*(int*) (a + 0xe8) = -1;
	}
	k = *(int*) (a + 0xec);
	if (k != -1) {
		if (!fcn_004c4450(k)) {
			fcn_00500bb0(a + 0x52, 0, 1, 0);
			return;
		}
		*(int*) (a + 0xec) = -1;
	}
	gm_ResolveEntityById(0, (void**) &pktA, 0, *(int*) (a + 0xac));
	gm_ResolveEntityById((void**) &pktB, 0, 0, *(int*) (a + 0xb0));
	gm_ResolveEntityById(0, 0, (void**) &itm, *(int*) (a + 0xb4));
	if (pktA == 0 || pktB == 0) {
		fcn_00546190(a);
		return;
	}
	ent = fcn_005463a0(2, 0, 0xf, 2, *(unsigned short*) (a + 8));
	while (ent != 0) {
		if (*(int*) (ent + 0xac) == *(int*) (a + 0xac)) {
			if (*(int*) (ent + 0xb4) != *(int*) (a + 0xb0)) {
				fcn_00546190(a);
				return;
			}
			fcn_00500bb0(a + 0x52, 0, 5, 0);
			return;
		}
		ent = gm_NextEntityQueryMatch();
	}
	if (*(char*) (a + 0xf1) == 0 && fcn_005ba020(pktB, pktA) == 0) {
		fcn_005ba020(pktB, pktA);
		fcn_00546190(a);
		return;
	}
	q = fcn_00502cd0(*(int*) (pktA + 0x14), 1, 0, 0x1dd);
	n = *(unsigned char*) (q + 0x1c);
	if (n >= 3) {
		n = 3;
	}
	found = 0;
	i = 0;
	ps = (short*) (a + 0xd6);
	while (i < n) {
		if (ps[-3] != 0 || ps[0] != 0) {
			found = 1;
		}
		i++;
		ps++;
		if (found) {
			break;
		}
	}
	if (!found) {
		e2 = fcn_00502cd0(*(int*) (pktA + 0x5d), 2, 6, 0, 0x2a);
		if (e2 == 0) {
			e2 = fcn_00502cd0(*(int*) (pktA + 0x5d), 2, 6, 0, 0x116);
		}
		if (e2 != 0) {
			r = fcn_00502cd0(*(int*) (q + 0x14), 1, 5);
			while (r != 0) {
				*(int*) (a + 0xe8) = fcn_004c51f0(*(int*) (e2 + 2),
				    *(int*) (q + 2), *(int*) r, *(int*) (r + 0xe),
				    g_773d75, 0);
				r = gm_NextEntityQueryMatch();
			}
		}
		if (*(int*) (a + 0xe8) != -1) {
			fcn_00500bb0(a + 0x52, 0, 5, 0);
			return;
		}
		fcn_00546190(a);
		return;
	}
	found = 0;
	i = 0;
	ps = (short*) (a + 0xd0);
	while (i < n) {
		if (ps[0] != 0) {
			found = 1;
		}
		i++;
		ps++;
		if (found) {
			break;
		}
	}
	if (!found) {
		if (itm != 0 && *(int*) (itm + 0x16c) != 0) {
			left = fcn_0050d320((char*) 0x7f4ca0
			    + *(unsigned short*) (*(int*) (itm + 0x16c) + 0x27) * 0x21c,
			    g_773d75);
			if (left >= *(int*) (itm + 0x1b8)) {
				left = *(int*) (itm + 0x1b8);
			}
		}
		if (n <= 0) {
			goto done;
		}
		pi = (int*) (a + 0xc4);
		ps = (short*) (a + 0xd6);
		cnt = n;
		do {
			if (ps[0] == 0 || pi[0] != *(int*) (pktB + 1)) {
				goto i2next;
			}
			if (lpGebaeudePROT[*(unsigned char*) pktB * 0x24d] == '\n') {
				e2 = fcn_00503d10(ps[0]);
			} else {
				e2 = fcn_00502cd0(*(int*) (pktB + 0x5d), 2, 6, 0, 0x2a);
				if (e2 == 0) {
					e2 = fcn_00502cd0(*(int*) (pktB + 0x5d), 2, 6,
					    0, 0x116);
				}
			}
			if (e2 == 0) {
				goto i2next;
			}
			r2 = fcn_00502cd0(*(int*) (e2 + 0x14), 1, 0, ps[0]);
			if (r2 == 0) {
				goto i2next;
			}
			if (lpGebaeudePROT[*(unsigned char*) pktB * 0x24d] != '\n') {
				amt = (int) (fcn_0050bb50(*(int*) r2, g_773d75)
				    * *(float*) (pktB + 0x49));
			} else {
				amt = (int) (fcn_0050bb50(*(int*) r2, g_773d75)
				    * g_664ef8);
			}
			lim = pi[6];
			cand = gm_GetMsgField(e2, r2)
			    - ((fcn_0050dfd0(e2, *(int*) r2) * *(int*) (r2 + 0x1c)) >> 2);
			if (cand <= lim) {
				lim = cand;
			}
			m = lim;
			if (left / amt <= m) {
				m = left / amt;
			}
			if (m < 0) {
				m = 0;
			}
			if (m != 0) {
				*(int*) (a + 0xe8) = fcn_004c51f0(*(int*) (e2 + 2),
				    *(int*) (q + 2), *(int*) r2, m, g_773d75, d);
			}
			if (itm != 0 && *(int*) (itm + 0x16c) != 0) {
				sprintf(buf, (char*) 0x6a7d00, itm + 0x30,
				    *(int*) (itm + 0x16c) + 5, amt * m, left, m,
				    (int) (lpObjektePROT + *(unsigned short*) r2 * 0x41 + 1));
			}
			left -= amt * m;
			if (itm != 0) {
				*(int*) (itm + 0x1b8) = *(int*) (itm + 0x1b8) - amt * m;
			}
i2next:
			if (m != 0 || *(char*) (a + 0xf0) == 0) {
				ps[0] = 0;
				pi[0] = -1;
			} else {
				flag |= 1;
			}
			ps++;
			pi++;
		} while (--cnt != 0);
		goto done;
	}
	pi = (int*) (a + 0xb8);
	ps = (short*) (a + 0xd0);
	cnt = n;
	do {
		if (ps[0] == 0 || pi[0] != *(int*) (pktB + 1)) {
			goto i1next;
		}
		if (lpGebaeudePROT[*(unsigned char*) pktB * 0x24d] == '\n') {
			e2 = fcn_00503d10(ps[0]);
		} else {
			e2 = fcn_00502cd0(*(int*) (pktB + 0x5d), 2, 6, 0, 0x2a);
			if (e2 == 0) {
				e2 = fcn_00502cd0(*(int*) (pktB + 0x5d), 2, 6, 0, 0x116);
			}
		}
		if (e2 == 0) {
			goto i1next;
		}
		r2 = fcn_00502cd0(*(int*) (e2 + 0x14), 1, 0, ps[0]);
		if (r2 == 0) {
			goto i1next;
		}
		t = gm_GetMsgField(q, r2);
		m = gm_eval_SlotVoll(e2, *(int*) r2, t);
		d = (int) (fcn_0050bb50(*(int*) r2, g_773d75) * g_664128);
		if (t < m) {
			m = t;
		}
		*(int*) (a + 0xe8) = fcn_004c51f0(*(int*) (e2 + 2), *(int*) (q + 2),
		    *(int*) r2, m, g_773d75, d);
		if (itm != 0) {
			*(int*) (itm + 0x1b8) = *(int*) (itm + 0x1b8) + d * m;
		}
		if (t - m != 0) {
			d = (int) (fcn_0050bb50(*(int*) r2, g_773d75) * g_664108);
			*(int*) (a + 0xe8) = fcn_004c51f0(-1, *(int*) (q + 2),
			    *(int*) r2, t - m, g_773d75, d);
		}
i1next:
		ps[0] = 0;
		pi[0] = -1;
		ps++;
		pi++;
	} while (--cnt != 0);
done:
	if (*(char*) (a + 0xf0) != 0 && flag != 0) {
		if (*(unsigned short*) 0x7f4c04 >= 0x14) {
			fcn_00500bb0(a + 0x52, 0, 5, 0);
			*(char*) (a + 0xf0) = 0;
			return;
		}
		fcn_00500bb0(a + 0x52, 0, 0x1e, 0);
		*(char*) (a + 0xf0) = (char) (*(char*) (a + 0xf0) - 1);
		return;
	}
	*(int*) (a + 0xb0) = -1;
	i = 0;
	pi = (int*) (a + 0xb8);
	ps = (short*) (a + 0xd0);
	while (i < n) {
		if (ps[0] != 0) {
			*(int*) (a + 0xb0) = pi[0];
		}
		i++;
		ps++;
		pi++;
		if (*(int*) (a + 0xb0) != -1) {
			break;
		}
	}
	if (*(int*) (a + 0xb0) == -1) {
		i = 0;
		pi = (int*) (a + 0xc4);
		ps = (short*) (a + 0xd6);
		while (i < n) {
			if (ps[0] != 0) {
				*(int*) (a + 0xb0) = pi[0];
			}
			i++;
			ps++;
			pi++;
			if (*(int*) (a + 0xb0) != -1) {
				break;
			}
		}
		if (*(int*) (a + 0xb0) == -1) {
			tmp = 0;
			gm_ResolveEntityById(0, (void**) &tmp, 0, *(int*) (a + 0x10));
			*(int*) (a + 0xb0) = *(int*) (tmp + 1);
		}
	}
	if (*(char*) (a + 0xf1) != 0) {
		fcn_00500bb0(a + 0x52, 1, 0x1e, 0);
		return;
	}
	memset(msg, 0, sizeof(msg));
	*(int*) (msg + 0x28) = *(int*) &g_7f4c00;
	*(int*) (msg + 0x2c) = *(int*) 0x7f4c04;
	*(int*) (msg + 0x30) = *(int*) 0x7f4c08;
	*(short*) (msg + 0x34) = *(short*) 0x7f4c0c;
	msg[4] = 0x0f;
	*(int*) (msg + 0xc) = -1;
	msg[0x36] = 2;
	*(int*) (msg + 8) = *(int*) ((char*) 0x7f4ca4 + *(unsigned short*) (a + 8) * 0x21c);
	*(int*) (msg + 0x58) = *(int*) (pktA + 2);
	*(int*) (msg + 0x5c) = *(int*) (pktB + 1);
	*(int*) (msg + 0x60) = *(int*) (a + 0xb0);
	*(int*) (msg + 0xa0) = *(int*) (a + 4);
	if (*(int*) (msg + 0x5c) != *(int*) (msg + 0x60)) {
		*(int*) (a + 0xec) = fcn_004c5530(msg);
		fcn_00500bb0(a + 0x52, 0, 10, 0);
		return;
	}
	fcn_00500bb0(a + 0x52, 0, 5, 0);
}
