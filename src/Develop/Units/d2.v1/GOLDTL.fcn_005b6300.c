#include <string.h>

/* Personnel/mercenary book controller. Native extent 0x005b6300..0x005b787b
 * (5499 bytes, chkstk frame 0x1a4c, no frame pointer).
 *
 * Frame map recovered from the native esp-relative accesses; offsets are from
 * the bottom of the chkstk allocation, so native [esp+N] reached with the four
 * saved registers pushed is frame offset N-0x10:
 *   0x00  19 int slots (loop counters, element handles, book pointer)
 *   0x4c  D2 message packet, 0xf8 bytes (+0x00 id, +0x04 type, +0x08 table
 *         words, +0x0c record value, +0x28..+0x34 form geometry, +0x58 handle,
 *         +0x5c per-row flags/handles, +0x8c trailing value)
 *   0x144 selection record, 0x5c bytes (+0x08 handle, +0x0c x, +0x1c count,
 *         +0x20 state byte, +0x24 flag, +0x58 label)
 *   0x1a0 secondary record, 0x54 bytes (field at +0x0c)
 *   0x1f4 text buffer 0x60
 *   0x254 12 selection rows of 0x5c (0x450)
 *   0x6a4 dispatch list, 12 entries at +0x04
 *   0x740 text buffer 0x60, 0x7a0 text buffer 0x60
 *   0x800 text buffer 0x1fc, 0x9fc text buffer 0x400
 *   0xdfc second 12-row selection block (0x450)
 *   0x124c text buffer 0x400, 0x164c text buffer 0x400
 * The declared FRAME reproduces those offsets exactly (checked statically).
 *
 * Transcribed: the opening block through the 12-row reset, the selection
 * population loop, the dialog message loop with its per-element updates, the
 * row/row2 comparison and teardown. The chkstk allocation is 0x1a4c like the
 * native body (no spill slots), and the epilogue matches: fcn_00534f30 runs,
 * then "add esp,0x1a60" / tail call to fcn_00532ef0. */


typedef struct {
	int type;      /* +0x00 */
	int a04;
	int a08;
	int a0c;
	short a10;
	short a12;
	int a14;
	int a18;
	short a1c;
	short a1e;
	char a20;
	char pad21[3];
	int a24;
	char pad28[0x3c - 0x28];
	int a3c;
	char pad40[0x58 - 0x40];
	int a58;
} SEL;

typedef struct {
	int id;        /* +0x00 */
	char type;     /* +0x04 */
	char pad05[3];
	int f08;       /* +0x08 */
	int f0c;
	int f10;
	char pad14[0x28 - 0x14];
	int f28;
	int f2c;
	int f30;
	short w34;
	char b36;
	short w38;
	char b3a;
	char pad3b[0x58 - 0x3b];
	int f58;
	int f5c[12];
	int f8c;
	char pad90[0xf8 - 0x90];
} MSG;

typedef struct {
	int v10;
	char* book;     /* 0x04 */
	int v18;
	int v1c;
	int v20;
	char* row;      /* 0x14 */
	int v28;
	int v2c;
	int v30;
	int v34;
	int v38;
	int v3c;
	int v40;
	int v44;
	int v48;
	int v4c;
	int v50;
	int v54;
	int v58;
	MSG msg;        /* 0x4c */
	SEL sel;        /* 0x144 */
	char rec2[0x54];/* 0x1a0 */
	char txt204[0x60];
	SEL rows[12];   /* 0x254 */
	int f6a4;
	int arr6a8[12];
	char pad6d8[0x64];
	char txt740[0x60];
	char txt7a0[0x60];
	char txt800[0x200];
	char txt9fc[0x400];
	SEL rows2[12];  /* 0xdfc */
	char txt124c[0x400];
	char txt164c[0x400];
} FRAME;

int __cdecl fcn_00534c40(int, int, int, int, int, int, int);
void __cdecl fcn_005350d0(int);
int __cdecl fcn_0057e880(int, int, int, int);
int __cdecl fcn_00517c00(int, int, int, void*);
char* __cdecl fcn_0050dc90(char*);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_005b58a0(void*, int, int);
int __cdecl d2_ShowTxt(int, int, int, int);
void __cdecl fcn_00468bb0(int, int, int, int, int, int, int);
void __cdecl fcn_0046b2b0(int);

int __cdecl fcn_0057ecc0(void);
void __cdecl fcn_005b6130(int, int);
void __cdecl fcn_00534c20(int);
void __cdecl fcn_00535550(int);
void __cdecl fcn_00535560(int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_004c4510(int, int);
void __cdecl fcn_004c4570(int, int, int, void*);
int __cdecl fcn_004c5360(void);
void __cdecl fcn_004c5530(void*);
void __cdecl fcn_004c4eb0(int);
void __cdecl fcn_004c4ef0(int);
void __cdecl fcn_004c5150(int, int, char, int);
void __cdecl fcn_004c54c0(int, int, int, int);
int __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00519190(int, ...);
int __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_0050c1b0(int, int, void*);
int __cdecl fcn_004693b0(void);
void __cdecl fcn_00469470(int, int);
void __cdecl fcn_004695a0(int, int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_005b5eb0(char*, char*);
void __cdecl fcn_005b59c0(int, int, int);
void __cdecl fcn_005b5c70(int);
void __cdecl fcn_005b5ce0(int, int, int, int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_005373e0(int, int);
int __cdecl fcn_004c53b0(void);
int __cdecl fcn_00505d00(int, void*);
int __cdecl fcn_005b5750(void);
int __cdecl fcn_0050b750(int, char);
extern double g_6640e8;
float __cdecl fcn_0050b8d0(unsigned char*, int, int, int);
int __cdecl fcn_00526010(int, int);
int __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl fcn_005462a0(void);
int __cdecl fcn_00505370(void*);
char* __cdecl fcn_0064d228(void);
int __cdecl fcn_0064d228_b(void);
int __cdecl fcn_00534f30(int);
int __cdecl fcn_00532510(void);
int __cdecl fcn_00532ef0(void);

#define G(p) (*(int*) (p))


/* ADDRESS: GOLDTL 0x005b6300 */
int __cdecl fcn_005b6300(unsigned char* a1, int a2, int a3)
{
	FRAME f;
	char* book;
	char* rec = a1;
	char* r;
	char* p;
	char* tbl;
	char* e;
	int el;
	int i;
	int t;
	int c;
	int k;
	int x;
	int y;
	int n;
	int trec;

	t = *a1;
	f.sel.type = 0;
	memset(&f.sel.a04, 0, 0x58);
	f.v38 = 0;
	tbl = (char*) *(unsigned int*) 0x868050 + t;
	f.v34 = -1;
	f.v48 = -1;
	f.v28 = -1;
	f.v1c = -1;
	f.v20 = -1;
	f.v44 = -1;
	f.v18 = -1;
	f.v40 = -1;
	f.v4c = -1;
	f.row = tbl + t * 0x24c;

	if (f.row[0] != 4 && f.row[0] != 0x13 && f.row[0] != 0x10) {
		book = (char*) fcn_00534c40(a2, 0x6a42c8, 4, 0x6ac2ec, 0x6ac300, 0x6ac314, 0x6ac328);
	} else {
		book = (char*) fcn_00534c40(a2, 0x6a42c8, 4, 0x6ac2cc, 0x6ac300, 0x6ac314, 0x6ac328);
	}
	f.book = book;
	fcn_005350d0((int) book);
	fcn_0057e880(0x21, (int) book, 0, 0);
	fcn_00517c00(*(unsigned short*) (rec + 0x27), 1, 2, f.txt7a0);
	fcn_00517c00(*(unsigned short*) (rec + 0x25), 1, 2, f.txt740);
	r = fcn_0050dc90(rec);
	if (r == 0) {
		strcpy(f.txt204, *(char**) 0x14abc28);
	} else {
		fcn_00517c00(*(unsigned short*) r, 1, 1, f.txt204);
	}
	d2_SetForm(*(int*) (book + 0x228), 3);
	f.v50 = fcn_00472250(*(int*) (book + 0x228), 3, 2);
	fcn_00472380(f.v50, 0x32, 0x96, *(int*) (rec + 0x3d));
	if (f.row[0] != 4 && f.row[0] != 0x13 && f.row[0] != 0x10) {
		el = f.v44 = fcn_00472250(*(int*) (book + 0x228), 3, 3);
		fcn_00472380(el, 0, 4, *(int*) (rec + 0x41));
		fcn_00468bb0(el, 5, *(int*) 0x14abbd8, *(int*) 0x14abbdc,
			*(int*) 0x14abbe0, *(int*) 0x14abbe4, *(int*) 0x14abbe8);
	}
	d2_SetForm(*(int*) (book + 0x228), 3);
	io_AppendText(0x6ac2c8);
	io_AppendText(0x6ac2c8);
	f.msg.f0c = fcn_00472250(*(int*) (book + 0x228), 3, io_AppendText(0x1a20));
	if (f.row[0] != 5 && f.row[0] != 9) {
		d2_SetForm(*(int*) (book + 0x228), 3);
		fcn_005b58a0(&f.sel.a08, 0x20, *(int*) (0x77255c + 0xc) / 2 - 0x18);
		el = d2_ShowTxt((short) (f.sel.a10 - 0x38), (short) (f.sel.a0c - 0x20),
			(char*) *(int*) 0x14abbd4, *(int*) 0x772514);
		G(G(0x1015ea0) + el * 756 + 0x6c) = 1;
		G(G(0x1015ea0) + el * 756 + 0x18) = 0xa0;
	}
	for (i = 0; i < 4; i++) {
		d2_SetForm(G(book + 0x228 + i * 4), 1);
		io_AppendText(0x1a1d);
		if (i == 0) {
			d2_SetForm(G(book + 0x228), 5);
		} else {
			d2_SetForm(G(book + 0x228 + i * 4), 4);
		}
		io_AppendText(0x6a2310, 0x1a37, i);
	}
	if (f.row[0] == 4 || f.row[0] == 0x13 || f.row[0] == 0x10) {
		el = fcn_00472250(G(book + 0x228), 3, 3);
		f.v44 = fcn_00472250(G(book + 0x228), 3, 1);
		fcn_0046b2b0(el);
		fcn_0046b2b0(f.v44);
		f.v44 = -1;
	}
	d2_SetForm(G(book + 0x230), 3);
	rec = (char*) (*(int*) 0x772514 * 0x3cc + 0x1015f40);
	f.v54 = G(rec + 0xc) / 2;
	f.v2c = G(rec + 0x10) / 2;
	for (i = 0; i < 0xc; i++) {
		G((char*) &f.rows + i * 0x5c + 8) = 0;
		G((char*) &f.rows + i * 0x5c + 0xc) = -1;
	}

	/* --- message loop: fill the selection rows for the current record --- */
	f.v10 = 0;
	f.v30 = 1;
	k = 0;
	p = f.book + 0x22c;
	for (f.v10 = 0; f.v10 < 0xc; f.v10++) {
		if (f.v10 >= (int) ((unsigned char) f.row[0x231] + (unsigned char) f.row[0x232]))
			break;
		y = k / 2;
		if (y >= 2) {
			k = 0;
			y = 0;
			p += 4;
			if (++f.v30 > 3)
				break;
		}
		e = *(char**) p;
		fcn_004727a0((int) e, 3);
		f.rows[f.v10].a58 = (int) e;
		fcn_005b58a0((void*) ((k % 2) * f.v44 + 0x28), y * f.v2c + 0x11,
			(int) &f.rows[f.v10]);
		if (f.v10 == 0 && f.v40 == -1) {
			f.v40 = fcn_004693b0();
			if (f.sel.a0c != -1) {
				fcn_00469470(f.v40, f.sel.a0c);
			} else {
				fcn_00469470(f.v40, f.rows[0].a0c);
			}
		} else {
			fcn_00469470(f.v40, f.rows[f.v10].a0c);
		}
		k++;
	}
	fcn_004695a0(f.v40, -1);
	f.v30 = f.v10;
	fcn_005b5eb0(f.book, a1);
	fcn_00473a90(0, 0);

	while (fcn_005373e0((int) fcn_005b6300, 0x677c7)) {
		if (G(0x14ce8e0) != 0 && fcn_0057ecc0() == 1)
			G(0x774654) = 1;
		fcn_005b6130((int) f.book, (int) a1);
		fcn_005350d0((int) f.book);
		fcn_00534c20((int) f.book);
		if (*(unsigned char*) 0x14cf950 == 0xcd)
			fcn_00535550((int) f.book);
		if (*(unsigned char*) 0x14cf950 == 0xcb)
			fcn_00535560((int) f.book);
		if (*(char*) (f.book + 0x270) != 0)
			goto L6fa2;
		if (f.v50 != -1) {
			f.v3c = fcn_00471f80(f.v50);
			if (f.v3c != G(a1 + 0x3d)) {
				if (f.v4c != -1 && fcn_004c4450(f.v4c) == 0)
					goto L6901;
				fcn_004c4510((int) a1, G(a1 + 1));
				fcn_004c4570(4, 1, 0x3d, &f.v3c);
				f.v4c = fcn_004c5360();
			}
		}
L6901:
		fcn_004727a0(G(f.book + 0x228), 4);
		fcn_0050c1b0((int) a1, *(unsigned short*) 0x774970, f.rec2);
		io_AppendText(0x1a2c, G(f.rec2 + 0xc));
		f.v2c = (int) fcn_0050dc90(a1);
		n = G(&f.sel.a1c);
		if (f.v2c == 0)
			goto L6993;
		if (*(unsigned short*) f.v2c == *(unsigned short*) 0x774970)
			goto L698c;
		if (*(char*) (f.v2c + 8) == 0)
			goto L6993;
		if (n != -1)
			goto L698c;
		f.sel.a08 = f.v2c;
		fcn_005b59c0(f.v2c, (int) &f.sel, 0);
		goto L69b6;
L698c:
		if (*(char*) (f.v2c + 8) != 0)
			goto L69b6;
L6993:
		if (n == -1)
			goto L69b6;
		f.sel.a08 = 0;
		fcn_005b5c70((int) &f.sel);
		f.v1c = -1;
L69b6:
		if (G(0x100f1dc) == -1)
			goto L6fa2;
		if (G(0x67d370) == f.sel.a0c && f.sel.a0c != -1) {
			for (i = 0; i < 3; i++) {
				fcn_004727a0(G(f.book + 0x228 + i * 4), 2);
				io_AppendText(0x6811b0);
			}
			f.v28 = -1;
			f.v1c = -1;
			f.v20 = -1;
			f.v18 = f.v10;
			t = (unsigned char) f.sel.a20;
			if (f.sel.a08 == 0 && t != 2) {
				e = (char*) fcn_005101e0(
					(char*) ((*(unsigned short*) (a1 + 0x27) * 0x21c) + 0x7f4ca0),
					*a1, 0, (char*) -1);
				e = fcn_0064d228();
				fcn_004727a0(f.sel.a58, 2);
				f.v48 = fcn_00472250(f.sel.a58, 2,
					io_AppendText(0x1a22, (int) e, f.row[0x223] + 0x130));
			} else if (t == 1) {
				fcn_004727a0(f.sel.a58, 2);
				io_AppendText(0x6811b0);
				f.v34 = fcn_00472250(f.sel.a58, 2,
					io_AppendText(0x1a21, *(unsigned short*) f.sel.a08));
			}
		}
		if (G(0x100f1dc) == -1)
			goto L6fa2;
		if (G(0x67d370) == f.v58 && f.v38 != 0
			&& *(signed char*) 0x7747b0 >= 0) {
			e = (char*) fcn_005b5750();
			if (e == 0)
				goto L6cb7;
			y = (int) e / f.v38;
			x = y % 3;
			trec = *(unsigned short*) 0x774970 * 0x21c;
			t = fcn_0050b750((int) e, *(char*) 0x773d75);
			if (fcn_00526010((int) (trec + 0x7f4ca0), t) == 0)
				goto L6cb7;
			if (f.v30 > 0) {
				f.v38 = f.v30;
				f.v10 = (int) (char*) &f.rows[0].a08;
				do {
					e = *(char**) f.v10;
					if (e != 0) {
						fcn_004c4eb0(0x6ac2bc);
						fcn_004c5150(G(e + 4), -1, *(char*) 0x773d75,
							fcn_0050b750(y, *(char*) 0x773d75));
						trec = *(unsigned short*) 0x774970 * 0x21c;
						fcn_004c54c0(G(0x7f4ca4 + trec), G(e + 4), x, 0);
						fcn_004c4ef0(0x6ac2bc);
					}
					f.v10 += 0x5c;
				} while (--f.v38 != 0);
			}
			if (f.sel.a08 != 0) {
				fcn_004c4eb0(0x6ac2b0);
				fcn_004c5150(G(f.sel.a08 + 4), -1, *(char*) 0x773d75,
					fcn_0050b750(y, *(char*) 0x773d75));
				trec = *(unsigned short*) 0x774970 * 0x21c;
				fcn_004c54c0(G(0x7f4ca4 + trec), G(f.sel.a08 + 4), x, 0);
				fcn_004c4ef0(0x6ac2b0);
			}
			trec = *(unsigned short*) 0x774970 * 0x21c;
			fcn_004c5150(G(0x7f4ca4 + trec), -1, *(char*) 0x773d75, fcn_0050b750((int) e, *(char*) 0x773d75));
		}
L6cb7:
		if (G(0x100f1dc) == -1)
			goto L6fa2;
		c = G(0x67d370);
		if (c == f.v48 && f.v48 != -1
			&& *(signed char*) 0x7747b0 >= 0) {
			e = (char*) f.v2c;
			if (e != 0 && *(char*) (e + 8) != 0)
				goto L6fa2;
			t = fcn_005463a0(2, 0, 7, 3, G(a1 + 1));
			if (t != 0) {
				do {
					if (*(char*) (t + 0xac) == 0)
						goto L6e44;
					t = fcn_005462a0();
				} while (t != 0);
			}
			memset(&f.msg, 0, 0xf8);
			f.msg.type = 7;
			f.msg.b36 = 1;
			f.msg.f5c[0] = 1;
			f.msg.f0c = *(int*) (a1 + 1);
			f.msg.f08 = G(0x7f4ca4 + *(unsigned short*) 0x774970 * 0x21c);
			f.msg.f28 = G(0x7f4c00);
			f.msg.f2c = G(0x7f4c04);
			f.msg.f30 = G(0x7f4c08);
			f.msg.w34 = *(short*) 0x7f4c0c;
			if (fcn_00505370((int) a1) != 0)
				f.msg.f5c[1] = -1;
			else
				f.msg.f5c[1] = G(G(0x7746cc) + 8);
			*(char*) &f.msg.f58 = 0;
			fcn_004c5530(&f.msg);
			fcn_0051af00(f.txt800, 0x1939, f.row[0x223] + 0x130);
			fcn_00526120(f.txt800, 0);
L6e44:
			for (i = 0; i < 3; i++) {
				fcn_004727a0(G(f.book + 0x228 + i * 4), 2);
				io_AppendText(0x6811b0);
			}
			f.sel.a20 = 2;
			goto L6f92;
		}
		if (c != f.v34 || f.sel.a08 == 0)
			goto L6fa2;
		if (fcn_00526120(*(char**) 0x14abbf8, 1) == 0)
			goto L6fa2;
		for (i = 0; i < 3; i++) {
			fcn_004727a0(G(f.book + 0x228 + i * 4), 2);
			io_AppendText(0x6811b0);
		}
		memset(&f.msg, 0, 0xf8);
		f.msg.type = 0x31;
		f.msg.b36 = 1;
		f.msg.f08 = G(0x7f4ca4 + *(unsigned short*) 0x774970 * 0x21c);
		f.msg.f0c = *(int*) (a1 + 1);
		f.msg.f28 = G(0x7f4c00);
		f.msg.f2c = G(0x7f4c04);
		f.msg.f30 = G(0x7f4c08);
		f.msg.w34 = *(short*) 0x7f4c0c;
		f.msg.f58 = G(f.sel.a08 + 4);
		fcn_004c5530(&f.msg);
		for (i = 0; i < 3; i++) {
			fcn_004727a0(G(f.book + 0x228 + i * 4), 2);
			io_AppendText(0x6811b0);
		}
		f.v18 = -1;
L6f92:
		f.v28 = -1;
		f.v1c = -1;
		f.v20 = -1;
		f.v34 = -1;
L6fa2:
		memcpy(f.rows2, f.rows, sizeof(f.rows));
		if (f.v30 > 0) {
			for (i = 0; i < f.v30; i++)
				f.rows[i].a08 = 0;
		}
		f.v40 = fcn_00505d00((int) a1, &f.f6a4);
		f.v2c = 2;
		p = (char*) &f.arr6a8[0];
		do {
			for (k = 0; k < 0xc; k++) {
				x = G(p);
				if (x == 0xffff)
					continue;
				if (f.v30 > 0) {
					for (n = 0; n < f.v30; n++) {
						if (f.rows[n].a08 == (int) (char*) (x * 0x21c + 0x7f4ca0))
							break;
					}
					if (n < f.v30)
						continue;
					for (n = 0; n < f.v30; n++) {
						if (f.rows[n].a08 == 0)
							break;
					}
					if (n >= f.v30)
						continue;
					f.rows[n].a08 = (int) (char*) (x * 0x21c + 0x7f4ca0);
					f.rows[n].a24 = *(unsigned char*) (x * 0x21c + 0x7f4ca0 + 0x165);
				}
				p += 4;
			}
			p = (char*) &f.arr6a8[0];
		} while (--f.v2c != 0);
		if (f.v30 > 0) {
			for (i = 0; i < f.v30; i++) {
				if (f.rows[i].a08 != f.rows2[i].a08 || f.rows[i].a24 != f.rows2[i].a24)
					fcn_005b5c70((int) &f.rows[i]);
			}
		}
		el = fcn_005463a0(2, 0, 6, 3, G(a1 + 1));
		for (i = 0; f.v10 = i, i < f.v30; i++) {
			if (f.rows[i].a08 != 0) {
				if (f.rows[i].a1c != -1)
					continue;
				fcn_005b59c0(f.rows[i].a08, (int) &f.rows[i], 0);
			} else {
				fcn_005b5ce0((int) a1, 6, (int) &f.rows[i], i);
			}
		}
		fcn_005b5ce0((int) a1, 7, (int) &f.sel, 0);
		if (f.v1c != -1 && f.v18 != -1 && f.rows[f.v18].a08 == 0) {
			f.v18 = -1;
			f.v28 = -1;
			f.v1c = -1;
			f.v20 = -1;
			f.v34 = -1;
			for (i = 0; i < 3; i++) {
				fcn_004727a0(G(f.book + 0x228 + i * 4), 2);
				io_AppendText(0x6811b0);
			}
		}
		if (G(0x100f1dc) == -1)
			goto L77c4;
		for (k = 0; k < 0xc; k++) {
			if (G(0x67d370) != f.rows[k].a0c)
				continue;
			for (i = 0; i < 3; i++) {
				fcn_004727a0(G(f.book + 0x228 + i * 4), 2);
				io_AppendText(0x6811b0);
			}
			f.v28 = -1;
			f.v1c = -1;
			f.v20 = -1;
			f.v34 = -1;
			f.v18 = k;
			if (f.rows[k].a08 == 0) {
				fcn_005101e0(
					(char*) ((*(unsigned short*) (a1 + 0x27) * 0x21c) + 0x7f4ca0),
					*a1, -1, 1);
				e = fcn_0064d228();
				fcn_004727a0(f.rows[k].a58, 2);
				f.v28 = fcn_00472250(f.rows[k].a58, 2,
					io_AppendText(0x1a22, (int) e, (unsigned char) f.row[0x230] + 0x20d));
			} else if (f.rows[k].a20 == 1) {
				fcn_004727a0(f.rows[k].a58, 2);
				io_AppendText(0x6811b0);
				f.v1c = fcn_00472250(f.rows[k].a58, 2,
					io_AppendText(0x1a21, *(unsigned short*) f.rows[k].a08));
				if (*(unsigned char*) (f.rows[k].a08 + 0x165) == f.row[0x230])
					f.v20 = fcn_00472250(f.rows[k].a58, 2,
						io_AppendText(0x1a25, *(unsigned short*) f.rows[k].a08));
			}
		}
		f.v10 = 0xc;
		c = G(0x67d370);
		if (c == f.v28 && f.v18 != -1) {
			el = fcn_005463a0(2, 0, 6, 3, G(a1 + 1));
			if (el != 0) {
				G(el + f.v18 * 4 + 0xb0) = 1;
			} else {
				memset(&f.msg, 0, 0xf8);
				f.msg.type = 6;
				f.msg.b36 = 1;
				f.msg.f08 = G(0x7f4ca4 + *(unsigned short*) 0x774970 * 0x21c);
				f.msg.f0c = *(int*) (a1 + 1);
				f.msg.f28 = G(0x7f4c00);
				f.msg.f2c = G(0x7f4c04);
				f.msg.f30 = G(0x7f4c08);
				f.msg.w34 = *(short*) 0x7f4c0c;
				f.msg.f5c[f.v18] = 1;
				if (fcn_00505370((int) a1) != 0)
					f.msg.f8c = -1;
				else
					f.msg.f8c = G(G(0x7746cc) + 8);
				*((char*) &f.msg.f58 + 1) = 1;
				*(char*) &f.msg.f58 = f.row[0x230];
				fcn_004c5530(&f.msg);
			}
			f.v18 = -1;
			for (i = 0; i < 3; i++) {
				fcn_004727a0(G(f.book + 0x228 + i * 4), 2);
				io_AppendText(0x6811b0);
			}
			fcn_0057e880(0x22, 0, 0, 0);
		} else if (c == f.v1c && f.v18 != -1
			&& *(signed char*) 0x7747b0 >= 0) {
			if (fcn_00526120(*(char**) 0x14abbf8, 1) == 0)
				goto L77c4;
			for (i = 0; i < 3; i++) {
				fcn_004727a0(G(f.book + 0x228 + i * 4), 2);
				io_AppendText(0x6811b0);
			}
			memset(&f.msg, 0, 0xf8);
			f.msg.type = 0x31;
			f.msg.b36 = 1;
			f.msg.f08 = G(0x7f4ca4 + *(unsigned short*) 0x774970 * 0x21c);
			f.msg.f0c = *(int*) (a1 + 1);
			f.msg.f28 = G(0x7f4c00);
			f.msg.f2c = G(0x7f4c04);
			f.msg.f30 = G(0x7f4c08);
			f.msg.w34 = *(short*) 0x7f4c0c;
			f.msg.f58 = G(f.rows[f.v18].a08 + 4);
			fcn_004c5530(&f.msg);
			f.v18 = -1;
		} else if (c == f.v20 && f.v18 != -1) {
			e = (char*) f.rows[f.v18].a08;
			if (G(e + 0x184) != 0 && G(e + 0x184) + 0x2c != G(a1 + 1)) {
				fcn_0051af00(f.txt124c, 0x42c4, *(unsigned short*) e);
				fcn_00526120(f.txt124c, 4);
			} else if (G(0x774800) == 0 && G(e + 0x174) < 4) {
				fcn_0051af00(f.txt164c, 0x1a27, 4);
				fcn_00526120(f.txt164c, 4);
			} else {
				t = (int) (fcn_0050b8d0(
					(unsigned char*) (*(unsigned short*) (a1 + 0x27) * 0x21c + 0x7f4ca0),
					*a1, -1, 1) * ((double) *(int*) (a1 + 0x3d) * g_6640e8));
				x = (int) (fcn_0050b8d0((unsigned char*) e, *a1, -1, 0) *
					((double) *(int*) (a1 + 0x3d) * g_6640e8));
				if (*(char*) (e + 9)) {
					fcn_0051af00(f.txt9fc, 0x1a29,
						*(unsigned short*) e,
						(unsigned char) f.row[0x22f] + 0x230);
				} else {
					fcn_0051af00(f.txt9fc, 0x1a28,
						*(unsigned short*) e,
						(unsigned char) f.row[0x22f] + 0x20d);
				}
				if (fcn_00526120(f.txt9fc, 0) == 0)
					goto L77c4;
				memset(&f.msg, 0, 0xf8);
				f.msg.type = 0x32;
				f.msg.b36 = 2;
				f.msg.f08 = G(0x7f4ca4 + *(unsigned short*) 0x774970 * 0x21c);
				f.msg.f0c = *(int*) (a1 + 1);
				f.msg.f28 = G(0x7f4c00);
				f.msg.f2c = G(0x7f4c04);
				f.msg.f30 = G(0x7f4c08);
				f.msg.w34 = *(short*) 0x7f4c0c;
				f.msg.f58 = G(e + 4);
				fcn_004c5530(&f.msg);
				p = f.book + 0x228;
				for (i = 0; i < 3; i++) {
					fcn_004727a0(G(p), 2);
					io_AppendText(0x6811b0);
					p += 4;
				}
				f.v18 = -1;
				f.v20 = -1;
			}
			goto L77c4;
		}
L77c4:
		;
	}
L77de:
	if (f.v40 != -1)
		fcn_00469510(f.v40);
	fcn_004c4510((int) a1, G(a1 + 1));
	if (f.v4c != -1) {
		f.v3c = fcn_00471f80(f.v4c);
		fcn_004c4570(4, 1, 0x41, &f.v3c);
	}
	if (f.v50 != -1) {
		f.v3c = fcn_00471f80(f.v50);
		fcn_004c4570(4, 1, 0x3d, &f.v3c);
	}
	fcn_004c5360();
	fcn_0057e880(0x21, 0, 1, 0);
	fcn_00534f30((int) f.book);
	return fcn_00532ef0();
}
