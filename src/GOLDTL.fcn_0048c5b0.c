/*
 * Reports the goods stock of one town building to the server: collects the
 * producers, sums the segment stock and sends the message packet.
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
	unsigned char flag2;  /* +0x36 */
	char pad37[0x58 - 0x37];
	int f58;
	int f5c;
	int f60;              /* +0x60 */
	int slots[6];         /* +0x64 */
	unsigned short ids[6];/* +0x7c */
	int f88[4];           /* +0x88 */
	char pad98[0x9d - 0x98];
	unsigned char skip;   /* +0x9d */
	char pad9e[0xf8 - 0x9e];
} Msg; /* 0xf8 */

extern int g_99ec10;
extern unsigned char g_773d75;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;
extern int g_772620;

int __cdecl fcn_0050cce0(char*, void*, int);
int __cdecl fcn_0050de80(char*, Stats*);
char* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl fcn_0050dfd0(char*, int);
float __cdecl fcn_0050bb50(int, unsigned char);
int __cdecl fcn_0047d1b0(void);
int __cdecl fcn_0047d1e0(void);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c5150(int, int, char, int);
int __cdecl fcn_004c4eb0(char*);
int __cdecl fcn_004c4ef0(char*);
int __cdecl fcn_004c51f0(int, int, short, int, char, int);
int __cdecl fcn_00500bb0(void*, int, int, int);
int __cdecl fcn_0050b7c0(int, int);

/* ADDRESS: GOLDTL 0x0048c5b0 */
int __cdecl fcn_0048c5b0(char* o, char* req)
{
	int i;
	int n;
	int k;
	char* q;
	int tmp;
	int i2;
	char* ent;
	int sums[4];
	Msg m;
	Stats st;
	Stats st2;
	char line[0x400];

	n = 0;
	k = 0;
	if (*(float*) 0x100b0e0 <= *(float*) 0x6628a8 || *(int*) 0x100b0f4 == 0) {
		return 0;
	}
	fcn_0050cce0(*(char**) (o + 0x16c), &st2, 0);
	if (*(int*) 0x100e74c <= 0) {
		return 1;
	}
	for (i2 = 0; i2 < *(int*) 0x100e74c; i2++) {
		if (k > 3) {
			__asm { int 3 }
		}
		ent = (char*) *(int*) (0x100dbc0 + i2 * 4);
		memset(&m, 0, 0xf8);
		if (*(unsigned char*) (ent + 0x12) < 0x21) {
			m.type = 0x10;
			m.state = *(int*) (0x7f4ca4
			    + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c);
			m.f0c = *(int*) (*(int*) (o + 0x16c) + 1);
			m.p28 = g_7f4c00;
			m.p2c = g_7f4c04;
			m.p30 = g_7f4c08;
			m.p34 = g_7f4c0c;
			m.flag = 1;
			fcn_00500bb0(&m.p28, 0, 0, 10);
			m.f58 = *(int*) (ent + 2);
			m.slots[0] = 5;
			m.ids[4] = 0;
			m.ids[5] = 0;
			m.f5c = 100 - (int) *(unsigned char*) (ent + 0x12);
			fcn_004c5530(&m);
			continue;
		}
		memset(&m, 0, 0xf8);
		if (fcn_0047d1e0() > fcn_0047d1b0()) {
			m.skip = 1;
		}
		for (i = 0; i < 3; i++) {
			m.ids[i] = 0;
			m.slots[i] = -1;
			m.ids[i + 3] = 0;
			m.slots[i + 3] = -1;
		}
		fcn_0050de80(ent, &st);
		q = fcn_00502cd0(*(int*) (ent + 0x14), 1, 0, 0x1dd);
		i = 0;
		if (st.x0 > 0) {
			for (; i < st.x0; i++) {
				if (st.x48[i] == 0) {
					continue;
				}
				sprintf(line, (char*) 0x67e918, *(int*) (o + 0x16c) + 5,
				    st.x68[i], st.x48[i] * 0x41 + 1 + g_99ec10);
				for (tmp = 0x100b0c0; tmp < 0x100d0c0; tmp += 0x40) {
					if (*(int*) tmp == (int) st.x48[i]) {
						break;
					}
				}
				if (st.x68[i] == 0) {
					continue;
				}
				sprintf(line, (char*) 0x67e8c0, *(int*) (o + 0x16c) + 5,
				    st.x68[i], st.x48[i] * 0x41 + 1 + g_99ec10);
				tmp = (int) fcn_0050bb50((int) st.x48[i], g_773d75);
				sprintf(line, (char*) 0x67e358, -1, *(int*) (q + 2),
				    (int) st.x48[i], st.x68[i], g_773d75, (double) tmp);
				fcn_004c51f0(-1, *(int*) (q + 2), (short) st.x48[i],
				    st.x68[i], (char) g_773d75,
				    (int) fcn_0050bb50((int) st.x48[i], g_773d75));
				*(int*) (o + 0x1b8) = (int) (fcn_0050bb50((int) st.x48[i],
				    g_773d75) + *(int*) (o + 0x1b8));
				st.x48[i] = 0;
				st.x68[i] = 0;
			}
		}
		sums[0] = 0;
		sums[1] = 0;
		sums[2] = 0;
		sums[3] = 0;
		n = 0;
		i = 0;
		if (*(int*) 0x100b0c0 != 0) {
			tmp = fcn_0050dfd0(q, *(unsigned short*) 0x100b0c0);
			m.ids[3] = *(unsigned short*) 0x100b0c0;
			m.slots[3] = *(int*) (*(int*) 0x100b0c8 + 1);
			if (tmp > *(int*) 0x100b0f4) {
				tmp = *(int*) 0x100b0f4;
			}
			m.f88[0] = tmp;
			n = 1;
			i = 1;
		}
		for (; i < *(int*) 0x100b0a8; i++) {
			if (*(float*) (0x100b0c0 + i * 0x40 + 0x20) > *(float*) 0x6628a8) {
				break;
			}
			if (*(int*) (*(int*) (0x100b0c0 + i * 0x40 + 8) + 1) != m.slots[3]) {
				continue;
			}
			if (*(int*) (0x100b0c0 + i * 0x40 + 0x34) == 0) {
				continue;
			}
			if (*(int*) (0x100b0c0 + i * 0x40 + 8) == 0) {
				continue;
			}
			m.ids[n + 3] = *(unsigned short*) (0x100b0c0 + i * 0x40);
			m.slots[n + 4] = *(int*) (*(int*) (0x100b0c0 + i * 0x40 + 8) + 1);
			tmp = fcn_0050dfd0(q, (int) m.ids[n + 3]);
			if (tmp > *(int*) (0x100b0c0 + i * 0x40 + 0x34)) {
				tmp = *(int*) (0x100b0c0 + i * 0x40 + 0x34);
			}
			m.f88[n] = tmp;
			n++;
			if (*(char*) *(int*) (0x100b0c0 + i * 0x40 + 8) == 'G') {
				sums[*(int*) (*(int*) (0x100b0c0 + i * 0x40 + 8) + 0x65)]
				    = (int) ((float) tmp * *(float*) (0x100b0c0 + i * 0x40 + 0x1c)
				    + sums[*(int*) (*(int*) (0x100b0c0 + i * 0x40 + 8) + 0x65)]);
			}
		}
		{
			for (n = 1; n < 4; n++) {
				tmp = fcn_0050b7c0(*(int*) (0x7f4e18
				    + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c), n);
				if (sums[n] > tmp) {
					i = sums[n] * 9 / 8;
					fcn_004c4eb0((char*) 0x67e8b0);
					fcn_004c5150(*(int*) (0x7f4ca4
					    + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c),
					    -1, (char) n, i);
					fcn_004c5150(-1, *(int*) (0x7f4ca4
					    + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c),
					    (char) g_773d75, (int) ((double) i * *(double*) 0x664110));
					fcn_004c4ef0((char*) 0x67e8b0);
				} else if (sums[n] * 2 < tmp) {
					i = tmp - sums[n] * 9 / 8;
					fcn_004c4eb0((char*) 0x67e8b0);
					fcn_004c5150(*(int*) (0x7f4ca4
					    + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c),
					    -1, (char) g_773d75, i);
					fcn_004c5150(-1, *(int*) (0x7f4ca4
					    + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c),
					    (char) n, (int) ((double) i * *(double*) 0x664110));
					fcn_004c4ef0((char*) 0x67e8b0);
				}
			}
		}
		i = 0;
		if (k < 3) {
			for (; i < *(int*) 0x100b0ac; i++) {
				if (*(float*) (0x100d0c0 + i * 0x58 + 0x34) > *(float*) 0x6628a8) {
					break;
				}
				if (*(int*) (*(int*) (0x100d0c0 + i * 0x58 + 0x14) + 1) != m.slots[3]) {
					continue;
				}
				if (*(int*) (0x100d0c0 + i * 0x58 + 0x4c) == 0) {
					continue;
				}
				tmp = fcn_0050dfd0(q, *(int*) (0x100d0c0 + i * 0x58));
				k = 0;
				if (st.x0 <= 0) {
					continue;
				}
				for (; k < st.x0; k++) {
					if (st.x48[k] != 0) {
						continue;
					}
					sprintf(line, (char*) 0x67e358, *(int*) (q + 2),
					    *(int*) (req + 2), *(int*) (0x100d0c0 + i * 0x58),
					    *(int*) (0x100d0c0 + i * 0x58 + 0x4c) > tmp
					    ? tmp : *(int*) (0x100d0c0 + i * 0x58 + 0x4c),
					    g_773d75, 0);
					fcn_004c51f0(*(int*) (q + 2), *(int*) (req + 2),
					    *(short*) (0x100d0c0 + i * 0x58),
					    *(int*) (0x100d0c0 + i * 0x58 + 0x4c) > tmp
					    ? tmp : *(int*) (0x100d0c0 + i * 0x58 + 0x4c),
					    (char) g_773d75, 0);
					m.ids[n] = *(unsigned short*) (0x100d0c0 + i * 0x58);
					m.slots[n] = *(int*) (*(int*) (0x100d0c0 + i * 0x58 + 0x14) + 1);
					n++;
					st.x48[k] = *(unsigned short*) (0x100d0c0 + i * 0x58);
				}
			}
			k = n;
		}
		tmp = m.slots[0];
		if (tmp == -1) {
			tmp = m.slots[3];
		}
		m.type = 0x0b;
		m.state = *(int*) (0x7f4ca4
		    + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c);
		m.f0c = *(int*) (*(int*) (o + 0x16c) + 1);
		m.p28 = g_7f4c00;
		m.p2c = g_7f4c04;
		m.p30 = g_7f4c08;
		m.p34 = g_7f4c0c;
		m.flag = 1;
		m.f58 = *(int*) (ent + 2);
		m.f5c = tmp;
		m.f60 = *(int*) (o + 4);
		if (*(int*) 0x100b0a4 == 0) {
			fcn_004c5530(&m);
			g_772620++;
		}
	}
	return 1;
}
