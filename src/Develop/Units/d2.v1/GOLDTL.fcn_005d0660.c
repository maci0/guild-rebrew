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
 * Native order: the record tables hold (id, -1, text, x, y, 0) entries. The
 * child walk fills tabB by slot 0/1 then 4/5, tabA holds the two parents and
 * tabC the records whose +2 byte is below 0xa. The last three passes print
 * the labels and the visibility bit comes from the a1 flag bits.
 */
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include <string.h>
#include "Develop/Units/d2.v1/d2_gui.h"
extern char* g_772500;			/* 0x00772500 */
extern int d2_CurrentWindowId;			/* 0x00772514 */
#include "client_data.h"
extern int g_100f1dc;			/* 0x0100f1dc */
extern char* g_1015ea0;		/* 0x01015ea0 */
extern int g_14ce8e0;			/* 0x014ce8e0 */
extern int g_774654;			/* 0x00774654 */
extern int d2_CurrentElementId;			/* 0x0067d370 */
extern char g_7f4ca0[];			/* 0x007f4ca0 */

int __cdecl d2_TutorialAllowsFlag(int);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl gm_LookupEntityRecordById(unsigned int);
void* __cdecl fcn_00470820(short, short, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_ClearPaintbox(void);
int __cdecl d2_ClearWindowChildren(int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl fcn_00472c30(int, int, int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_005c9090(char*, int, int, int, int);
void __cdecl fcn_00471af0(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
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
	char buf[768];
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
	unsigned int t0;

	if (!d2_TutorialAllowsFlag(1)) {
		return;
	}
	fcn_0057e880(6, 0, 0, 0);
	ent = gm_LookupEntityRecordById(a0);
	if (!ent) {
		return;
	}
	win = (int) fcn_00470820(0, 0, (char*) 0x6acab0);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(win);
	d2_SetForm(win, 2);
	if (a2) {
		io_AppendText(a2);
	} else {
		io_AppendText(0x9f);
	}
	d2_SetForm(win, 1);
	count = 1;
	g_100f1dc = -1;
	rows = *(int*) ((char*) g_1015f4c + d2_CurrentWindowId * 0x3cc);
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
			{
				char* er;
				char* rec;
				int slot;
				int id;
				int k;
				char* p;

				slot = 0;
				er = (char*) ent;
				tabB[2].id = *(short*) er;
				rec = (char*) gm_LookupEntityRecordById(
				    *(int*) (er + 0x5c));
				if (rec) {
					if (!(*(int*) (er + 0x1c8) & 0x40000) &&
					    !(*(int*) (rec + 0x1c8) & 0x40000)) {
						flag = 1;
						tabB[3].id = *(short*) rec;
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
					k = 3;
					for (;;) {
						if (slot >= 6) {
							break;
						}
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
						k++;
						if (k >= 8) {
							break;
						}
					}
				}
				p = (char*) tabC;
				for (k = 3; k < 8; k++) {
					if (nc >= 5) {
						break;
					}
					id = *(int*) (er + 0x68 + (k - 3) * 4);
					if (id != -1) {
						rec = (char*) gm_LookupEntityRecordById(id);
						if (rec) {
							if (*(unsigned char*) (rec + 2) < 0xa) {
								*(short*) p = *(short*) rec;
								nc++;
								p += 0x10;
							}
						}
					}
				}

				d2_SetForm(win, 1);
				d2_ClearPaintbox();
				d2_ClearWindowChildren(d2_CurrentWindowId, 1);
				posY[0] = rows2 - w;
				tabA[0].text = d2_AddElementToWindow(posY[0] - 0x5a, 0xa,
				    0x5db, d2_CurrentWindowId);
				n3 = w / 2;
				t0 = posY[0] + n3;
				tabA[0].x = (short) (t0 - 0x5a);
				tabA[0].y = 0xa;
				idx = posY[0] - 0x58;
				if (tabA[0].id != -1) {
					id = tabA[0].id & 0xffff;
					d2_AddElementToWindow(idx, 0xc,
					    *(int*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[id]) + 0x18c),
					    d2_CurrentWindowId);
					
					*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[tabA[0].text]) + 0x1d0) = 3;
					*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[tabA[0].text]) + 0x2f0) =
					    (int) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[id]));
				} else {
					d2_AddElementToWindow(idx, 0xc, 0x4fb, d2_CurrentWindowId);
					tabA[0].text = -1;
				}
				tabA[1].text = d2_AddElementToWindow(rows2 + 0x5a, 0xa,
				    0x5db, d2_CurrentWindowId);
				tabA[1].x = (short) (n3 + rows2 + 0x5a);
				tabA[1].y = 0xa;
				idx = rows2 + 0x5c;
				if (tabA[1].id == -1) {
					d2_AddElementToWindow(idx, 0xc, 0x4fb, d2_CurrentWindowId);
					tabA[1].text = -1;
				} else {
					id = tabA[1].id & 0xffff;
					d2_AddElementToWindow(idx, 0xc,
					    *(int*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[id]) + 0x18c),
					    d2_CurrentWindowId);
					
					*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[tabA[1].text]) + 0x1d0) = 3;
					*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[tabA[1].text]) + 0x2f0) =
					    (int) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[id]));
				}

				if (flag) {
					tabB[2].text = d2_AddElementToWindow(posY[0] - 0x10,
					    0x96, 0x5db, d2_CurrentWindowId);
					tabB[2].x = (short) (t0 - 0x10);
					tabB[2].y = 0x96;
					idx = posY[0] - 0xe;
					if (tabB[2].id == -1) {
						d2_AddElementToWindow(idx, 0x98, 0x4fb, d2_CurrentWindowId);
						tabB[2].text = -1;
					} else {
						id = tabB[2].id & 0xffff;
						d2_AddElementToWindow(idx, 0x98,
						    *(int*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[id]) + 0x18c),
						    d2_CurrentWindowId);
						*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[tabB[2].text]) + 0x1d0) = 3;
						*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[tabB[2].text]) + 0x2f0) =
						    (int) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[id]));
					}
					tabB[3].text = d2_AddElementToWindow(rows2 + 0x10,
					    0x96, 0x5db, d2_CurrentWindowId);
					tabB[3].x = (short) (n3 + rows2 + 0x10);
					tabB[3].y = 0x96;
					idx = rows2 + 0x12;
					if ((unsigned short) tabB[3].id != 0xffff) {
						id = tabB[3].id & 0xffff;
						d2_AddElementToWindow(idx, 0x98,
						    *(int*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[id]) + 0x18c),
						    d2_CurrentWindowId);
						*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[tabB[3].text]) + 0x1d0) = 3;
						*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[tabB[3].text]) + 0x2f0) =
						    (int) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[id]));
					} else {
						d2_AddElementToWindow(idx, 0x98, 0x4fb, d2_CurrentWindowId);
						tabB[3].text = -1;
					}
				} else {
					idx = rows2 - n3;
					tabB[2].text = d2_AddElementToWindow(idx, 0x96, 0x5db,
					    d2_CurrentWindowId);
					tabB[2].x = (short) rows2;
					tabB[2].y = 0x96;
					idx += 2;
					if (tabB[2].id != -1) {
						id = tabB[2].id & 0xffff;
						d2_AddElementToWindow(idx, 0x98,
						    *(int*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[id]) + 0x18c),
						    d2_CurrentWindowId);
						*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[tabB[2].text]) + 0x1d0) = 3;
						*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[tabB[2].text]) + 0x2f0) =
						    (int) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[id]));
					} else {
						d2_AddElementToWindow(idx, 0x98, 0x4fb, d2_CurrentWindowId);
						tabB[2].text = -1;
					}
				}

				if (nb) {
					nb = rows / 5;
					posX[0] = nb + 0x10;
					t0 = (rows * 4) / 5;
					posX[1] = t0 - w - 0x10;
					{
						char* p;
						int k;
						int* px;

						idx = 2;
						p = (char*) tabB;
						for (k = 0; k < 2; k++) {
							if (*(short*) p == -1) {
								break;
							}
							*(int*) (p + 4) = d2_AddElementToWindow(
							    posX[k], 0x96, 0x5db, d2_CurrentWindowId);
							*(short*) (p + 0xa) = 0x96;
							*(short*) (p + 8) =
							    (short) (posX[k] + n3);
							id = *(short*) p & 0xffff;
							d2_AddElementToWindow(posX[k] + 2, 0x98,
							    *(int*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[
id]) + 0x18c), d2_CurrentWindowId);
							*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[
*(int*) (p + 4)]) + 0x1d0) = 3;
							*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[
*(int*) (p + 4)]) + 0x2f0) =
							    (int) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[id]));
							p += 0x10;
						}
						posX[0] = nb - w - 0x10;
						posX[1] = t0 + 0x10;
						px = posX;
						p = (char*) &tabB[4];
						for (k = 4; k < 6; k++) {
							if (*(short*) p == -1) {
								break;
							}
							*(int*) (p + 4) = d2_AddElementToWindow(
							    *px, 0x96, 0x5db, d2_CurrentWindowId);
							*(short*) (p + 0xa) = 0x96;
							*(short*) (p + 8) =
							    (short) (*px + n3);
							id = *(short*) p & 0xffff;
							d2_AddElementToWindow(*px + 2, 0x98,
							    *(int*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[
id]) + 0x18c), d2_CurrentWindowId);
							*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[
*(int*) (p + 4)]) + 0x1d0) = 3;
							*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[
*(int*) (p + 4)]) + 0x2f0) =
							    (int) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[id]));
							px++;
							p += 0x10;
						}
					}
				}

				t0 = (*((int*) (&tabB[2].x))) & 0xffff;
				posY[1] = (((int) t0 - h - 0xa) / 2) + h + 0xa;
				{
					char* p;
					int k;

					p = (char*) &tabA[0].x;
					for (k = 0; k < 2; k++) {
						fcn_00472c30(*(unsigned short*) p,
						    *(unsigned short*) (p + 2) + h + 5,
						    *(unsigned short*) p, posY[1], 0x10, 0x10, 0x10);
						p += 0x10;
					}
				}
				idx = *(int*) (&tabA[1].x) & 0xffff;
				nb = *(int*) (&tabA[0].x) & 0xffff;
				{
					char* p;
					int k;

					p = (char*) tabB;
					for (k = 0; k < 6; k++) {
						if (*(short*) p != -1 && k != 3) {
							fcn_00472c30(*(short*) (p + 8),
							    *(short*) (p + 0xa) + h + 5,
							    *(short*) (p + 8), posY[1],
							    0x10, 0x10, 0x10);
							if (*(short*) (p + 8) < nb) {
								nb = *(short*) (p + 8);
							}
							if (*(short*) (p + 8) > idx) {
								idx = *(short*) (p + 8);
							}
						}
						p += 0x10;
					}
				}
				if (nb != idx) {
					idx++;
				}
				fcn_00472c30(nb, posY[1], idx, posY[1], 0x10, 0x10, 0x10);
				tabC[0].y = 0x122;
				if (nc) {
					char* p;
					int k;

					if (nc & 1) {
						posC[0] = rows2 - n3;
						posC[1] = posC[0] - w - 0x28;
						posC[2] = posC[0] + w + 0x28;
						posC[3] = posC[1] - w - 0x28;
						posC[4] = posC[2] + w + 0x28;
						p = (char*) tabC;
						for (k = 0; k < 5; k++) {
							if (*(short*) p == -1) {
								break;
							}
							*(int*) (p + 4) = d2_AddElementToWindow(
							    posC[k], 0x122, 0x5db, d2_CurrentWindowId);
							*(short*) (p + 0xa) = 0x122;
							*(short*) (p + 8) =
							    (short) (posC[k] + n3);
							id = *(short*) p & 0xffff;
							d2_AddElementToWindow(posC[k] + 2, 0x124,
							    *(int*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[
id]) + 0x18c), d2_CurrentWindowId);
							*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[
*(int*) (p + 4)]) + 0x1d0) = 3;
							*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[
*(int*) (p + 4)]) + 0x2f0) =
							    (int) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[id]));
							p += 0x10;
						}
					} else {
						posB[0] = posY[0] - 0x14;
						posB[1] = rows2 + 0x14;
						posB[2] = posB[0] - w - 0x28;
						posB[3] = posB[1] + w + 0x28;
						p = (char*) tabC;
						for (k = 0; k < 4; k++) {
							if (*(short*) p == -1) {
								break;
							}
							*(int*) (p + 4) = d2_AddElementToWindow(
							    posB[k], 0x122, 0x5db, d2_CurrentWindowId);
							*(short*) (p + 0xa) = 0x122;
							*(short*) (p + 8) =
							    (short) (posB[k] + n3);
							id = *(short*) p & 0xffff;
							d2_AddElementToWindow(posB[k] + 2, 0x124,
							    *(int*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[
id]) + 0x18c), d2_CurrentWindowId);
							*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[
*(int*) (p + 4)]) + 0x1d0) = 3;
							*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[
*(int*) (p + 4)]) + 0x2f0) =
							    (int) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[id]));
							p += 0x10;
						}
					}
				}
				{
					char* p;
					int k;

					idx = *(short*) (&tabB[2].x) & 0xffff;
					posY[0] = idx;
					nb = idx;
					if (flag) {
						idx = *(short*) (&tabB[3].x) & 0xffff;
						p = (char*) &tabB[2].x;
						for (k = 0; k < 2; k++) {
							fcn_00472c30(*(short*) p,
							    *(short*) (p + 2) + h + 5,
							    *(short*) p,
							    (((int) (*(short*) (&tabC[0].y) & 0xffff) -
							    t0 - h) / 2) + t0 + h, 0x10, 0x10, 0x10);
							p += 0x10;
						}
						fcn_00472c30(nb,
						    (((int) (*(short*) (&tabC[0].y) & 0xffff) -
						    t0 - h) / 2) + t0 + h, nb + 1,
						    (((int) (*(short*) (&tabC[0].y) & 0xffff) -
						    t0 - h) / 2) + t0 + h, 0x10, 0x10, 0x10);
					}
					p = (char*) &tabC[0].x;
					for (k = 0; k < 5; k++) {
						if (*(short*) (p - 8) == -1) {
							break;
						}
						fcn_00472c30(*(short*) p,
						    *(short*) (p + 2) + h + 5,
						    *(short*) p,
						    (((int) (*(short*) (&tabC[0].y) & 0xffff) -
						    t0 - h) / 2) + t0 + h, 0x10, 0x10, 0x10);
						if (*(short*) p < nb) {
							nb = *(short*) p;
						}
						if (*(short*) p > idx) {
							idx = *(short*) p;
						}
						p += 0x10;
					}
					if (nc) {
						fcn_00472c30(idx,
						    (((int) (*(short*) (&tabC[0].y) & 0xffff) -
						    t0 - h) / 2) + t0 + h, idx + 1,
						    (((int) (*(short*) (&tabC[0].y) & 0xffff) -
						    t0 - h) / 2) + t0 + h,
						    0x10, 0x10, 0x10);
						if (!flag) {
							fcn_00472c30(posY[0],
							    t0 + h + 5, posY[0],
							    (((int) (*(short*) (&tabC[0].y) & 0xffff) -
							    t0 - h) / 2) + t0 + h,
							    0x10, 0x10, 0x10);
						}
					}
				}

				{
					char* p;
					int k;

					p = (char*) tabB;
					for (k = 6; k; k--) {
						if (*(short*) p == -1) {
							break;
						}
						*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[*(int*) (p + 4)]) + 0x5c) =
						    ((a1 & 1) && !(a1 & 0xc)) ||
						    (a1 & 0x10) ? 1 : 0;
						io_FormatTextBuffer(buf + 0x100, 0x6ac96c,
						    *(unsigned short*) p);
						nb = *(unsigned short*) (p + 8);
						t0 = *(unsigned short*) (p + 0xa);
						fcn_005c9090(buf + 0x100, nb, t0 + rows2 + 3,
						    0x50, 0x56);
						if (*(short*) p == *(short*) ent) {
							d2_AddElementToWindow(nb - n3 - 0xa,
							    t0 - 0xa,
							    *(int*) (ent + 0x54),
							    d2_CurrentWindowId);
						}
						p += 0x10;
					}
					p = (char*) tabA;
					for (k = 2; k; k--) {
						if (*(short*) p == -1) {
							break;
						}
						*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[*(int*) (p + 4)]) + 0x5c) =
						    (a1 & 0xc) ? 0 : 1;
						io_FormatTextBuffer(buf, 0x6ac96c,
						    *(unsigned short*) p);
						nb = *(unsigned short*) (p + 8);
						t0 = *(unsigned short*) (p + 0xa);
						fcn_005c9090(buf, nb, t0 + rows2 + 3,
						    0x50, 0x56);
						if (*(short*) p == *(short*) ent) {
							d2_AddElementToWindow(nb - n3 - 0xa,
							    t0 - 0xa,
							    *(int*) (ent + 0x54),
							    d2_CurrentWindowId);
						}
						p += 0x10;
					}
					p = (char*) tabC;
					for (k = 5; k; k--) {
						if (*(short*) p == -1) {
							break;
						}
						*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[*(int*) (p + 4)]) + 0x5c) =
						    ((a1 & 1) && !(a1 & 0xc)) ||
						    ((a1 & 2) && (a1 & 8) &&
						    *(unsigned short*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[
(*(short*) p & 0xffff)]) + 0xa) > 0xa)
						    ? 1 : 0;
						io_FormatTextBuffer(buf + 0x200, 0x6ac96c,
						    *(unsigned short*) p);
						nb = *(unsigned short*) (p + 8);
						t0 = *(unsigned short*) (p + 0xa);
						fcn_005c9090(buf + 0x200, nb, t0 + rows2 + 3,
						    0x50, 0x56);
						if (*(short*) p == *(short*) ent) {
							d2_AddElementToWindow(nb - n3 - 0xa,
							    t0 - 0xa,
							    *(int*) (ent + 0x54),
							    d2_CurrentWindowId);
						}
						p += 0x10;
					}
				}
			}
		}
		if (g_14ce8e0 != 0 && !(a1 & 8)) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			int hid;
			int rec;
			char* q;
			int k;

			hid = -1;
			rec = 0;
			q = (char*) &tabB[0].text;
			for (k = 0; k < 6; k++) {
				if (d2_CurrentElementId == *(int*) q) {
					hid = k;
					rec = gm_LookupEntityRecordById(
					    *(int*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[
(tabB[k].id & 0xffff)]) + 4));
					break;
				}
				q += 0x10;
			}
			q = (char*) &tabA[0].text;
			for (k = 0; hid == -1 && k < 2; k++) {
				if (d2_CurrentElementId == *(int*) q) {
					hid = k;
					rec = gm_LookupEntityRecordById(
					    *(int*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[
(tabA[k].id & 0xffff)]) + 4));
					break;
				}
				q += 0x10;
			}
			q = (char*) &tabC[0].text;
			for (k = 0; hid == -1 && k < 5; k++) {
				if (d2_CurrentElementId == *(int*) q) {
					rec = gm_LookupEntityRecordById(
					    *(int*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[
(tabC[k].id & 0xffff)]) + 4));
					break;
				}
				q += 0x10;
			}
			if (rec) {
				fcn_00471af0(win, 0);
				if (!(a1 & 0x10) && (a1 & 8)) {
					if (ent != rec) {
						fcn_005d1790((void*) rec, 1);
					} else {
						fcn_005d1790((void*) rec, 0);
					}
				}
				fcn_00471af0(win, 1);
			} else {
				count = 1;
			}
		}
		if (!main_RunFrameLoop((void*) 0x5d0660, a3)) {
			break;
		}
	}
	d2_DestroyForm(win);
	fcn_0057e880(6, 0, 1, 0);
}
