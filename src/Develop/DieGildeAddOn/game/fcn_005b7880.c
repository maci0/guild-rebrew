#include <string.h>

/*
 * Personnel book window controller.  Native extent 0x005b7880..0x005b8752
 * (3794 bytes), chkstk frame 0x110c, no frame pointer, saved registers
 * ebx/ebp/esi/edi.  Native order:
 *
 * 1. Building record and book window (fcn_00534c40 / fcn_005350d0), id
 *    buffers through fcn_00517c00, header labels and the four slot buttons.
 * 2. Twelve 0x5c-byte row records laid out over three pages, four rows per
 *    page; each row carries a radio button (fcn_004693b0 / fcn_00469470), a
 *    d2 icon, a label and a value control.
 * 3. Dialog loop: broadcast gating, per-row packet builds (types 6, 0x31,
 *    0x32), row refresh from the entity table at 0x7f4ca0 (0x21c-byte
 *    entities), the old-area diff and the label/value repaint.
 *
 * The frame is one aggregate at chkstk offset 0.  Frame layout (native esp
 * offsets; four saved registers sit below it):
 *   0x000 15 scalar slots
 *   0x03c message packet, 0xf8 bytes (f28/f2c/f30/w34, flag at +0x36,
 *         handle at +0x58, per-row flags at +0x5c, trailing value at +0x8c)
 *   0x134 twelve row records, 0x5c each
 *   0x584 0x60 name buffer
 *   0x5e4 0x80 worker buffer
 *   0x664 0x80 default buffer
 *   0x6e4 0x80 number buffer
 *   0x764 slot table, 0x26 ints
 *   0x7fc 0x60 number buffer
 *   0x85c 0x60 number buffer
 *   0x8bc 0x400 text buffer
 *   0xcbc second twelve-row block
 */

typedef struct {
	int id;                /* +0x00 */
	char type;             /* +0x04 */
	char pad05[3];
	int f08;               /* +0x08 */
	int f0c;               /* +0x0c */
	int f10;               /* +0x10 */
	char pad14[0x28 - 0x14];
	int f28;               /* +0x28 */
	int f2c;               /* +0x2c */
	int f30;               /* +0x30 */
	short w34;             /* +0x34 */
	char b36;              /* +0x36 */
	char pad37[0x58 - 0x37];
	char b58;              /* +0x58 */
	char b59;              /* +0x59 */
	char pad5a[0x5c - 0x5a];
	int f5c[12];           /* +0x5c */
	int f8c;               /* +0x8c */
	char pad90[0xf8 - 0x90];
} MSG;
/* SIZE 0xf8 */

typedef struct {
	int x;                 /* +0x00 */
	int y;                 /* +0x04 */
	unsigned char* obj;    /* +0x08 */
	int icon;              /* +0x0c */
	int bar;               /* +0x10 */
	int label;             /* +0x14 */
	int value;             /* +0x18 */
	int x1c;               /* +0x1c */
	unsigned char state;   /* +0x20 */
	char pad21[0x28 - 0x21];
	int a[6];              /* +0x28 */
	char pad40[0x58 - 0x40];
	int win;               /* +0x58 */
} Row;
/* SIZE 0x5c */

typedef struct {
	char pad0[0x18];
	int w;                 /* +0x18 */
	int h;                 /* +0x1c */
	char pad20[0x4c - 0x20];
	int f4c;               /* +0x4c */
	char pad50[0x5c - 0x50];
	int f5c;               /* +0x5c */
	char pad60[0x6c - 0x60];
	int f6c;               /* +0x6c */
	char pad70[0x2f4 - 0x70];
} Ctl;
/* SIZE 0x2f4 */

typedef struct {
	int* pIt; int pg; int cnt; int hA; char* win; int tv; int hB; int hC;
	int tv3; int hD; unsigned char* ent; int hRadio; int nSlots; int tv2; int hE;
	MSG msg; Row rows[12];
	char txtName[0x60]; char txtWorker[0x80]; char txtDefault[0x80];
	char txtNum[0x80]; int slots[0x26];
	char numB[0x60]; char numA[0x60]; char text[0x400]; Row old[12];
} FRAME;
/* SIZE 0x110c */

#define GUI(i) (((Ctl*) *(void**) 0x1015ea0)[i])

extern int lpGebaeudePROT;

void* __cdecl fcn_00534c40(unsigned int, int, int, ...);
void __cdecl fcn_005350d0(char*);
void __cdecl fcn_00534c20(char*);
int __cdecl fcn_00517c00(int, int, int, char*);
char* __cdecl fcn_0050dc90(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char*, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00535550(char*);
void __cdecl fcn_00535560(char*);
int __cdecl fcn_005b5750(void);
int __cdecl fcn_0050b750(int, int);
int __cdecl fcn_00526010(void*, int, int);
void __cdecl fcn_004c4eb0(int);
void __cdecl fcn_004c5150(int, int, int, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_004c4ef0(int);
void __cdecl fcn_004c5530(void*);
void __cdecl fcn_0046b2b0(int);
int __cdecl fcn_00505d00(unsigned char*, int*);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl fcn_0046f940(int, char*);
int __cdecl fcn_0046fac0(int, int, char*, int);
int __cdecl fcn_005463a0(int, int, int, int, int);
float __cdecl fcn_005101e0(unsigned char*, int, int, int);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_0051af00(char*, char*, ...);
int __cdecl fcn_0050f950(int, int);
void __cdecl fcn_00472380(int, int, int, int);
int __cdecl fcn_004693b0(int, int);
void __cdecl fcn_00469470(int, int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00534f30(char*);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_00505370(char*);

/* ADDRESS: GOLDTL 0x005b7880 */
void __cdecl fcn_005b7880(unsigned char* a0, int a1)
{
	FRAME f;
	char* p;
	Row* r;
	int i = 0;
	int n;
	int y;
	int perRow;
	int entityId;
	double percent;

	f.nSlots = 0;
	f.hC = -1;
	f.hB = -1;
	f.hD = -1;
	f.hA = -1;
	f.hRadio = -1;
	f.ent = (unsigned char*) (lpGebaeudePROT + a0[0] * 0x24d);
	f.win = (char*) fcn_00534c40(a1, 0x6a42c8, 4, 0x6ac340, 0x6ac300,
	                           0x6ac314, 0x6ac328);
	fcn_005350d0(f.win);
	fcn_00517c00(*(unsigned short*) (a0 + 0x27), 1, 2, f.numA);
	fcn_00517c00(*(unsigned short*) (a0 + 0x25), 1, 2, f.numB);
	p = fcn_0050dc90((int) a0);
	if (p == 0) {
		strcpy(f.txtName, *(char**) 0x14abc28);
	} else {
		fcn_00517c00(*(unsigned short*) p, 1, 1, f.txtName);
	}
	d2_SetForm(*(int*) (f.win + 0x228), 3);
	io_AppendText((char*) 0x68beac);
	io_AppendText((char*) 0x6ac33c);
	f.hE = fcn_00472250(*(int*) (f.win + 0x228), 3,
	                    io_AppendText((char*) 0x1a20));
	d2_SetForm(*(int*) (f.win + 0x228), 3);
	for (i = 0; i < 4; i++) {
		d2_SetForm(*(int*) (f.win + 0x228 + i * 4), 1);
		io_AppendText((char*) 0x1a1d);
		if (i == 0) {
			d2_SetForm(*(int*) (f.win + 0x228), 5);
		} else {
			d2_SetForm(*(int*) (f.win + 0x228 + i * 4), 4);
		}
		io_AppendText((char*) 0x6a2310, (char*) 0x1a37, i + 1);
	}
	d2_SetForm(*(int*) (f.win + 0x230), 3);

	n = *(int*) 0x772514 * 0x3cc;
	f.tv3 = *(int*) (0x1015f4c + n) / 2;
	f.tv2 = *(int*) (0x1015f50 + n) / 2;
	for (i = 0; i < 12; i++) {
		f.rows[i].obj = 0;
		f.rows[i].icon = -1;
	}

	f.pIt = (int*) (f.win + 0x22c);
	f.cnt = 0;
	f.pg = 1;
	i = 0;
	for (;;) {
		if ((int) (f.ent[0x232] + f.ent[0x231]) <= i) {
			break;
		}
		if (f.cnt / 2 >= 2) {
			f.cnt = 0;
			f.pg++;
			f.pIt++;
			if (f.pg > 3) {
				break;
			}
		}
		d2_SetForm(*f.pIt, 3);
		f.rows[i].win = *f.pIt;
		f.tv = f.cnt % 2 * f.tv3 + 0x10;
		f.rows[i].x = f.tv;
		f.rows[i].y = f.cnt / 2 * f.tv2 + 0x11;
		f.tv = f.tv + 0x18;
		f.rows[i].icon = fcn_0046f740(f.tv, f.rows[i].y, 0x5db,
		                              *(int*) 0x772514);
		if (i == 0) {
			f.hRadio = fcn_004693b0(1, f.rows[i].icon);
		} else {
			fcn_00469470(f.hRadio, f.rows[i].icon);
		}
		f.tv -= 0x36;
		f.rows[i].label = fcn_0046fac0(f.tv, f.rows[i].y - 0x11,
		                               *(char**) 0x14abc28,
		                               *(int*) 0x772514);
		GUI(f.rows[i].icon).f5c = 1;
		GUI(f.rows[i].label).w = 0xa0;
		GUI(f.rows[i].label).f6c = 1;
		f.rows[i].value = fcn_0046fac0(f.tv, f.rows[i].y + 0x44,
		                               (char*) 0x6b5c60,
		                               *(int*) 0x772514);
		f.rows[i].obj = 0;
		GUI(f.rows[i].value).w = 0xa0;
		GUI(f.rows[i].value).f6c = 1;
		f.rows[i].x1c = -1;
		f.rows[i].bar = -1;
		for (n = 0; n < 6; n++) {
			f.rows[i].a[n] = -1;
		}
		i++;
		f.cnt++;
		if (i >= 12) {
			break;
		}
	}
	f.cnt = i;

	d2_SetOverlayAnimation(0, 0);
	while (fcn_005373e0((void*) 0x5b7880, 0x677c7)) {
		if (*(int*) 0x14ce8e0) {
			*(int*) 0x774654 = 1;
		}
		fcn_005350d0(f.win);
		fcn_00534c20(f.win);
		if (*(unsigned char*) 0x14cf950 == 0xcd) {
			fcn_00535550(f.win);
		}
		if (*(unsigned char*) 0x14cf950 == 0xcb) {
			fcn_00535560(f.win);
		}
		if (*(char*) (f.win + 0x270)) {
			goto L7e3d;
		}
		if (*(int*) 0x100f1dc != -1 && *(int*) 0x67d370 == f.hE
		    && f.nSlots != 0) {
			n = fcn_005b5750();
			if (n == 0) {
				goto L7e3d;
			}
			perRow = n / f.nSlots;
			y = perRow / 3;
			if (fcn_00526010(
			        (void*) (0x7f4ca0
			                 + *(unsigned short*) 0x774970 * 0x21c),
			        fcn_0050b750(n, *(unsigned char*) 0x773d75),
			        *(unsigned char*) 0x773d75)) {
				f.pIt = (int*) &f.rows[0].obj;
				f.pg = f.cnt;
				while (f.pg > 0) {
					p = (char*) *f.pIt;
					if (p != 0) {
						fcn_004c4eb0(0x6ac2bc);
						fcn_004c5150(
						    *(int*) (p + 4), -1,
						    *(unsigned char*) 0x773d75,
						    fcn_0050b750(
						        perRow,
						        *(unsigned char*)
						            0x773d75));
						fcn_004c54c0(
						    *(int*) (0x7f4ca4
						             + *(unsigned short*)
						                   0x774970
						                   * 0x21c),
						    *(int*) (p + 4), y, 0);
						fcn_004c4ef0(0x6ac2bc);
					}
					f.pIt = (int*) ((char*) f.pIt + 0x5c);
					f.pg--;
				}
			}
			fcn_004c5150(
			    -1,
			    *(int*) (0x7f4ca4
			             + *(unsigned short*) 0x774970 * 0x21c),
			    *(unsigned char*) 0x773d75,
			    fcn_0050b750(n, *(unsigned char*) 0x773d75));
		}
	L7e3d:
		n = f.cnt;
		for (i = 0; i < 0x114; i++) {
			((int*) f.old)[i] = ((int*) f.rows)[i];
		}
		if (n > 0) {
			for (i = 0; i < n; i++) {
				f.rows[i].obj = 0;
			}
		}
		f.nSlots = fcn_00505d00((unsigned char*) a0, f.slots);
		for (i = 0; i < 12; i++) {
			entityId = f.slots[0x19 + i];
			if (entityId == 0xffff) {
				continue;
			}
			p = (char*) (0x7f4ca0 + entityId * 0x21c);
			if (*(char*) (0x7f4e04 + entityId * 0x21c) != 0) {
				continue;
			}
			for (y = 0; y < n; y++) {
				if (f.rows[y].obj == (unsigned char*) p) {
					break;
				}
			}
			if (y < n) {
				continue;
			}
			for (y = 0; y < n; y++) {
				if (f.rows[y].obj == 0) {
					f.rows[y].obj = (unsigned char*) p;
					break;
				}
			}
		}
		if (f.cnt > 0) {
			f.pg = f.cnt;
			i = 0;
			while (f.pg > 0) {
				if (f.rows[i].obj != f.old[i].obj) {
					if (f.rows[i].x1c != -1) {
						fcn_0046b2b0(f.rows[i].x1c);
						f.rows[i].x1c = -1;
					}
					if (f.rows[i].bar != -1) {
						fcn_0046b2b0(f.rows[i].bar);
						f.rows[i].bar = -1;
					}
					for (y = 0; y < 6; y++) {
						if (f.rows[i].a[y] != -1) {
							fcn_0046b2b0(
							    f.rows[i].a[y]);
							f.rows[i].a[y] = -1;
						}
					}
				}
				i++;
				f.pg--;
			}
		}

		f.pg = (int) fcn_005463a0(2, 0, 6, 3, *(int*) (a0 + 1));
		f.pIt = (int*) (f.pg + 0xb0);
		f.tv3 = n;
		i = 0;
		if (n > 0) {
			r = f.rows;
			do {
				if (r->obj != 0) {
					if (r->x1c == -1) {
						d2_SetForm(r->win, 3);
						r->x1c = fcn_0046f740(
						    r->x + 0x1a, r->y,
						    *(int*) (r->obj + 0x18c),
						    *(int*) 0x772514);
						fcn_00517c00(
						    *(unsigned short*) r->obj, 1,
						    1, f.txtNum);
						fcn_0046f940(r->label, f.txtNum);
						GUI(r->label).f6c = 1;
						GUI(r->label).w = 0xa0;
						r->bar = fcn_004677e0(
						    r->x + 0xc, r->y + 0x32, 0x40,
						    0, 0x64, 0x75, 0x42,
						    *(int*) 0x772514);
						r->state = 1;
						GUI(r->bar).f4c = 1;
					}
					if (r->bar != -1) {
						f.tv = fcn_0050f950(
						    *(unsigned short*) 0x774970,
						    *(unsigned short*) r->obj);
						percent = (f.tv + 128.0) * 100.0;
						fcn_00472380(
						    r->bar, 0, 0x64,
						    (int) (percent * 0.00392156862745098));
					}
				} else if (f.pg != 0
				           && ((char*) f.pg)[0xac] == 0x13
				           && *f.pIt != 0) {
					strcpy(f.txtWorker,
					       *(char**) 0x14abbb0);
					r->state = 2;
					fcn_0046f940(r->label, f.txtWorker);
					GUI(r->label).w = 0xa0;
					GUI(r->label).h = 0x28;
				} else {
					if (r->x1c != -1) {
						fcn_0046b2b0(r->x1c);
						r->x1c = -1;
					}
					if (r->bar != -1) {
						fcn_0046b2b0(r->bar);
						r->bar = -1;
					}
					for (y = 0; y < 6; y++) {
						if (r->a[y] != -1) {
							fcn_0046b2b0(r->a[y]);
							r->a[y] = -1;
						}
					}
					strcpy(f.txtDefault,
					       *(char**) 0x14abc28);
					r->state = 0;
					fcn_0046f940(r->label, f.txtDefault);
					GUI(r->label).w = 0xa0;
					GUI(r->label).h = 0x28;
					fcn_0046f940(r->value,
					             (char*) 0x6b5c60);
				}
				r++;
				f.pIt++;
				f.tv3--;
			} while (f.tv3 != 0);
		}

		if (f.hB != -1 && f.hA != -1 && f.rows[f.hA].obj == 0) {
			f.hA = -1;
			f.hB = -1;
			f.hC = -1;
			f.hD = -1;
			for (i = 0; i < 3; i++) {
				d2_SetForm(*(int*) (f.win + 0x228 + i * 4), 2);
				io_AppendText((char*) 0x6811b0);
			}
		}
		if (*(int*) 0x100f1dc == -1) {
			goto L870d;
		}
		for (i = 0; i < 12; i++) {
			if (f.rows[i].icon != *(int*) 0x67d370) {
				continue;
			}
			for (y = 0; y < 3; y++) {
				d2_SetForm(*(int*) (f.win + 0x228 + y * 4), 2);
				io_AppendText((char*) 0x6811b0);
			}
			f.hA = i;
			f.hB = -1;
			f.hC = -1;
			f.hD = -1;
			if (f.rows[i].obj == 0) {
				n = (int) fcn_005101e0(
				    (unsigned char*) (0x7f4ca0
				                      + *(unsigned short*) (a0 + 0x27)
				                            * 0x21c),
				    a0[0], -1, 1);
				d2_SetForm(f.rows[i].win, 2);
				f.hC = fcn_00472250(f.rows[i].win, 2,
				                    io_AppendText(
				                        (char*) 0x1a22, n,
				                        (char*) 0x220));
			} else if (f.rows[i].state == 1) {
				d2_SetForm(f.rows[i].win, 2);
				io_AppendText((char*) 0x6811b0);
				f.hB = fcn_00472250(
				    f.rows[i].win, 2,
				    io_AppendText(
				        (char*) 0x1a21,
				        *(unsigned short*) f.rows[i].obj));
				if (*(unsigned char*) (f.rows[i].obj + 0x165)
				    == f.ent[0x230]) {
					f.hD = fcn_00472250(
					    f.rows[i].win, 2,
					    io_AppendText(
					        (char*) 0x1a25,
					        *(unsigned short*) f.rows[i].obj));
				}
			}
		}
		if (*(int*) 0x67d370 == f.hC && f.hA != -1) {
			p = (char*) fcn_005463a0(2, 0, 6, 3,
			                         *(int*) (a0 + 1));
			if (p != 0) {
				*(int*) (p + 0xb0 + f.hA * 4) = 1;
			} else {
				memset(&f.msg, 0, 0xf8);
				f.msg.f0c = *(int*) (a0 + 1);
				f.msg.type = 6;
				f.msg.b36 = 1;
				f.msg.f30 = *(int*) 0x7f4c08;
				f.msg.f08 = *(int*) (0x7f4ca4
				                     + *(unsigned short*) 0x774970
				                           * 0x21c);
				f.msg.f28 = *(int*) 0x7f4c00;
				f.msg.f2c = *(int*) 0x7f4c04;
				f.msg.w34 = *(short*) 0x7f4c0c;
				f.msg.f5c[f.hA] = 1;
				if (fcn_00505370((char*) a0) != 0) {
					f.msg.f8c = -1;
				} else {
					f.msg.f8c = *(int*) (*(int*) 0x7746cc
					                     + 2);
				}
				f.msg.b59 = 0;
				f.msg.b58 = 0x13;
				fcn_004c5530(&f.msg);
			}
			f.hA = -1;
			for (i = 0; i < 3; i++) {
				d2_SetForm(*(int*) (f.win + 0x228 + i * 4), 2);
				io_AppendText((char*) 0x6811b0);
			}
			goto L870d;
		}
		if (*(int*) 0x67d370 == f.hB && f.hA != -1) {
			if (fcn_00526120(*(char**) 0x14abbf8, 1) != 0) {
				for (i = 0; i < 3; i++) {
					d2_SetForm(
					    *(int*) (f.win + 0x228 + i * 4), 2);
					io_AppendText((char*) 0x6811b0);
				}
				memset(&f.msg, 0, 0xf8);
				f.msg.type = 0x31;
				f.msg.b36 = 1;
				f.msg.f08 = *(int*) (0x7f4ca4
				                     + *(unsigned short*) 0x774970
				                           * 0x21c);
				f.msg.f0c = *(int*) (a0 + 1);
				f.msg.f28 = *(int*) 0x7f4c00;
				f.msg.f2c = *(int*) 0x7f4c04;
				f.msg.f30 = *(int*) 0x7f4c08;
				f.msg.w34 = *(short*) 0x7f4c0c;
				*(int*) &f.msg.b58 = *(int*) (f.rows[f.hA].obj + 4);
				fcn_004c5530(&f.msg);
				f.hA = -1;
			}
			goto L870d;
		}
		if (*(int*) 0x67d370 == f.hD && f.hA != -1) {
			p = (char*) f.rows[f.hA].obj;
			if (*(int*) (p + 0x174) < 4) {
				fcn_0051af00(f.text, (char*) 0x1a27, 4);
				fcn_00526120(f.text, 0);
			} else {
				memset(&f.msg, 0, 0xf8);
				f.msg.type = 0x32;
				f.msg.b36 = 2;
				f.msg.f08 = *(int*) (0x7f4ca4
				                     + *(unsigned short*) 0x774970
				                           * 0x21c);
				f.msg.f0c = *(int*) (a0 + 1);
				f.msg.f28 = *(int*) 0x7f4c00;
				f.msg.f2c = *(int*) 0x7f4c04;
				f.msg.f30 = *(int*) 0x7f4c08;
				f.msg.w34 = *(short*) 0x7f4c0c;
				*(int*) &f.msg.b58 = *(int*) (p + 4);
				fcn_004c5530(&f.msg);
				f.hA = -1;
			}
		}
	L870d:
		;
	}

	if (f.hRadio != -1) {
		fcn_00469510(f.hRadio);
	}
	fcn_00534f30(f.win);
	fcn_00532ef0();
}
