#include <string.h>

/*
 * Personnel book window builder.
 *
 * Creates the book window, builds the four header labels, up to twelve
 * worker-slot rows (0x5c-byte gauge records) laid out four per page over
 * three pages, refreshes the row controls for the open record, then runs the
 * shared message loop. Every selection sends the packet-builder operations for
 * the clicked slot. Closes the window and hands the tail to fcn_00532ef0.
 *
 * Bar scale uses the compiler-literal doubles 0x666088 (128.0), 0x662c38
 * (100.0) and 0x665388 (1.0/255.0) through named externs: the pointer-cast
 * dereference forces an 8-byte aligned EBP frame and breaks the prologue.
 * Remaining gap: the frame is 0x1360, not 0x1368. Evidence: .scratch/5b88b0/.
 */

typedef struct
{
	int x;
	int y;
	unsigned char* obj;
	int icon;
	int bar;
	int label;
	int value;
	int x1c;
	unsigned char state;
	char pad21[0x28 - 0x21];
	int a[6];
	int b[6];
	int win;
} Row;
/* SIZE 0x5c */

typedef struct
{
	char pad0[0x18];
	int w;
	int h;
	char pad20[0x4c - 0x20];
	int f4c;
	char pad50[0x5c - 0x50];
	int f5c;
	char pad60[0x6c - 0x60];
	int f6c;
	char pad70[0x2f4 - 0x70];
} Ctl;
/* SIZE 0x2f4 */

#define GUI(i) (((Ctl*) *(void**) 0x1015ea0)[i])

void* __cdecl fcn_00534c40(unsigned int, int, char, ...);
void __cdecl fcn_005350d0(char*);
void __cdecl fcn_00534c20(char*);
int __cdecl fcn_00517c00(int, int, int, char*);
char* __cdecl fcn_0050dc90(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char*, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_005b58a0(int, int, Row*);
int __cdecl d2_ShowTxt(int, int, char*, int);
int __cdecl fcn_005b5eb0(int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_005b6130(int, char*);
void __cdecl fcn_00535550(char*);
void __cdecl fcn_00535560(char*);
int __cdecl fcn_005b8760(void);
int __cdecl fcn_0050b750(int, int);
int __cdecl fcn_00526010(void*, int, int);
void __cdecl fcn_004c4eb0(int);
void __cdecl fcn_004c5150(int, int, char, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_004c4ef0(int);
void __cdecl fcn_005b59c0(unsigned char*, Row*, int);
void __cdecl fcn_005b5c70(Row*);
float __cdecl fcn_005101e0(unsigned char*, int, int, int);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00505d00(unsigned char*, int*);
void __cdecl fcn_0046b2b0(int);
void* __cdecl fcn_005463a0(int, ...);
void* __cdecl he_fn_Handlung(void);
int __cdecl fcn_0050f950(int, int);
void __cdecl fcn_0046f940(int, const char*);
extern double dbl_128_0;
extern double dbl_100_0;
extern double dbl_0_00392156862745098;
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl d2_SetElementValue(int, ...);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00534f30(char*);
void __cdecl fcn_00532ef0(void);
float __cdecl fcn_004ff210(unsigned short, int);
void __cdecl fcn_0051af00(char*, char*, ...);
int __cdecl gm_CheckEntityType(int);
int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl fcn_00469470(int, int);

/* ADDRESS: GOLDTL 0x005b88b0 */
void __cdecl fcn_005b88b0(char* a0, int a1)
{
	int cnt;
	int pg;
	int* pIt;
	char* win;
	int hA;
	int sel;
	int tv;
	int tv2;
	int tv3;
	int hB;
	int hC;
	unsigned char* ent;
	int nSlots;
	int hD;
	int hE;
	Row gage;
	char pkt[0x100];
	Row rows[12];
	char txtName[0x60];
	char txtNum[0x80];
	char txtWorker[0x80];
	char txtDefault[0x80];
	int slots[0x26];
	char numA[0x60];
	char numB[0x60];
	char textA[0x200];
	char textB[0x400];
	Row old[12];
	int i;
	int ret;
	char* p;
	Row* r;

	cnt = 0;
	ent = (unsigned char*) (*(void**) 0x868050) + *(unsigned char*) a0 * 0x24d;
	hA = -1;
	sel = -1;
	hB = -1;
	hC = -1;
	hD = -1;

	win = (char*) fcn_00534c40(a1, 0x6a42c8, 4, 0x6ac340, 0x6ac300, 0x6ac314,
	                          0x6ac328);
	fcn_005350d0(win);
	fcn_00517c00(*(unsigned short*) (a0 + 0x27), 1, 2, numA);
	fcn_00517c00(*(unsigned short*) (a0 + 0x25), 1, 2, numB);
	p = fcn_0050dc90((int) a0);
	if (p == 0) {
		strcpy(txtName, *(char**) 0x14abc28);
	} else {
		fcn_00517c00(*(unsigned short*) p, 1, 1, txtName);
	}

	d2_SetForm(*(int*) (win + 0x228), 3);
	io_AppendText((char*) 0x68beac);
	io_AppendText((char*) 0x6ac33c);
	hE = fcn_00472250(*(int*) (win + 0x228), 3,
	                  io_AppendText((char*) 0x413e));
	d2_SetForm(*(int*) (win + 0x228), 3);
	for (i = 0; i < 4; i++) {
		d2_SetForm(*(int*) (win + 0x228 + i * 4), 1);
		io_AppendText((char*) 0x413d);
		if (i == 0) {
			d2_SetForm(*(int*) (win + 0x228), 5);
		} else {
			d2_SetForm(*(int*) (win + 0x228 + i * 4), 4);
		}
		io_AppendText((char*) 0x6a2310, (char*) 0x4143, i);
	}
	d2_SetForm(*(int*) (win + 0x230), 3);

	tv3 = *(int*) (0x1015f4c + *(int*) 0x772514 * 0x3cc) / 2;
	tv2 = *(int*) (0x1015f50 + *(int*) 0x772514 * 0x3cc) / 2;

	for (i = 0; i < 12; i++) {
		rows[i].obj = 0;
		rows[i].icon = -1;
	}

	pIt = (int*) (win + 0x22c);
	cnt = 0;
	pg = 1;
	i = 0;
	for (;;) {
		if ((int) (ent[0x232] + ent[0x231]) <= i) {
			break;
		}
		if (cnt / 2 >= 2) {
			cnt = 0;
			pg++;
			pIt++;
			if (pg > 3) {
				break;
			}
		}
		d2_SetForm(3, *pIt);
		tv = cnt % 2 * tv3 + 0x10;
		rows[i].win = *pIt;
		rows[i].x = tv;
		rows[i].y = cnt / 2 * tv2 + 0x11;
		tv = tv + 0x18;
		rows[i].icon = fcn_0046f740(tv, rows[i].y, 0x5db, *(int*) 0x772514);
		if (i == 0) {
			hB = d2_CreateRadioGroup(1, rows[i].icon);
		} else {
			fcn_00469470(hB, rows[i].icon);
		}
		tv -= 0x36;
		rows[i].label = d2_ShowTxt(tv, rows[i].y - 0x11,
		                           *(char**) 0x14abc28, *(int*) 0x772514);
		GUI(rows[i].icon).f5c = 1;
		GUI(rows[i].label).w = 0xa0;
		GUI(rows[i].label).f6c = 1;
		r = &rows[i];
		rows[i].value = d2_ShowTxt(tv, r->y + 0x44, (char*) 0x6b5c60,
		                           *(int*) 0x772514);
		rows[i].obj = 0;
		GUI(rows[i].value).w = 0xa0;
		GUI(rows[i].value).f6c = 1;
		rows[i].x1c = -1;
		rows[i].bar = -1;
		rows[i].a[0] = -1;
		rows[i].a[1] = -1;
		rows[i].a[2] = -1;
		rows[i].a[3] = -1;
		rows[i].a[4] = -1;
		rows[i].a[5] = -1;
		i++;
		cnt++;
		if (i >= 12) {
			break;
		}
	}

	tv2 = i;
	d2_SetForm(*(int*) (win + 0x228), 3);
	fcn_005b58a0(*(int*) (*(int*) 0x77255c + 0xc) / 2 - 0x18, 0x20, &gage);
	cnt = d2_ShowTxt(gage.x, gage.y - 0x20, *(char**) 0x14abbd4,
	                 *(int*) 0x772514);
	GUI(cnt).f6c = 1;
	GUI(cnt).w = 0x64;
	fcn_005b5eb0((int) win, a0);
	d2_SetOverlayAnimation(0, 0);

	while (fcn_005373e0((void*) 0x5b88b0, 0x677c7)) {
		if (*(int*) 0x14ce8e0) {
			*(int*) 0x774654 = 1;
		}
		fcn_005350d0(win);
		fcn_00534c20(win);
		fcn_005b6130((int) win, a0);
		if (*(char*) 0x14cf950 == 0xcd) {
			fcn_00535550(win);
		}
		if (*(char*) 0x14cf950 == 0xcb) {
			fcn_00535560(win);
		}
		if (*(char*) (win + 0x270)) {
			goto packet2;
		}
		if (*(int*) 0x100f1dc != -1 && *(int*) 0x67d370 == hE && nSlots != 0
		    && (ret = fcn_005b8760()) != 0) {
			tv = ret / nSlots;
			tv2 = tv % 3;
			tv3 = fcn_0050b750(ret, *(unsigned char*) 0x773d75);
			if (fcn_00526010((void*) (0x7f4ca0
			                          + *(unsigned short*) 0x774970 * 0x21c),
			                 tv3, *(unsigned char*) 0x773d75)) {
				for (i = 0; i < nSlots; i++) {
					if (rows[i].obj == 0) {
						continue;
					}
					fcn_004c4eb0(0x6ac2bc);
					fcn_0050b750(tv, *(unsigned char*) 0x773d75);
					fcn_004c5150(*(int*) (rows[i].obj + 4), -1,
					             *(unsigned char*) 0x773d75, tv3);
					fcn_004c54c0(*(int*) (rows[i].obj + 4), tv2, 0,
					             *(int*) (0x7f4ca4
					                      + *(unsigned short*) 0x774970
					                            * 0x21c));
					fcn_004c4ef0(0x6ac2bc);
				}
			}
			fcn_004c5150(fcn_0050b750(ret, *(unsigned char*) 0x773d75), -1,
			             *(unsigned char*) 0x773d75,
			             *(int*) (0x7f4ca4
			                      + *(unsigned short*) 0x774970 * 0x21c));
		}
		p = fcn_0050dc90((int) a0);
		if (p != 0) {
			if (*(unsigned short*) p != *(unsigned short*) 0x774970) {
				if (p[8] == 0) {
					goto clear_gage;
				}
				if (gage.x1c != -1) {
					goto keep_gage;
				}
				fcn_005b59c0((unsigned char*) p, &gage, 0);
				goto after_gage;
			}
		}
keep_gage:
		if (p != 0 && p[8] != 0) {
			goto after_gage;
		}
clear_gage:
		if (gage.x1c != -1) {
			gage.y = 0;
			fcn_005b5c70(&gage);
			hA = -1;
		}
after_gage:
		if (*(int*) 0x100f1dc != -1 && *(int*) 0x67d370 == gage.icon
		    && gage.icon != -1) {
			for (i = 0; i < 3; i++) {
				d2_SetForm(2, *(int*) (win + 0x228 + i * 4));
				io_AppendText((char*) 0x6811b0);
			}
			hA = -1;
			sel = cnt;
			if (gage.obj == 0 && gage.state != 2) {
				d2_SetForm(gage.win, 2);
				hD = fcn_00472250(gage.win, 2,
				                  io_AppendText((char*) 0x1a22,
				                                (int) fcn_005101e0(
				                                    (unsigned char*) a0, a0[0],
				                                    0, -1),
				                                ent[0x223] + 0x130));
			}
			if (gage.state == 1) {
				fcn_005b59c0((unsigned char*) p, &gage, 0);
				hB = fcn_00472250(gage.win, 2,
				                  io_AppendText((char*) 0x1a21,
				                                *(unsigned short*) p));
			}
		}
		if (*(int*) 0x100f1dc == -1) {
			goto after2;
		}
		if (*(int*) 0x67d370 != hD || gage.obj != 0) {
			goto packet2;
		}
		p = (char*) fcn_005463a0(2, 0, 6, 3, *(int*) (a0 + 1));
		if (p != 0) {
			if (p[0xac] == 0) {
				goto packet2;
			}
			for (;;) {
				p = (char*) he_fn_Handlung();
				if (p == 0) {
					break;
				}
				if (p[0xac] == 0) {
					goto packet2;
				}
			}
		}
		memset(pkt, 0, 0xf8);
		*(int*) (pkt + 0x0c) = *(int*) (a0 + 1);
		*(unsigned char*) (pkt + 4) = 7;
		*(unsigned char*) (pkt + 0x36) = 1;
		*(int*) (pkt + 0x30) = *(int*) 0x7f4c08;
		*(int*) (pkt + 0x5c) = 1;
		*(int*) (pkt + 8) = *(int*) (0x7f4ca4
		                             + *(unsigned short*) 0x774970 * 0x21c);
		*(int*) (pkt + 0x28) = *(int*) 0x7f4c00;
		*(int*) (pkt + 0x2c) = *(int*) 0x7f4c04;
		*(unsigned short*) (pkt + 0x34) = *(unsigned short*) 0x7f4c0c;
		if (gm_CheckEntityType((int) a0)) {
			*(int*) (pkt + 0x5c) = -1;
		} else {
			*(int*) (pkt + 0x5c) = *(int*) (*(int*) 0x7746cc + 2);
		}
		*(unsigned char*) (pkt + 0x58) = 0;
		fcn_004c5530(pkt);
		fcn_0051af00(textA, (char*) 0x1939, ent[0x223] + 0x130);
		fcn_00526120(textA, 0);

packet2:
		if (*(int*) 0x100f1dc == -1 || *(int*) 0x67d370 != hE) {
			goto after2;
		}
		if (gage.obj == 0) {
			goto after2;
		}
		if (fcn_00526120(*(char**) 0x14abbf8, 1) == 0) {
			goto after2;
		}
		for (i = 0; i < 3; i++) {
			d2_SetForm(2, *(int*) (win + 0x228 + i * 4));
			io_AppendText((char*) 0x6811b0);
		}
		memset(pkt, 0, 0xf8);
		*(unsigned char*) (pkt + 4) = 0x31;
		*(unsigned char*) (pkt + 0x36) = 1;
		*(int*) (pkt + 0x0c) = *(int*) (a0 + 1);
		*(int*) (pkt + 8) = *(int*) (0x7f4ca4
		                             + *(unsigned short*) 0x774970 * 0x21c);
		*(int*) (pkt + 0x28) = *(int*) 0x7f4c00;
		*(int*) (pkt + 0x2c) = *(int*) 0x7f4c04;
		*(unsigned short*) (pkt + 0x34) = *(unsigned short*) 0x7f4c0c;
		*(int*) (pkt + 0x30) = *(int*) 0x7f4c08;
		*(int*) (pkt + 0x5c) = *(int*) (gage.obj + 4);
		fcn_004c5530(pkt);
		for (i = 0; i < 3; i++) {
			d2_SetForm(2, *(int*) (win + 0x228 + i * 4));
			io_AppendText((char*) 0x6811b0);
		}
		hA = -1;
		hC = -1;
		sel = -1;

after2:
		for (i = 0; i < 0x114; i++) {
			((int*) old)[i] = ((int*) rows)[i];
		}
		for (i = 0; i < tv2; i++) {
			rows[i].obj = 0;
		}
		nSlots = fcn_00505d00((unsigned char*) a0, slots);
		for (i = 0; i < 12; i++) {
			if (slots[0xd + i] == 0xffff) {
				continue;
			}
			r = (Row*) (0x7f4ca0 + slots[0xd + i] * 0x21c);
			if (*(char*) (0x7f4e04 + slots[0xd + i] * 0x21c) != 0) {
				continue;
			}
			for (tv = 0; tv < tv2; tv++) {
				if (rows[tv].obj == (unsigned char*) r) {
					break;
				}
			}
			if (tv < tv2) {
				continue;
			}
			for (tv = 0; tv < tv2; tv++) {
				if (rows[tv].obj == 0) {
					rows[tv].obj = (unsigned char*) r;
					break;
				}
			}
		}
		for (i = 0; i < tv2; i++) {
			if (rows[i].obj == old[i].obj) {
				continue;
			}
			if (rows[i].x1c != -1) {
				fcn_0046b2b0(rows[i].x1c);
				rows[i].x1c = -1;
			}
			if (rows[i].bar != -1) {
				fcn_0046b2b0(rows[i].bar);
				rows[i].bar = -1;
			}
			for (tv = 0; tv < 6; tv++) {
				if (rows[i].a[tv] != -1) {
					fcn_0046b2b0(rows[i].a[tv]);
					rows[i].a[tv] = -1;
				}
			}
		}
		p = (char*) fcn_005463a0(2, 0, 6, 3, *(int*) (a0 + 1));
		pIt = (int*) (p + 0xb0);
		hC = tv2;
		i = 0;
		if (tv2 > 0) {
			tv3 = tv2;
			r = rows;
			do {
				if (r->obj != 0) {
					if (r->x1c == -1) {
						d2_SetForm(r->win, 3);
						r->x1c = fcn_0046f740(
						    r->x + 0x1a, r->y,
						    *(int*) (r->obj + 0x18c),
						    *(int*) 0x772514);
						fcn_00517c00(*(unsigned short*) r->obj, 1, 1,
						             txtNum);
						fcn_0046f940(r->label, txtNum);
						GUI(r->label).f6c = 1;
						GUI(r->label).w = 0xa0;
						r->value = fcn_004677e0(
						    r->x + 0xc, r->y + 0x32, 0x40, 0, 0x64,
						    0x75, 0x42, *(int*) 0x772514);
						r->state = 1;
						GUI(r->value).f4c = 1;
					}
					if (r->bar != -1) {
						tv = fcn_0050f950(
						    *(unsigned short*) r->obj,
						    *(unsigned short*) 0x774970);
						d2_SetElementValue(
						    r->bar, 0, 0x64,
						    (int) ((tv + dbl_128_0) * dbl_0_00392156862745098
						           * dbl_100_0));
					}
				} else if (p != 0 && p[0xac] == 0x13
				           && *pIt != 0) {
					strcpy(txtWorker, *(char**) 0x14abbb0);
					r->state = 2;
					fcn_0046f940(r->label, txtWorker);
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
					for (tv = 0; tv < 6; tv++) {
						if (r->a[tv] != -1) {
							fcn_0046b2b0(r->a[tv]);
							r->a[tv] = -1;
						}
					}
					strcpy(txtDefault, *(char**) 0x14abc28);
					fcn_0046f940(r->label, txtDefault);
					GUI(r->label).w = 0xa0;
					GUI(r->label).h = 0x28;
					fcn_0046f940(r->value, (char*) 0x6b5c60);
				}
				r++;
				pIt++;
				tv3--;
			} while (tv3);
		}
		if (hA != -1 && sel != -1 && rows[sel].obj == 0) {
			hA = -1;
			sel = -1;
			for (i = 0; i < 3; i++) {
				d2_SetForm(2, *(int*) (win + 0x228 + i * 4));
				io_AppendText((char*) 0x6811b0);
			}
		}
		if (*(int*) 0x100f1dc != -1) {
			for (i = 0; i < 12; i++) {
				if (rows[i].icon != *(int*) 0x67d370) {
					continue;
				}
				for (tv = 0; tv < 3; tv++) {
					d2_SetForm(2, *(int*) (win + 0x228 + tv * 4));
					io_AppendText((char*) 0x6811b0);
				}
				hA = -1;
				sel = i;
				if (rows[i].obj != 0 && rows[i].state == 1) {
					d2_SetForm(2, rows[i].win);
					io_AppendText((char*) 0x6811b0);
					hA = fcn_00472250(
					    rows[i].win, 2,
					    io_AppendText((char*) 0x413f,
					                  *(unsigned short*) rows[i].obj));
				}
			}
			if (*(int*) 0x67d370 == hA && sel != -1) {
				fcn_0051af00(textB, (char*) 0x4140,
				             *(unsigned short*) rows[sel].obj);
				if (fcn_00526120(textB, 1) != 0) {
					for (i = 0; i < 3; i++) {
						d2_SetForm(2, *(int*) (win + 0x228 + i * 4));
						io_AppendText((char*) 0x6811b0);
					}
					fcn_004ff210(*(unsigned short*) rows[sel].obj, -1000);
					sel = -1;
				}
			}
		}
	}

	if (hD != -1) {
		fcn_00469510(hD);
	}
	fcn_00534f30(win);
	fcn_00532ef0();
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")

