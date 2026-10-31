#include <string.h>

extern int g_774970;
extern int g_774968;
extern int g_774978;
extern int g_774654;
extern int g_7e2700;
extern int g_7e46ac;
extern int g_6a3420;
extern int g_6b8014;
extern int g_772514;
extern int g_77250c;
extern int g_77255c;
extern int g_1040480;
extern int g_1040484;
extern int g_1040488;
extern int g_104048c;
extern int g_1040490;
extern int g_1040494;
extern int g_100f1dc;
extern char g_14cf950;
extern char g_7f4c00[];
extern char g_7f4ca0[];

int __cdecl io_AppendText(int, ...);
char* __cdecl fcn_004730c0(int, int, int, int, char*, int, int);
void __cdecl fcn_00473150(unsigned char*);
int __cdecl fcn_005373e0(int, int);
int __cdecl fcn_00509570(int);
void __cdecl fcn_00438b40(char*, int*);
void __cdecl fcn_00438cb0(char*, int*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_005272e0(void);
void __cdecl fcn_00537320(int);
int __cdecl fcn_00535570(void);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_00500d60(void*, void*);
int __cdecl fcn_00503fe0(int, int);
int __cdecl fcn_00503e80(void);
int __cdecl fcn_00504bd0(int);
int __cdecl fcn_0050c1b0(char*, int, int*);
int __cdecl fcn_0050d640(int, int, int, int*);
int __cdecl fcn_0050d5d0(int, char*, int*);
int __cdecl fcn_0050d2a0(int);
int __cdecl fcn_004fcda0(unsigned short, int, int*);
int __cdecl fcn_004fcb50(unsigned short, int*, int);
int __cdecl fcn_0064d228(void);
void __cdecl fcn_005459a0(int);
void __cdecl fcn_00476970(int);
void __cdecl fcn_00469e30(int);
void __cdecl fcn_0046e830(int, int, int, int, int);
void __cdecl fcn_004234e0(char*, char*, int, int, int, int, int);
void __cdecl fcn_00535630(void);
void __cdecl fcn_005355f0(void);
int __cdecl fcn_0050db40(char*, int);
void __cdecl fcn_004e5a00(void*);
void __cdecl fcn_005413d0(int);


/* Black editor panel for the current 0x7f4ca0 entity: prints the building
 * and unit counters, then runs the modal 0x24087 message loop. */
/* ADDRESS: GOLDTL 0x00541620 */
void __cdecl fcn_00541620(void)
{
	unsigned char panel[0x114];
	int vals2[6];
	int vals[6];
	char names[6];
	int info[0x15];
	int v1d0[10];
	int stamp[10];
	unsigned char* win;
	char* ent;
	unsigned short id;
	unsigned char b;
	int a7;
	int b200;
	int c1fc;
	int d1f8;
	int e1ec;
	int f1e8;
	int g1f4;
	int h1f0;
	int n;
	int i;
	int k;
	int sel;
	int kind;

	b200 = 0;
	e1ec = 0;
	f1e8 = 0;
	g1f4 = 0;
	a7 = 0;
	*(int*) (char*) &g_7e2700 = 0;
	if (g_6a3420 != 0) {
		win = (unsigned char*) fcn_004730c0(0, 0, g_1040494, g_1040490, "BLACK", 0x1e, 1);
		while ((*win & 4) == 0) {
			fcn_005373e0(0, g_7e46ac);
		}
		g1f4 = (int) win;
	}
	id = (unsigned short) g_774970;
	sel = (int) fcn_00509570((id & 0xffff) * 0x21c + (int) (char*) g_7f4ca0);
	k = (id & 0xffff) * 0x21c;
	*(int*) (sel + 0x3c) += *(int*) (k + 0x7f4e44) + *(int*) (k + 0x7f4e40);
	fcn_00438b40((char*) g_6b8014, (int*) (sel + 0x8c));
	fcn_00438cb0((char*) g_6b8014, (int*) (sel + 0x9c));
	if (g_6a3420 == 0) {
		goto fold;
	}
	d1f8 = 0;
	d2_SetOverlayAnimation(0, 0);
	fcn_005272e0();
	fcn_00537320(0x24087);
	i = fcn_00535570();
	fcn_00471b60(i);
	if (g1f4 != 0) {
		fcn_00473150((unsigned char*) g1f4);
		g1f4 = 0;
	}
	fcn_004730c0(0, 0, g_1040494, g_1040490, "BLACK", 0x1e, 10);
	d2_SetForm(i, 2);
	io_AppendText(0x7d);
	fcn_00500d60((void*) (char*) g_7f4c00, stamp);
	d2_SetForm(i, 1);
	io_AppendText(0x2007);
	k = (id & 0xffff) * 0x21c;
	a7 = *(int*) (k + 0x7f4e3c);
	c1fc = a7 - *(int*) (k + 0x7f4e38);
	if (a7 != 0) {
		io_AppendText(0x2008, a7);
	}
	a7 = *(int*) ((id & 0xffff) * 0x21c + 0x7f4e38);
	if (a7 != 0) {
		io_AppendText(0x2009, a7);
	}
	a7 = c1fc;
	if (*(int*) (sel + 0x40) != 0) {
		io_AppendText(0x2014, *(int*) (sel + 0x40));
		b200 = *(int*) (sel + 0x40);
		a7 = c1fc - b200;
	}
	if (*(int*) (sel + 0x44) != 0) {
		io_AppendText(0x2016, *(int*) (sel + 0x44));
		a7 -= *(int*) (sel + 0x44);
		b200 += *(int*) (sel + 0x44);
	}
	if (*(int*) (sel + 0x48) != 0) {
		io_AppendText(0x201b, *(int*) (sel + 0x48));
		a7 -= *(int*) (sel + 0x48);
		b200 += *(int*) (sel + 0x48);
	}
	if (*(int*) (sel + 0x4c) != 0) {
		io_AppendText(0x201a, *(int*) (sel + 0x4c));
		a7 -= *(int*) (sel + 0x4c);
		b200 += *(int*) (sel + 0x4c);
	}
	if (*(int*) (sel + 0x54) != 0) {
		io_AppendText(0x2015, *(int*) (sel + 0x54));
		a7 -= *(int*) (sel + 0x54);
		b200 += *(int*) (sel + 0x54);
	}
	if (*(int*) (sel + 0x28) != 0) {
		io_AppendText(0x201c, *(int*) (sel + 0x28));
		a7 -= *(int*) (sel + 0x28);
		b200 += *(int*) (sel + 0x28);
	}
	if (*(int*) (sel + 0x14) != 0) {
		io_AppendText(0x200d, *(int*) (sel + 0x14));
		a7 += *(int*) (sel + 0x14);
		c1fc += *(int*) (sel + 0x14);
	}
	if (*(int*) (sel + 0x18) != 0) {
		io_AppendText(0x200c, *(int*) (sel + 0x18));
		a7 += *(int*) (sel + 0x18);
		c1fc += *(int*) (sel + 0x18);
	}
	if (*(int*) (sel + 0x1c) != 0) {
		io_AppendText(0x200b, *(int*) (sel + 0x1c));
		a7 += *(int*) (sel + 0x1c);
		c1fc += *(int*) (sel + 0x1c);
	}
	if (*(int*) (sel + 0x20) != 0) {
		io_AppendText(0x2010, *(int*) (sel + 0x20));
		a7 += *(int*) (sel + 0x20);
		c1fc += *(int*) (sel + 0x20);
	}
	if (*(int*) (sel + 0x50) != 0) {
		io_AppendText(0x201d, *(int*) (sel + 0x50));
		a7 -= *(int*) (sel + 0x50);
		b200 += *(int*) (sel + 0x50);
	}
	if (a7 == 0) {
		io_AppendText(0x201e);
	} else {
		io_AppendText(0x204c, a7);
	}
	d2_SetForm(i, 3);
	*(int*) ((char*) g_77255c + 0x28c) = 0x55;
	io_AppendText(0x2005);
	d2_SetForm(i, 1);
	io_AppendText(0x68112c);
	ent = (char*) fcn_00503fe0(1, 6);
	while (ent != 0) {
		if (*(short*) (ent + 0x27) == (short) (id & 0xffff) ||
		    *(short*) (ent + 0x25) == (short) (id & 0xffff)) {
			b = *(unsigned char*) ent;
			kind = fcn_00504bd0((int) b);
			n = fcn_0050c1b0(ent, (int) (id & 0xffff), info);
			if (n != 0 || (kind != 5 && kind != 6)) {
				c1fc += *(int*) ((char*) info + 0x44);
				e1ec += *(int*) ((char*) info + 0xc);
				b200 += *(int*) ((char*) info + 0x48);
				d1f8 += *(int*) ((char*) info + 0x50);
			}
		}
		ent = (char*) fcn_00503e80();
	}
	n = fcn_0050d640(id & 0xffff, 0, 0xffff, v1d0);
	i = 0;
	if (n > 0) {
		do {
			c1fc = fcn_0064d228();
			k = fcn_0064d228();
			d1f8 = fcn_0064d228();
			i++;
		} while (i < n);
		if (k != 0) {
			io_AppendText(0x2048, k);
		}
	}
	k = (id & 0xffff) * 0x21c;
	if (*(char*) (k + 0x7f4e06) != 0 || *(char*) (k + 0x7f4e09) != 0) {
		fcn_004fcda0(id, 0, v1d0);
		k = (id & 0xffff) * 0x21c;
		b = *(unsigned char*) (k + 0x7f4e06);
		h1f0 = (-(*(char*) (k + 0x7f4ca9) != 0) & 0x28) + 0x253;
		if (b != 0) {
			io_AppendText(0x2049, (int) b + h1f0, v1d0[1]);
		}
		b = *(unsigned char*) ((id & 0xffff) * 0x21c + 0x7f4e09);
		if (b != 0) {
			io_AppendText(0x2049, (int) b + h1f0, v1d0[2]);
		}
		d1f8 += v1d0[1] + v1d0[2];
		c1fc += v1d0[1] + v1d0[2];
	}
	n = fcn_004fcb50(id, vals, 0);
	if (n != 0) {
		i = 0;
		do {
			b200 = a7;
			if (names[i] == 0) {
				break;
			}
			io_AppendText(0x6a4340, (unsigned char) names[i] + 0x1f64,
				vals2[i], vals[i]);
			a7 += vals[i];
			d1f8 -= vals[i];
			f1e8 += vals[i];
			i++;
			b200 = a7;
		} while (i < 6);
	}
	if (e1ec != 0) {
		io_AppendText(0x204a, e1ec);
	}
	n = fcn_0050d5d0(id & 0xffff, 0, v1d0);
	a7 = 0;
	i = 0;
	if (n > 0) {
		do {
			b200 = fcn_0064d228();
			a7 = fcn_0064d228();
			d1f8 = fcn_0064d228();
			i++;
		} while (i < n);
	}
	if (b200 != 0 && a7 != 0) {
		io_AppendText(0x204b, a7);
	}
	io_AppendText(0x204c, d1f8);
	c1fc -= b200;
	if (c1fc > 0) {
		io_AppendText(0x204d, c1fc);
	} else if (c1fc < 0) {
		io_AppendText(0x204e, c1fc);
	}
	n = fcn_0050d2a0((id & 0xffff) * 0x21c + (int) (char*) g_7f4ca0);
	io_AppendText(0x2029, ((n - f1e8) - e1ec) - a7);
	fcn_005459a0(0xffff);
	fcn_00476970(g_77250c);
	fcn_00469e30(0x79d);
	g_774978 = 1;
	g_1040488 = 0;
	g_1040480 = g_1040494;
	g_1040484 = 0;
	g_104048c = g_1040490;
	d2_SetForm(i, 1);
	k = g_772514;
	d2_SetForm(i, 2);
	io_AppendText(0x7d);
	fcn_0046e830(-1, -1, g_772514, k, 0x767);
	*(int*) (k * 0x3cc + 0x10161b4) = 0x18;
	fcn_004234e0(0, "RollenKurz_s_01", 1, 0x3f, 0x7f, 0, 0);
	i = fcn_005373e0((int) fcn_00541620, 0x24087);
	while (i != 0) {
		fcn_00535630();
		if (g_100f1dc == 2 || g_14cf950 == 0x1c) {
			g_774654 = 1;
		}
		i = fcn_005373e0((int) fcn_00541620, 0x24087);
	}
	fcn_005355f0();
fold:
	*(int*) (sel + 0x2c) += *(int*) (sel + 0x14) + *(int*) (sel + 0x18);
	*(int*) (sel + 0x14) = 0;
	*(int*) (sel + 0x30) += *(int*) (sel + 0x1c);
	*(int*) (sel + 0x18) = 0;
	*(int*) (sel + 0x34) += *(int*) (sel + 0x20);
	*(int*) (sel + 0x1c) = 0;
	*(int*) (sel + 0x38) += *(int*) (sel + 0x24);
	*(int*) (sel + 0x20) = 0;
	*(int*) (sel + 0x24) = 0;
	*(int*) (sel + 0x28) = 0;
	*(int*) (sel + 0x40) = 0;
	*(int*) (sel + 0x44) = 0;
	*(int*) (sel + 0x48) = 0;
	*(int*) (sel + 0x4c) = 0;
	*(int*) (sel + 0x50) = 0;
	*(int*) (sel + 0x54) = 0;
	if (g1f4 != 0) {
		fcn_00473150((unsigned char*) g1f4);
		g1f4 = 0;
	}
	n = fcn_0050db40((char*) ((id & 0xffff) * 0x21c + (int) (char*) g_7f4ca0),
		-(f1e8 + e1ec + a7));
	if (n != 0) {
		memset(panel, 0, 0x114);
		*(unsigned char*) (panel + 8) = 9;
		*(unsigned char*) (panel + 0x26) = 0x60;
		*(int*) (panel + 0x14) = -1;
		*(unsigned char*) (panel + 0x30) = 1;
		*(int*) (panel + 0xc) = *(int*) ((id & 0xffff) * 0x21c + 0x7f4ca4);
		*(int*) (panel + 0x34) = *(int*) (panel + 0xc);
		if (g1f4 != 0) {
			fcn_00473150((unsigned char*) g1f4);
		}
		fcn_004e5a00(panel);
		if (g_774968 != 0) {
			fcn_005413d0(id & 0xffff);
		}
		g_774968 = 0;
	}
}
