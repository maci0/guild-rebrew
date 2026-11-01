#include <string.h>

/* Personnel/mercenary book controller. Native extent 0x005b6300..0x005b787b
 * (5499 bytes, chkstk frame 0x1a4c, no frame pointer).
 *
 * Frame map recovered from the native esp-relative accesses (all offsets are
 * from the bottom of the chkstk allocation; the caller's 4 saved registers sit
 * above it, so native [esp+N] equals frame offset N-0x10):
 *   0x00  19 int slots (locals/element handles)
 *   0x4c  D2 message packet, 0xf8 bytes (id at +0, value at +4, +8, ...)
 *   0x144 selection record, 0x5c bytes (+0 type, +0x08/+0x0c coordinates)
 *   0x1a0 secondary record, 0x54 bytes
 *   0x1f4 text buffer 0x60
 *   0x25c 12 selection rows of 0x5c (0x450)
 *   0x6a4 two more dwords
 *   0x73c text buffer 0x60, 0x79c text buffer 0x60
 *   0x7fc text buffer 0x200, 0x9fc text buffer 0x400
 *   0xdfc second 12-row selection block (0x450)
 *   0x124c text buffer 0x400, 0x164c text buffer 0x400
 * The frame declared below reproduces those offsets exactly.
 *
 * Partial reconstruction: the opening block through the 12-row selection reset
 * (native 0x005b6300..0x005b6706). The remainder
 * (0x005b670c..0x005b787a, the message loop and teardown) is not transcribed.
 * The final store only pins the frame extent until the rest is written. */


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
	char pad21[0x3c - 0x21];
	int a3c;
	char pad40[0x58 - 0x40];
	int a58;
} SEL;

typedef struct {
	int id;        /* +0x00 */
	int val;       /* +0x04 */
	int f08;       /* +0x08 */
	int f0c;
	int f10;
	char pad14[8];
	int f1c;
	char pad20[8];
	int f28;
	int f2c;
	int f30;
	short w34;
	char b36;
	short w38;
	char b3a;
	char pad3b[0x58 - 0x3b];
	char b58;
	char b59;
	char pad5a[2];
	char b5c;
	int f60;
	char pad64[0x8c - 0x64];
	int f8c;
	char pad90[0xf8 - 0x90];
} MSG;

typedef struct {
	int v10;
	char* book;     /* 0x14 */
	int v18;
	int v1c;
	int v20;
	char* row;      /* 0x24 */
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
	MSG msg;        /* 0x6c */
	SEL sel;        /* 0x154 */
	char pad1b0[0x54];
	char txt204[0x60];
	SEL rows[12];   /* 0x264 */
	char pad6b4[0x98];
	char txt74c[0x60];
	char txt7ac[0x60];
	char txt80c[0x200];
	char txta0c[0x400];
	SEL rows2[12];  /* 0xe0c */
	char txt125c[0x400];
	char txt165c[0x400];
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

#define G(p) (*(int*) (p))


/* ADDRESS: GOLDTL 0x005b6300 */
int __cdecl fcn_005b6300(unsigned char* a1, int a2, int a3)
{
	FRAME f;
	char* row;
	char* book;
	char* rec = a1;
	char* r;
	char* tbl;
	int el;
	int i;
	int t;

	f.sel.type = 0;
	memset(&f.sel.a04, 0, 0x58);
	f.v38 = 0;
	t = *a1;
	tbl = (char*) *(unsigned int*) 0x868050 + t;
	row = tbl + t * 0x24c;
	f.v34 = -1;
	f.v48 = -1;
	f.v28 = -1;
	f.v1c = -1;
	f.v20 = -1;
	f.v44 = -1;
	f.v18 = -1;
	f.v40 = -1;
	f.v4c = -1;
	f.row = row;

	if (row[0] != 4 && row[0] != 0x13 && row[0] != 0x10) {
		book = (char*) fcn_00534c40(a2, 0x6a42c8, 4, 0x6ac2ec, 0x6ac300, 0x6ac314, 0x6ac328);
	} else {
		book = (char*) fcn_00534c40(a2, 0x6a42c8, 4, 0x6ac2cc, 0x6ac300, 0x6ac314, 0x6ac328);
	}
	f.book = book;
	fcn_005350d0((int) book);
	fcn_0057e880(0x21, (int) book, 0, 0);
	fcn_00517c00(*(unsigned short*) (rec + 0x27), 1, 2, f.txt7ac);
	fcn_00517c00(*(unsigned short*) (rec + 0x25), 1, 2, f.txt74c);
	r = fcn_0050dc90(rec);
	if (r == 0) {
		strcpy(f.txt204, *(char**) 0x14abc28);
	} else {
		fcn_00517c00(*(unsigned short*) r, 1, 1, f.txt204);
	}
	d2_SetForm(*(int*) (book + 0x228), 3);
	f.v50 = fcn_00472250(*(int*) (book + 0x228), 3, 2);
	fcn_00472380(f.v50, 0x32, 0x96, *(int*) (rec + 0x3d));
	if (row[0] != 4 && row[0] != 0x13 && row[0] != 0x10) {
		f.v44 = fcn_00472250(*(int*) (book + 0x228), 3, 3);
		fcn_00472380(f.v44, 0, 4, *(int*) (rec + 0x41));
		fcn_00468bb0(f.v44, 5, *(int*) 0x14abbd8, *(int*) 0x14abbdc,
			*(int*) 0x14abbe0, *(int*) 0x14abbe4, *(int*) 0x14abbe8);
	}
	d2_SetForm(*(int*) (book + 0x228), 3);
	io_AppendText((int) 0x6ac2c8);
	io_AppendText((int) 0x6ac2c8);
	f.msg.f0c = fcn_00472250(*(int*) (book + 0x228), 3, io_AppendText(0x1a20));
	if (row[0] != 5 && row[0] != 9) {
		d2_SetForm(*(int*) (book + 0x228), 3);
		fcn_005b58a0(&f.sel.a08, 0x20, *(int*) (0x77255c + 0xc) / 2 - 0x18);
		el = d2_ShowTxt(*(int*) 0x772514, *(int*) 0x14abbd4,
			(short) (f.sel.a0c - 0x20), (short) (f.sel.a10 - 0x38));
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
	if (row[0] == 4 || row[0] == 0x13 || row[0] == 0x10) {
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
	f.txt165c[0x3ff] = 0;
	return 0;
}
