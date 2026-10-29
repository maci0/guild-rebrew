/*
 * Re-balances the goods stock of one town building: queries the producers,
 * sells or buys the missing goods through the trade packets and finally
 * reports the request to the server.
 */
#include <string.h>
#include <stdio.h>

typedef struct {
	int x0;
	int n;
	int x8[16];
	unsigned short x48[16];
	int x68[16];
	int xa8;
	int xac;
	int xb0;
	char* xb4;
} Stats; /* 0xb8 */

typedef struct {
	int f00;              /* +0x00 */
	unsigned char type;   /* +0x04 */
	unsigned char f05;
	unsigned char flag;   /* +0x06 */
	unsigned char f07;
	int state;            /* +0x08 */
	int f0c;              /* +0x0c */
	int f10;
	int f14;
	int f18;
	char pad1c[0x28 - 0x1c];
	int p28;
	int p2c;
	int p30;
	unsigned short p34;
	char pad36[0x58 - 0x36];
	int f58;
	char pad5c[0x04];
	int f60;
	int slots[6];         /* +0x64 */
	unsigned short ids[6];/* +0x7c */
	char pad88[0x9d - 0x88];
	unsigned char skip;   /* +0x9d */
	char pad9e[0xf8 - 0x9e];
} Msg; /* 0xf8 */

extern int lpObjektePROT;
extern unsigned char g_773d75;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;

int __cdecl fcn_0050cce0(char*, void*, int);
int __cdecl fcn_0050de80(char*, Stats*);
char* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl fcn_0050dfd0(char*, int);
float __cdecl fcn_0050bb50(int, unsigned char);
int __cdecl fcn_0047d1b0(void);
int __cdecl fcn_0047d1e0(void);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c5150(int, int, char, int);
int __cdecl fcn_004c4eb0(int);
int __cdecl fcn_004c4ef0(int);
int __cdecl fcn_004c51f0(int, int, short, int, char, int);
int __cdecl fcn_00500bb0(void*, int, int);
int __cdecl gm_QueryEntitySum(int, int);


/* ADDRESS: GOLDTL 0x0048cdb0 */
unsigned int __cdecl fcn_0048cdb0(char* o, char* req)
{
	Msg m;
	Stats st;
	char line[0x100];
	int totals[4];
	char* v2;
	char* e;
	char* g;
	char* q;
	int* p;
	int i;
	int j;
	int k;
	int n;
	int amt;
	int lim;
	int sum;
	int want;
	float price;

	if (*(float*) 0x100d0f4 < *(float*) 0x6628a8 || *(int*) 0x100d10c == 0)
		return 0;
	fcn_0050cce0(*(char**) (o + 0x16c), line, 0);
	for (i = 0; i < *(int*) 0x100e74c; i++) {
		v2 = (char*) *(int*) (0x100dbc0 + i * 4);
		if (*(unsigned char*) (v2 + 0x12) >= 0x21) {
			memset(&m, 0, sizeof(m));
			if (fcn_0047d1e0() > fcn_0047d1b0())
				m.skip = 1;
			for (k = 0; k < 3; k++) {
				m.ids[k] = 0;
				m.slots[k] = -1;
				m.ids[k + 3] = 0;
				m.slots[k + 3] = -1;
			}
			fcn_0050de80(v2, &st);
			q = fcn_00502cd0(*(int*) (v2 + 0x14), 1, 0, 0x1dd);
			n = 0;
			if (st.x0 > 0) {
				for (i = 0; i < st.x0; i++) {
					if (st.x48[i] == 0)
						continue;
					sprintf(line, (char*) 0x67e918, *(int*) (o + 0x16c) + 5, st.x68[i], st.x48[i] * 0x41 + 1 + lpObjektePROT);
					for (p = (int*) 0x100b0c0; p < (int*) 0x100d0c0; p += 0x10) {
						if (*p == (int) st.x48[i])
							break;
					}
					if (st.x68[i] == 0)
						continue;
					sprintf(line, (char*) 0x67e8c0, *(int*) (o + 0x16c) + 5, st.x68[i], st.x48[i] * 0x41 + 1 + lpObjektePROT);
					price = fcn_0050bb50((int) st.x48[i], g_773d75);
					sprintf(line, (char*) 0x67e358, -1, *(int*) (q + 2), (int) st.x48[i], st.x68[i], g_773d75, (double) (int) price);
					fcn_004c51f0(-1, *(int*) (q + 2), (short) st.x48[i], st.x68[i], (char) g_773d75, (int) fcn_0050bb50((int) st.x48[i], g_773d75));
					*(int*) (o + 0x1b8) = (int) fcn_0050bb50((int) st.x48[i], g_773d75);
					st.x48[i] = 0;
					st.x68[i] = 0;
				}
			}
			amt = fcn_0050dfd0(q, *(int*) 0x100d0c0);
			lim = *(int*) 0x100d10c;
			if (amt < lim)
				lim = amt;
			sprintf(line, (char*) 0x67e358, *(int*) (q + 2), *(int*) (req + 2), *(int*) 0x100d0c0, lim, g_773d75);
			if (*(int*) 0x100d10c <= amt)
				amt = *(int*) 0x100d10c;
			fcn_004c51f0(*(int*) (q + 2), *(int*) (req + 2), *(short*) 0x100d0c0, amt, (char) g_773d75, 0);
			m.ids[n] = *(unsigned short*) 0x100d0c0;
			n++;
			m.slots[n] = *(int*) (*(int*) 0x100d0d4 + 1);
			m.ids[0] = *(unsigned short*) 0x100d0c0;
			j = 1;
			while (j < *(int*) 0x100b0ac && n < 3) {
				e = (char*) (0x100d118 + j * 0x58);
				if (*(float*) (e + 0x34) <= *(float*) 0x6628a8)
					break;
				if (*(int*) (*(int*) (e + 0x14) + 1) != 0 && *(int*) (e + 0x4c) != 0) {
					lim = fcn_0050dfd0(q, *(int*) e);
					if (st.x0 > 0) {
						for (k = 0; k < st.x0; k++) {
							if (st.x48[k] != 0)
								continue;
							want = *(int*) (e + 0x4c);
							if (lim < want)
								want = lim;
							sprintf(line, (char*) 0x67e358, *(int*) (q + 2), *(int*) (req + 2), *(int*) e, want, g_773d75);
							want = *(int*) (e + 0x4c);
							if (lim < want)
								want = lim;
							fcn_004c51f0(*(int*) (q + 2), *(int*) (req + 2), *(short*) e, want, (char) g_773d75, 0);
							m.ids[n] = *(unsigned short*) e;
							n++;
							m.slots[n] = *(int*) (*(int*) (e + 0x14) + 1);
							st.x48[k] = *(unsigned short*) e;
							break;
						}
					}
				}
				j++;
			}
			memset(totals, 0, sizeof(totals));
			j = 0;
			while (j < *(int*) 0x100b0a8 && j < 3) {
				e = (char*) (0x100b0c0 + j * 0x40);
				if (*(float*) (e + 0x20) <= *(float*) 0x6628a8)
					break;
				g = (char*) *(int*) (e + 8);
				if (*(int*) (g + 1) != m.slots[1] || *(int*) (e + 0x34) == 0) {
					j++;
					continue;
				}
				if (g == 0) {
					j++;
					continue;
				}
				m.ids[j + 3] = *(unsigned short*) e;
				m.slots[j + 4] = *(int*) (g + 1);
				amt = fcn_0050dfd0(q, (int) m.ids[j + 3]);
				if (*(int*) (e + 0x34) <= amt)
					amt = *(int*) (e + 0x34);
				totals[j + 1] = amt;
				if (*g == 'G')
					totals[*(int*) (g + 0x65)] = (int) fcn_0050bb50((int) m.ids[j + 3], g_773d75);
				j++;
			}
			lim = m.slots[1];
			if (m.slots[1] == -1)
				lim = 0;
			m.type = 0x0b;
			m.state = *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c + 0x7f4ca4;
			m.f0c = *(int*) (*(int*) (o + 0x16c) + 1);
			m.p28 = g_7f4c00;
			m.p2c = g_7f4c04;
			m.p30 = g_7f4c08;
			m.p34 = g_7f4c0c;
			m.flag = 1;
			m.f58 = *(int*) (v2 + 2);
			m.slots[0] = *(int*) (o + 4);
			for (k = 1; k < 4; k++) {
				sum = gm_QueryEntitySum(*(int*) (0x7f4e18 + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c), 1);
				want = totals[k];
				if (want <= sum) {
					if (want * 2 < sum) {
						fcn_004c4eb0((int) (char*) 0x67e8b0);
						fcn_004c5150(*(int*) (0x7f4ca4 + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c), -1, (char) k, sum - (want * 9) / 8);
						fcn_004c5150(-1, *(int*) (0x7f4ca4 + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c), (char) k, (want * 9) / 8);
						fcn_004c4ef0((int) (char*) 0x67e8b0);
					}
				}
				else {
					fcn_004c4eb0((int) (char*) 0x67e8b0);
					fcn_004c5150(*(int*) (0x7f4ca4 + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c), -1, (char) k, (want * 9) / 8);
					fcn_004c5150(-1, *(int*) (0x7f4ca4 + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c), (char) k, want - (want * 9) / 8);
					fcn_004c4ef0((int) (char*) 0x67e8b0);
				}
			}
			if (*(int*) 0x100b0a4 == 0) {
				fcn_004c5530(&m);
				*(int*) 0x772620 = *(int*) 0x772620 + 1;
			}
		}
		else {
			memset(&m, 0, 0x28);
			m.type = 0x10;
			m.flag = 1;
			m.state = *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c + 0x7f4ca4;
			m.f0c = *(int*) (*(int*) (o + 0x16c) + 1);
			m.p28 = g_7f4c00;
			m.p2c = g_7f4c04;
			m.p30 = g_7f4c08;
			m.p34 = g_7f4c0c;
			fcn_00500bb0(&m.p28, 0, 0);
			m.f58 = *(int*) (v2 + 2);
			m.slots[0] = 5;
			m.ids[4] = 0;
			m.ids[5] = 0;
			m.f60 = 100 - (int) *(unsigned char*) (v2 + 0x12);
			fcn_004c5530(&m);
		}
	}
	return 1;
}
