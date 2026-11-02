/*
 * Family tree window builder.
 *
 * Opens the tree view window and prepares the root entity: the window handle,
 * the tree mode, the title string and the graphics state are set up before the
 * walk over the family records starts. The body then draws the collected
 * records and pumps the modal window until the caller's callback returns 0.
 *
 * Native body 0x5d0660..0x5d1785 (0x1125 bytes). The frame is one 0x438
 * allocation, the four callee-saved registers are saved after the two
 * early exits, and the record tables are 16-byte entries cleared to -1.
 *
 * Open gaps: the frame comes out 8 bytes short (two native slots stay in
 * registers here), so the second immediate and the branch distances do not
 * agree yet. The hover block near the end still guesses at the native slot
 * use and the last three text passes map their positions approximately.
 */

#include <string.h>

extern int* g_772500;			/* 0x00772500 */
extern int g_772514;			/* 0x00772514 */
extern int g_100f1dc;			/* 0x0100f1dc */
extern char g_1015ea0[];		/* 0x01015ea0 */
extern int g_14ce8e0;			/* 0x014ce8e0 */
extern int g_774654;			/* 0x00774654 */
extern int g_67d370;			/* 0x0067d370 */
extern char g_7f4ca0[];			/* 0x007f4ca0 */

int __cdecl fcn_0057ec20(int);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl gm_LookupEntityRecordById(unsigned int);
void* __cdecl fcn_00470820(short, short, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(void*, ...);
void __cdecl fcn_00472e50(void);
int __cdecl fcn_0046f2c0(int, int);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_00472c30(int, int, int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_005c9090(char*, int, int, int, int);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_005d1790(void*, int);

typedef struct TreeRec {
	short id;			/* +0 */
	short f2;			/* +2 */
	int text;			/* +4 */
	short x;			/* +8 */
	short y;			/* +10 */
	int f12;			/* +12 */
} TreeRec;

/* ADDRESS: GOLDTL 0x005d0660 */
void __cdecl fcn_005d0660(unsigned int a0, unsigned char a1, int a2, unsigned int a3)
{
	char buf3[256];
	char buf2[256];
	char buf1[256];
	TreeRec tabC[5];
	TreeRec tabB[6];
	int posC[5];
	int posB[4];
	TreeRec tabA[2];
	int rows;
	int posY[2];
	int win;
	int count;
	int posX[2];
	int flag;
	int rows2;
	int nc;
	int w;
	int ent;
	int h;
	int n3;
	int nb;
	int idx;
	int t0;
	int hid;
	int rec;
	/* Address-taken keepalives: the native frame keeps two hover-state
	 * slots in memory. These hold those slots while hid/rec work the
	 * values in registers. */
	int keepHid;
	int keepRec;

	if (!fcn_0057ec20(1)) {
		return;
	}
	fcn_0057e880(6, 0, 0, 0);
	ent = gm_LookupEntityRecordById(a0);
	if (!ent) {
		return;
	}
	win = (int) fcn_00470820(0, 0, (char*) 0x6acab0);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(win);
	d2_SetForm(win, 2);
	io_AppendText(a2 ? (void*) a2 : (void*) 0x9f);
	d2_SetForm(win, 1);
	count = 1;
	g_100f1dc = -1;
	rows = *(int*) (0x1015f4c + g_772514 * 0x3cc);
	for (;;) {
		if (count) {
			rows2 = rows / 2;
			w = *(short*) ((char*) g_772500 + 0x1ec2c);
			h = *(short*) ((char*) g_772500 + 0x1ec2e);
			memset(tabA, 0xff, sizeof tabA);
			memset(tabB, 0xff, sizeof tabB);
			memset(tabC, 0xff, sizeof tabC);
			count = 0;
			nc = 0;
			nb = 0;
			flag = 0;
			t0 = 0;
			{
				char* er;
				char* rec;
				int id;
				int slot;
				int k;
				char* p;
				int col;
				int i;

				slot = 0;
				er = (char*) ent;
				tabB[2].id = *(short*) er;
				rec = (char*) gm_LookupEntityRecordById(
				    *(int*) (er + 0x5c));
				if (rec) {
					if (!(*(int*) (er + 0x1c8) & 0x40000)) {
						if (!(*(int*) (rec + 0x1c8) & 0x40000)) {
							flag = 1;
							tabB[3].id = *(short*) rec;
						}
					}
				}
				rec = (char*) gm_LookupEntityRecordById(
				    *(int*) (er + 0x64));
				if (rec) {
					tabA[1].id = *(short*) rec;
				}
				rec = (char*) gm_LookupEntityRecordById(
				    *(int*) (er + 0x60));
				if (rec) {
					tabA[0].id = *(short*) rec;
					p = rec + 0x68;
					idx = 3;
					if (nb < 6) {
						for (;;) {
							id = *(int*) p;
							if (id != -1) {
								if (id != *(int*) (er + 4)) {
									rec = (char*) gm_LookupEntityRecordById(id);
									if (rec) {
										tabB[slot].id = *(short*) rec;
										nb++;
										slot++;
										if (slot == 2) {
											slot = 4;
										}
									}
								}
							}
							p += 4;
							idx++;
							if (idx >= 8) {
								break;
							}
						}
					}
				}
				p = (char*) tabC;
				for (k = 3; k < 8; k++) {
					if (nc >= 5) {
						break;
					}
					id = *(int*) (er + 0x68 + (k - 3) * 4);
					if (id == -1) {
						continue;
					}
					rec = (char*) gm_LookupEntityRecordById(id);
					if (!rec) {
						continue;
					}
					if (*(unsigned char*) (rec + 2) >= 0xa) {
						continue;
					}
					*(short*) p = *(short*) rec;
					nc++;
					p += 0x10;
				}

				d2_SetForm(win, 1);
				fcn_00472e50();
				fcn_0046f2c0(g_772514, 1);
				i = rows2 - t0;
				tabA[0].text = fcn_0046f740(g_772514, 0x5db, 0xa,
				    i - 0x5a);
				n3 = t0 / 2;
				tabA[0].x = (short) ((rows2 - posY[0]) + n3 - 0x5a);
				tabA[0].y = 0xa;
				i = (rows2 - t0) - 0x58;
				if (tabA[0].id != -1) {
					id = tabA[0].id & 0xffff;
					col = fcn_0046f740(g_772514,
					    *(int*) (g_7f4ca0 + id * 0x21c + 0x18c),
					    0xc, i);
					tabA[0].text = col;
					*(int*) (g_1015ea0 + col * 756 + 0x1d0) = 3;
					*(int*) (g_1015ea0 + col * 756 + 0x2f0) =
					    (int) (g_7f4ca0 + id * 0x21c);
				} else {
					fcn_0046f740(g_772514, 0x4fb, 0xc, i);
					tabA[0].text = -1;
				}
				tabA[1].text = fcn_0046f740(g_772514, 0x5db, 0xa,
				    rows2 + 0x5a);
				tabA[1].x = (short) (n3 + rows2 + 0x5a);
				tabA[1].y = 0xa;
				i = rows2 + 0x5c;
				if (tabA[1].id != -1) {
					id = tabA[1].id & 0xffff;
					col = fcn_0046f740(g_772514,
					    *(int*) (g_7f4ca0 + id * 0x21c + 0x18c),
					    0xc, i);
					tabA[1].text = col;
					*(int*) (g_1015ea0 + col * 756 + 0x1d0) = 3;
					*(int*) (g_1015ea0 + col * 756 + 0x2f0) =
					    (int) (g_7f4ca0 + id * 0x21c);
				} else {
					fcn_0046f740(g_772514, 0x4fb, 0xc, i);
					tabA[1].text = -1;
				}

				if (flag) {
					col = fcn_0046f740(g_772514, 0x5db, 0x96,
					    (rows2 - t0) - 0x10);
					tabB[2].text = col;
					tabB[2].x = (short) (n3 + rows2 - 0x10);
					tabB[2].y = 0x96;
					i = (rows2 - t0) - 0xe;
					if (tabB[2].id != -1) {
						id = tabB[2].id & 0xffff;
						fcn_0046f740(g_772514,
						    *(int*) (g_7f4ca0 + id * 0x21c + 0x18c),
						    0x98, i);
						*(int*) (g_1015ea0 + col * 756 + 0x1d0) = 3;
						*(int*) (g_1015ea0 + col * 756 + 0x2f0) =
						    (int) (g_7f4ca0 + id * 0x21c);
					} else {
						fcn_0046f740(g_772514, 0x4fb, 0x98, i);
						tabB[2].text = -1;
					}
					col = fcn_0046f740(g_772514, 0x5db, 0x96,
					    rows2 + 0x10);
					tabB[3].text = col;
					tabB[3].x = (short) (n3 + rows2 + 0x10);
					tabB[3].y = 0x96;
					i = rows2 + 0x12;
					if (tabB[3].id != -1) {
						id = tabB[3].id & 0xffff;
						fcn_0046f740(g_772514,
						    *(int*) (g_7f4ca0 + id * 0x21c + 0x18c),
						    0x98, i);
						*(int*) (g_1015ea0 + col * 756 + 0x1d0) = 3;
						*(int*) (g_1015ea0 + col * 756 + 0x2f0) =
						    (int) (g_7f4ca0 + id * 0x21c);
					} else {
						fcn_0046f740(g_772514, 0x4fb, 0x98, i);
						tabB[3].text = -1;
					}
				} else {
					i = rows2 - n3;
					col = fcn_0046f740(g_772514, 0x5db, 0x96, i);
					tabB[2].text = col;
					tabB[2].x = (short) rows2;
					tabB[2].y = 0x96;
					i += 2;
					if (tabB[2].id != -1) {
						id = tabB[2].id & 0xffff;
						fcn_0046f740(g_772514,
						    *(int*) (g_7f4ca0 + id * 0x21c + 0x18c),
						    0x98, i);
						*(int*) (g_1015ea0 + col * 756 + 0x1d0) = 3;
						*(int*) (g_1015ea0 + col * 756 + 0x2f0) =
						    (int) (g_7f4ca0 + id * 0x21c);
					} else {
						fcn_0046f740(g_772514, 0x4fb, 0x98, i);
						tabB[2].text = -1;
					}
				}

				if (nb) {
					nb = rows / 10;
					posX[0] = nb + 0x10;
					posX[1] = (rows * 4) / 10 - w - 0x10;
					for (k = 0; k < 2; k++) {
						if (tabB[k].id == -1) {
							break;
						}
						col = fcn_0046f740(g_772514, 0x5db, 0x96,
						    posX[k]);
						tabB[k].text = col;
						tabB[k].y = 0x96;
						tabB[k].x = (short) (posY[k] + nc);
						id = tabB[k].id & 0xffff;
						fcn_0046f740(g_772514,
						    *(int*) (g_7f4ca0 + id * 0x21c + 0x18c),
						    0x98, posY[k] + 2);
						*(int*) (g_1015ea0 + col * 756 + 0x1d0) = 3;
						*(int*) (g_1015ea0 + col * 756 + 0x2f0) =
						    (int) (g_7f4ca0 + id * 0x21c);
					}
					p = (char*) posX;
					for (i = 4; i < 6; i++) {
						if (tabB[i].id == -1) {
							break;
						}
						col = fcn_0046f740(g_772514, 0x5db, 0x96,
						    *(int*) p);
						tabB[i].text = col;
						tabB[i].y = 0x96;
						tabB[i].x = (short) (*(short*) p + nc);
						id = tabB[i].id & 0xffff;
						fcn_0046f740(g_772514,
						    *(int*) (g_7f4ca0 + id * 0x21c + 0x18c),
						    0x98, *(int*) p + 2);
						*(int*) (g_1015ea0 + col * 756 + 0x1d0) = 3;
						*(int*) (g_1015ea0 + col * 756 + 0x2f0) =
						    (int) (g_7f4ca0 + id * 0x21c);
						p += 4;
					}
				}

				i = ((tabB[2].y - h - 0xa) / 2) + h + 0xa;
				p = (char*) &tabA[0].x;
				for (k = 0; k < 2; k++) {
					fcn_00472c30(*(short*) p,
					    *(short*) (p + 2) + h + 5,
					    *(short*) p, i, 0x10, 0x10, 0x10);
					p += 0x10;
				}
				id = tabA[0].x & 0xffff;
				i = tabA[1].x & 0xffff;
				t0 = 0;
				p = (char*) &tabB[0].x;
				for (k = 0; k < 6; k++) {
					if (*(short*) (p - 8) != -1 && t0 != 3) {
						col = *(short*) p;
						fcn_00472c30(col,
						    *(short*) (p + 2) + h + 5,
						    col, posY[1], 0x10, 0x10, 0x10);
						if (col < id) {
							id = col;
						}
						if (col > i) {
							i = col;
						}
					}
					p += 0x10;
					t0++;
				}
				if (id != i) {
					i++;
				}
				fcn_00472c30(id, posY[1], i, posY[1], 0x10, 0x10, 0x10);
				tabC[0].y = 0x122;
				tabC[0].x = tabA[0].x & 0xffff;
				tabC[1].x = tabA[0].x & 0xffff;

				if (a1 & 1) {
					posB[0] = rows2 - n3;
					posC[0] = posB[0] - w - 0x28;
					posB[1] = posB[0] + w + 0x28;
					posC[1] = posC[0] - w - 0x28;
					posC[2] = posB[1] + w + 0x28;
					p = (char*) tabC;
					for (k = 0; k < 5; k++) {
						if (*(short*) p == -1) {
							break;
						}
						col = fcn_0046f740(g_772514, 0x5db,
						    0x122, posC[k]);
						*(int*) (p + 4) = col;
						*(short*) (p + 0xa) = 0x122;
						*(short*) (p + 8) = (short) (posB[k] + nc);
						id = *(short*) p & 0xffff;
						fcn_0046f740(g_772514,
						    *(int*) (g_7f4ca0 + id * 0x21c + 0x18c),
						    0x124, posC[k] + 2);
						*(int*) (g_1015ea0 + col * 756 + 0x1d0) = 3;
						*(int*) (g_1015ea0 + col * 756 + 0x2f0) =
						    (int) (g_7f4ca0 + id * 0x21c);
						p += 0x10;
					}
				} else {
					posB[0] = rows2 - n3;
					posC[0] = posB[0] - w - 0x28;
					posC[2] = posC[0] - w - 0x28;
					posB[1] = posB[0] + w + 0x28;
					posC[1] = posB[1] + w + 0x28;
					p = (char*) tabC;
					for (k = 0; k < 4; k++) {
						if (*(short*) p == -1) {
							break;
						}
						col = fcn_0046f740(g_772514, 0x5db,
						    0x122, posC[k]);
						*(int*) (p + 4) = col;
						*(short*) (p + 0xa) = 0x122;
						*(short*) (p + 8) = (short) (posB[k] + nc);
						id = *(short*) p & 0xffff;
						fcn_0046f740(g_772514,
						    *(int*) (g_7f4ca0 + id * 0x21c + 0x18c),
						    0x124, posB[k] + 2);
						*(int*) (g_1015ea0 + col * 756 + 0x1d0) = 3;
						*(int*) (g_1015ea0 + col * 756 + 0x2f0) =
						    (int) (g_7f4ca0 + id * 0x21c);
						p += 0x10;
					}
				}

				p = (char*) tabB;
				for (k = 0; k < 6; k++) {
					if (*(short*) p == -1) {
						break;
					}
					col = *(int*) (p + 4);
					*(int*) (g_1015ea0 + col * 756 + 0x5c) =
					    (a1 & 1) ? ((a1 & 0xc) ? 1 : 0)
					    : ((a1 & 0x10) ? 1 : 0);
					io_FormatTextBuffer(buf3, 0x6ac96c,
					    *(short*) p);
					fcn_005c9090(buf3, *(short*) (p + 8),
					    *(short*) (p + 0xa) + rows2 + 3,
					    0x50, 0x56);
					if (*(short*) p == *(short*) er) {
						fcn_0046f740(g_772514,
						    *(int*) (er + 0x54),
						    *(short*) (p + 8) - w - 0xa,
						    *(short*) (p + 0xa) - 0xa);
					}
					p += 0x10;
				}
				p = (char*) tabA;
				for (k = 0; k < 2; k++) {
					if (*(short*) p == -1) {
						break;
					}
					col = *(int*) (p + 4);
					*(int*) (g_1015ea0 + col * 756 + 0x5c) =
					    (a1 & 0xc) ? 0 : 1;
					io_FormatTextBuffer(buf1, 0x6ac96c,
					    *(short*) p);
					fcn_005c9090(buf1, *(short*) (p + 8),
					    *(short*) (p + 0xa) + rows2 + 3,
					    0x50, 0x56);
					if (*(short*) p == *(short*) er) {
						fcn_0046f740(g_772514,
						    *(int*) (er + 0x54),
						    *(short*) (p + 8) - w - 0xa,
						    *(short*) (p + 0xa) - 0xa);
					}
					p += 0x10;
				}
				p = (char*) tabC;
				for (k = 0; k < 5; k++) {
					if (*(short*) p == -1) {
						break;
					}
					col = *(int*) (p + 4);
					*(int*) (g_1015ea0 + col * 756 + 0x5c) =
					    ((a1 & 1) && !(a1 & 0xc)) ||
					    !(a1 & 2) || !(a1 & 8) ? 1 : 0;
					io_FormatTextBuffer(buf2, 0x6ac96c,
					    *(short*) p);
					fcn_005c9090(buf2, *(short*) (p + 8),
					    *(short*) (p + 0xa) + rows2 + 3,
					    0x50, 0x56);
					if (*(short*) p == *(short*) er) {
						fcn_0046f740(g_772514,
						    *(int*) (er + 0x54),
						    *(short*) (p + 8) - w - 0xa,
						    *(short*) (p + 0xa) - 0xa);
					}
					p += 0x10;
				}
			}
		}
		if (g_14ce8e0 != 0 && !(a1 & 8)) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			hid = -1;
			{
				char* q;
				int j;

				q = (char*) &tabB[0].y;
				for (j = 0; j < 6; j++) {
					if (g_67d370 == *(int*) q) {
						hid = j;
						break;
					}
					q += 0x10;
				}
			}
			rec = 0;
			if (hid != -1) {
				rec = gm_LookupEntityRecordById(
				    *(int*) (g_7f4ca0 +
				    (*(short*) (&tabB[hid].x) & 0xffff) * 0x21c + 4));
			}
			if (!rec) {
				hid = -1;
				{
					char* q;
					int j;

					q = (char*) &tabA[0].x;
					for (j = 0; j < 2; j++) {
						if (g_67d370 == *(int*) q) {
							hid = j;
							break;
						}
						q += 0x10;
					}
				}
				if (hid != -1) {
					rec = gm_LookupEntityRecordById(
					    *(int*) (g_7f4ca0 +
					    (*(short*) (&tabA[hid].x) & 0xffff) * 0x21c + 4));
				}
			}
			if (!rec) {
				hid = -1;
				{
					char* q;
					int j;

					q = (char*) &tabC[0].x;
					for (j = 0; j < 5; j++) {
						if (g_67d370 == *(int*) q) {
							hid = j;
							break;
						}
						q += 0x10;
					}
				}
				if (hid != -1) {
					rec = gm_LookupEntityRecordById(
					    *(int*) (g_7f4ca0 +
					    (*(short*) (&tabC[hid].x) & 0xffff) * 0x21c + 4));
				}
			}
			keepHid = hid;
			keepRec = rec;
			if (rec) {
				fcn_00471af0(win, 0);
				if (!(a1 & 0x10) && (a1 & 8)) {
					fcn_005d1790((void*) rec,
					    *(int*) &posY[1] != rec ? 1 : 0);
				}
				fcn_00471af0(win, 1);
			} else {
				count = 1;
			}
			if (a3 == 0x5d0660) {
				io_AppendText((void*) &keepHid, (void*) &keepRec);
			}
		}
		if (!fcn_005373e0((void*) 0x5d0660, a3)) {
			break;
		}
	}
	fcn_00471e30(win);
	fcn_0057e880(6, 1, 0, 0);
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")
unsigned char _tlead_GOLDTL_fcn_005d0660[619] = {
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    };
