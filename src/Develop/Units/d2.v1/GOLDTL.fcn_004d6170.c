#include <stdio.h>
#include <string.h>

extern char g_6b5c60[];
extern char g_7f4ca4[];
extern char g_7f4ca0[];
extern unsigned short g_774970;
extern int g_68b79c;
#include "GOLDTL.fcn_004d6170_gconf.h"
extern char* g_772e9c;
extern char* g_772ea4;
extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_774654;
extern unsigned char* lpGebaeudePROT;
extern unsigned char g_773d75;
extern int g_772514;
extern int g_aed32c;
extern char* g_14a79c0;

void __cdecl fcn_00475220(char*);
void __cdecl fcn_00533a40(char*);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl fcn_00502cd0(int, ...);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_004ce740(char*);
char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(int, ...);
int __cdecl fcn_005373e0(void*, int);
int __cdecl gm_SearchTable67(int);
void __cdecl fcn_004d5740(char*, int, int);
int __cdecl fcn_004d5490(int, int, int);
char* __cdecl gm_GetEntityTableEntry(char*);
void __cdecl fcn_0050d490(char*);
void __cdecl fcn_004c51f0(int, int, int, int, int, int);
double __cdecl fcn_0050bb50(int, int);
char* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl fcn_004b4650(char*, int);
void __cdecl fcn_004c5f60(int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_004e6eb0(char*, unsigned int);
void __cdecl fcn_00412830(int);
int __cdecl fcn_00471e30(int);
int __cdecl fcn_004e6cb0(int);
int __cdecl gm_AccumulateTyped2(char*);
void __cdecl fcn_004c5150(int, int, int, int);
int __cdecl gm_MapEntityStatRange(int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_00534160(int, int, int, int);
int __cdecl fcn_0050b750(int, int);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4700(int, int, int, int*);
void __cdecl fcn_004c5360(void);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl fcn_00507910(int);
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl gm_RandomMod(int);
void __cdecl fcn_0050ff70(char*, int);

/* ADDRESS: GOLDTL 0x004d6170 */
int __cdecl fcn_004d6170(char* ctx)
{
	int mode;
	char* side;
	char* rec;
	int pay;
	int screen;
	int qlo;
	int qhi;
	int flo;
	int fhi;
	struct {
		char small[0x100];
		char buf[0x400];
		char cat[0x400];
		char msg[0x400];
		char spare[0x408];
	} s;
	int* id;
	int n;
	int tally;
	char* ent;
	char* cur;
	unsigned char flags;
	unsigned char kind;
	char* row;
	int i;
	int col;
	int line;
	int bonus;
	int sum;
	int choice;
	char* p;
	int mask;
	char* looked;
	char looked_kind;
	char* self;

	self = ctx;
	mode = 0;
	rec = 0;
	fcn_00475220(g_6b5c60);
	fcn_00533a40(g_6b5c60);
	if (*(int*) (self + 0x10c) != -1) {
		ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10c));
		rec = fcn_00502cd0(*(int*) (ent + 0x5d), 2, 6, 0, 0x116);
		if (rec == 0) {
			rec = fcn_00502cd0(*(int*) (ent + 0x5d), 2, 6, 0, 0x2a);
		}
	}
	if (g_68b79c == *(int*) (g_7f4ca4 + g_774970 * 0x21c)) {
		for (id = (int*) (self + 0x80), n = 16; n != 0; n--, id++) {
			if (*id != -1) {
				ent = gm_LookupEntityRecordById(*id);
				if (ent != 0) {
					fcn_004ce740(ent);
				}
			}
		}
		for (id = (int*) (self + 0xc0), n = 16; n != 0; n--, id++) {
			if (*id != -1) {
				ent = gm_LookupEntityRecordById(*id);
				if (ent != 0) {
					fcn_004ce740(ent);
				}
			}
		}
	}
	if (g_772ea4 != 0) {
		side = g_772e98;
		if (g_772ea4 != g_772e9c) {
			side = g_772e9c;
		}
	} else {
		tally = 0;
		for (id = (int*) (self + 0x80), n = 16; n != 0; n--, id++) {
			if (*id != -1) {
				looked = gm_LookupEntityRecordIn32SlotTable(*id);
				looked_kind = looked[8];
				if (looked_kind != 0 && looked_kind != 4 &&
					*(int*) (*(int*) (*(int*) (looked + 0x184) + 0x34) + 0x218) != 1) {
					tally++;
				}
			}
		}
		n = 0;
		for (id = (int*) (self + 0xc0), i = 16; i != 0; i--, id++) {
			if (*id != -1) {
				looked = gm_LookupEntityRecordIn32SlotTable(*id);
				looked_kind = looked[8];
				if (looked_kind != 0 && looked_kind != 4 &&
					*(int*) (*(int*) (*(int*) (looked + 0x184) + 0x34) + 0x218) != 1) {
					n++;
				}
			}
		}
		if (n > tally) {
			side = g_772e9c;
		} else {
			side = g_772e98;
		}
	}
	screen = fcn_00470820(0, 0, "cutscenes\\combat_end");
	fcn_00471d80(screen, 3);
	d2_SetForm(screen, 2);
	io_AppendText(0x7d);
	d2_SetForm(screen, 1);
	if (*(int*) (g_7f4ca4 + g_774970 * 0x21c) == *(int*) (side + 4)) {
		if (side == g_772e98) {
			if (self[0x7c] & 1) {
				io_AppendText(0x1189, *(unsigned short*) g_772e98, *(unsigned short*) g_772e9c);
				io_AppendText(0x118a);
			} else {
				io_AppendText(0x1189, *(unsigned short*) g_772e98, *(unsigned short*) g_772e9c);
			}
		} else {
			io_AppendText(0x118e, *(unsigned short*) g_772e9c, *(unsigned short*) g_772e98);
		}
	} else if (side == g_772e9c) {
		io_AppendText(0x118c, *(unsigned short*) g_772e98, *(unsigned short*) g_772e9c);
		if (self[0x7c] & 1) {
			ent = fcn_00502cd0(0, 2, 7, 1, *(int*) (self + 0x100));
			if (*(int*) (ent + 0x24) != 0 && gm_SearchTable67(*(int*) (*(int*) (ent + 0x24) + 0xb4)) != 0) {
				io_AppendText(0x118d);
			}
		}
	} else {
		io_AppendText(0x118f, *(unsigned short*) g_772e9c, *(unsigned short*) g_772e98);
	}
	while (fcn_005373e0(fcn_004d6170, 0x7d6c6) != 0) {
		if (g_14ce8e0 != 0 || g_100f1dc == 2) {
			g_774654 = 1;
		}
	}
	d2_SetForm(screen, 1);
	io_AppendText((int) "$C");
	io_AppendText(0x1191);
	ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10c));
	kind = lpGebaeudePROT[(unsigned char) *ent * 0x24d];
	if (kind == 0x13) {
		mode = 0;
	} else if (kind == 0x10) {
		mode = 1;
	} else if (kind == 4) {
		mode = 2;
	}
	io_AppendText(0x1193, *(unsigned short*) g_772e9c, mode + 0x1125);
	fcn_004d5740(self + 0xc0, 0, 0x64);
	ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x14));
	if (ent == 0) {
		mode = 0;
	} else {
		kind = lpGebaeudePROT[(unsigned char) *ent * 0x24d];
		if (kind == 0x13) {
			mode = 0;
		} else if (kind == 0x10) {
			mode = 1;
		} else if (kind == 4) {
			mode = 2;
		}
	}
	io_AppendText((int) "$7A");
	io_AppendText(0x1193, *(unsigned short*) g_772e98, mode + 0x1125);
	fcn_004d5740(self + 0x80, 0, 0x12c);
	while (fcn_005373e0(fcn_004d6170, 0x7d6c6) != 0) {
		if (g_14ce8e0 != 0 || g_100f1dc == 2) {
			g_774654 = 1;
		}
	}
	d2_SetForm(screen, 1);
	io_AppendText((int) "$C");
	io_AppendText(0x1197);
	flags = (unsigned char) self[0x7c];
	if (flags & 1) {
		if (*(unsigned short*) g_772e98 == g_774970) {
			fcn_004d5490(0x24, 0x32, 2);
		} else if (*(unsigned short*) g_772e9c == g_774970) {
			pay = fcn_004d5490(0x24, 0x32, side == g_772e9c ? 0 : 1);
			cur = gm_GetEntityTableEntry(g_772e9c);
			if (cur != 0) {
				*(int*) (cur + 0x1c) += pay;
			}
			if (*(int*) (self + 0x10c) != -1) {
				ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10c));
				*(int*) (ent + 0x4d) += pay;
			}
		}
		for (id = (int*) (self + 0x100), n = 3; n != 0; n--, id++) {
			if (*id == -1) {
				continue;
			}
			cur = fcn_00502cd0(0, 2, 7, 1, *id);
			cur = fcn_00502cd0(*(int*) (cur + 0x14), 1, 0, 0x1dd);
			cur = fcn_00502cd0(*(int*) (cur + 0x14), 1, 5);
			while (cur != 0) {
				if (side == g_772e9c) {
					*(int*) (cur + 0xa) = (unsigned short) *g_772e9c;
				}
				if (*(int*) (cur + 0xa) == (unsigned short) *g_772e9c && rec != 0) {
					if (g_68b79c == *(int*) (g_7f4ca4 + g_774970 * 0x21c)) {
						fcn_0050d490(cur);
						fcn_004c51f0(*(int*) (rec + 2), *(int*) (cur + 6), *(unsigned short*) cur,
							*(int*) (cur + 0xe), g_773d75, 0);
					}
					fcn_0050bb50(*(unsigned short*) cur, g_773d75);
				}
				cur = gm_NextEntityQueryMatch();
			}
		}
		while (fcn_005373e0(fcn_004d6170, 0x7d6c6) != 0) {
			if (g_14ce8e0 != 0 || g_100f1dc == 2) {
				g_774654 = 1;
			}
		}
	} else if ((flags & 2) && side == g_772e9c && *(unsigned short*) side == g_774970) {
		ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x14));
		io_FormatTextBuffer(s.msg, 0x119f, ent, *(unsigned short*) g_772e9c, ent);
		kind = (unsigned char) *ent;
		if (kind != 0x1e && kind != 0x20 && kind != 0x1f) {
			io_FormatTextBuffer(s.cat, 0x11a0, (int) kind * 14 + 0x48e);
			strcat(s.msg, s.cat);
		}
		io_FormatTextBuffer(s.cat, 0x11a1);
		strcat(s.msg, s.cat);
		io_FormatTextBuffer(s.cat, 0x11a2);
		strcat(s.msg, s.cat);
		io_FormatTextBuffer(s.cat, 0x11a3);
		strcat(s.msg, s.cat);
		choice = fcn_004e6eb0(s.msg, 0x11);
		if (kind == 0x1e || kind == 0x20 || kind == 0x1f) {
			choice++;
		}
		if (choice == 1) {
			kind = lpGebaeudePROT[(unsigned char) *ent * 0x24d];
			if (kind == 4 || kind == 0x10) {
				fcn_004b4650(g_772e9c, 0x1c);
			}
			fcn_004c5f60(*(int*) (ent + 1), *(int*) (g_772e9c + 4), *(int*) (g_772e9c + 4));
			io_FormatTextBuffer(s.msg, 0x11a4, *(unsigned short*) g_772e9c, ent);
			fcn_004e6eb0(s.msg, 0);
		} else if (choice == 2) {
			s.buf[0] = g_6b5c60[0];
			memset(s.buf + 1, 0, 0x3ff);
			io_FormatTextBuffer(s.buf, 0x11a5, *(unsigned short*) g_772e9c, ent);
			fcn_004e6eb0(s.buf, 0);
			cur = fcn_00502cd0(*(int*) (ent + 0x5d), 2, 6, 0, 0x2a);
			if (cur == 0) {
				cur = fcn_00502cd0(*(int*) (ent + 0x5d), 2, 6, 0, 0x116);
			}
			pay = gm_AccumulateTyped2(g_772e98);
			if (pay >= 0x9c400) {
				pay = 0x9c400;
			}
			qhi = 0;
			qlo = fcn_004e6cb0(0x32);
			if (pay < 0) {
				pay = 0;
			}
			sum = (int) (((double) qlo * 0.001 + 0.07) * (double) pay);
			io_FormatTextBuffer(s.buf, (int) "$Z%T$A", sum);
			*(int*) &mode = sum;
			fcn_004c5150(*(int*) (g_772e9c + 4), *(int*) (g_772e98 + 4), g_773d75, sum);
			if (cur != 0 && rec != 0) {
				ent = fcn_00502cd0(*(int*) (cur + 0x14), 1, 5);
				while (ent != 0) {
					qlo = fcn_004e6cb0(0x14) + 0x50;
					qhi = 0;
					n = (int) ((double) qlo * 0.01 * (double) *(int*) (ent + 0xe));
					if (n < 1) {
						n = 1;
					}
					sprintf(s.small, "%i %s$A", n, *(char**) ((char*) g_14a79c0 + *(unsigned short*) ent * 8));
					strcat(s.buf, s.small);
					if (g_68b79c == *(int*) (g_7f4ca4 + g_774970 * 0x21c)) {
						fcn_004c51f0(*(int*) (rec + 2), *(int*) (cur + 2), *(unsigned short*) ent, n, g_773d75, 0);
					}
					sum = (int) (fcn_0050bb50(*(unsigned short*) ent, g_773d75) * (double) n + (double) sum);
					ent = gm_NextEntityQueryMatch();
				}
			}
			d2_SetForm(screen, 1);
			io_AppendText((int) s.buf);
			cur = gm_GetEntityTableEntry(g_772e9c);
			if (cur != 0) {
				*(int*) (cur + 0x1c) += sum;
			}
			if (*(int*) (self + 0x10c) != -1) {
				ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10c));
				*(int*) (ent + 0x4d) += sum;
			}
			while (fcn_005373e0(fcn_004d6170, 0x7d6c6) != 0) {
				if (g_14ce8e0 != 0 || g_100f1dc == 2) {
					g_774654 = 1;
				}
			}
		} else if (choice == 3) {
			s.buf[0] = g_6b5c60[0];
			memset(s.buf + 1, 0, 0x3ff);
			io_FormatTextBuffer(s.buf, 0x11a6, *(unsigned short*) g_772e9c, ent);
			fcn_004e6eb0(s.buf, 0);
			if (g_68b79c == *(int*) (g_7f4ca4 + g_774970 * 0x21c)) {
				fcn_0050ff70(ent, 0x14 - fcn_004e6cb0(0x14));
			}
		} else if (choice == 0) {
			io_FormatTextBuffer(s.msg, 0x11a7, *(unsigned short*) g_772e9c, *(unsigned short*) g_772e9c);
			fcn_004e6eb0(s.msg, 0);
			for (row = g_7f4ca0 + 0x164; row < g_7f4ca0 + 0x65564; row += 0x21c) {
				if (*(unsigned short*) (row - 0x164) == 0xffff || *(unsigned char*) (row - 0x15c) == 0) {
					continue;
				}
				i = gm_MapEntityStatRange(*(unsigned char*) row);
				if (i == 0xa || i == 0xb || i == 0xc) {
					fcn_004c54c0(*(int*) (g_772e9c + 4), *(int*) (row - 0x160), 6, 1);
				}
			}
		}
	} else if (flags & 4) {
		ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10c));
		if (lpGebaeudePROT[(unsigned char) *ent * 0x24d] == 0x13) {
			sum = 0;
			for (id = (int*) (self + 0x80), i = 0; i < 16; i++, id++) {
				if (*id == -1) {
					continue;
				}
				cur = gm_LookupEntityRecordIn32SlotTable(*id);
				col = (i % 4) * 80 + 0x30;
				line = (i / 4 + 1) * 100;
				fcn_0046f740(col, line, 0x5db, g_772514);
				fcn_0046f740(col + 2, line, *(int*) (cur + 0x18c), g_772514);
				fcn_00534160(col, line + 0x3c, *(unsigned char*) (cur + 0x83), 0x4eb);
				bonus = 0;
				if (cur[8] == 0) {
					bonus = (int) (*(unsigned char*) (cur + 0x83) * (1.0f / 42.0f) + 1.0f);
					fcn_0046f740(col + 6, line + 6, 0x3b, g_772514);
					bonus = fcn_0050b750(bonus * 40, g_773d75);
				}
				if (side == g_772e9c && cur[8] != 0) {
					fcn_004c4510(cur, *(int*) (cur + 4));
					pay = 0;
					fcn_004c4700(4, 1, (int) cur - g_aed32c + 0x16c, &pay);
					fcn_004c5360();
				}
				io_FormatTextBuffer(s.small, (int) "%T", bonus);
				if (bonus != 0) {
					d2_ShowTxt(col, line + 0x50, s.small, g_772514);
				}
				sum += bonus;
			}
			if (sum != 0) {
				fcn_004c5150(*(int*) (g_772e9c + 4), -1, g_773d75, sum);
			} else if (*(unsigned short*) g_772e9c == g_774970) {
				io_AppendText(0x11b6);
			}
			if (*(int*) (self + 0x10c) != -1) {
				ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10c));
				*(int*) (ent + 0x4d) += sum;
			}
			while (fcn_005373e0(fcn_004d6170, 0x7d6c6) != 0) {
				if (g_14ce8e0 != 0 || g_100f1dc == 2) {
					g_774654 = 1;
				}
			}
		}
	} else if (flags != 0 && side == g_772e9c && g_772e9c[2] != 6 && g_772e9c[2] != 7) {
		i = fcn_00507910((unsigned char) *ent);
		if (gm_CheckStatLevel(*(unsigned short*) g_772e9c, i) == 0 || *ent == 0xd || *ent == 0xc || *ent == 0xb) {
			mask = 0xffff;
			choice = (gm_RandomMod(3) & mask) + 1;
			if (choice != 0) {
				if (choice == 2) {
					s.buf[0] = g_6b5c60[0];
					memset(s.buf + 1, 0, 0x3ff);
					io_FormatTextBuffer(s.buf, 0x11a5, *(unsigned short*) g_772e9c, ent);
					fcn_004e6eb0(s.buf, 0);
					cur = fcn_00502cd0(*(int*) (ent + 0x5d), 2, 6, 0, 0x2a);
					if (cur == 0) {
						cur = fcn_00502cd0(*(int*) (ent + 0x5d), 2, 6, 0, 0x116);
					}
					pay = gm_AccumulateTyped2(g_772e98);
					if (pay >= 0x9c400) {
						pay = 0x9c400;
					}
					flo = fcn_004e6cb0(0x32);
					fhi = 0;
					if (pay < 0) {
						pay = 0;
					}
					sum = (int) (((double) flo * 0.001 + 0.07) * (double) pay);
					io_FormatTextBuffer(s.buf, (int) "$Z%T$A", sum);
					fcn_004c5150(*(int*) (g_772e9c + 4), *(int*) (g_772e98 + 4), g_773d75, sum);
					if (cur != 0 && rec != 0) {
						p = fcn_00502cd0(*(int*) (cur + 0x14), 1, 5);
						while (p != 0) {
							qlo = fcn_004e6cb0(0x14) + 0x50;
							qhi = 0;
							n = (int) ((double) qlo * 0.01 * (double) *(int*) (p + 0xe));
							if (n < 1) {
								n = 1;
							}
							sprintf(s.small, "%i %s$A", n, *(char**) ((char*) g_14a79c0 + *(unsigned short*) p * 8));
							strcat(s.buf, s.small);
							if (g_68b79c == *(int*) (g_7f4ca4 + g_774970 * 0x21c)) {
								fcn_004c51f0(*(int*) (rec + 2), *(int*) (cur + 2), *(unsigned short*) p, n, g_773d75, 0);
							}
							sum = (int) (fcn_0050bb50(*(unsigned short*) p, g_773d75) * (double) n + (double) sum);
							p = gm_NextEntityQueryMatch();
						}
					}
					goto settle;
				} else if (choice == 3) {
					s.buf[0] = g_6b5c60[0];
					memset(s.buf + 1, 0, 0x3ff);
					io_FormatTextBuffer(s.buf, 0x11a6, *(unsigned short*) g_772e9c, ent);
					fcn_004e6eb0(s.buf, 0);
					if (g_68b79c == *(int*) (g_7f4ca4 + g_774970 * 0x21c)) {
						fcn_0050ff70(ent, 0x14 - fcn_004e6cb0(0x14));
					}
				} else if (choice == 1) {
					io_FormatTextBuffer(s.cat, 0x11a7, *(unsigned short*) g_772e9c, *(unsigned short*) g_772e9c);
					fcn_004e6eb0(s.cat, 0);
					for (row = g_7f4ca0 + 0x164; row < g_7f4ca0 + 0x65564; row += 0x21c) {
						if (*(unsigned short*) (row - 0x164) == 0xffff || *(unsigned char*) (row - 0x15c) == 0) {
							continue;
						}
						i = gm_MapEntityStatRange(*(unsigned char*) row);
						if (i == 0xa || i == 0xb || i == 0xc) {
							fcn_004c54c0(*(int*) (g_772e9c + 4), *(int*) (row - 0x160), 6, 1);
						}
					}
				}
			}
		} else {
			io_FormatTextBuffer(s.cat, 0x11a4, *(unsigned short*) g_772e9c, ent);
			fcn_004e6eb0(s.cat, 0);
		}
	}
	goto done;
settle:
	d2_SetForm(screen, 1);
	io_AppendText((int) s.buf);
	cur = gm_GetEntityTableEntry(g_772e9c);
	if (cur != 0) {
		*(int*) (cur + 0x1c) += sum;
	}
	if (*(int*) (self + 0x10c) != -1) {
		ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10c));
		*(int*) (ent + 0x4d) += sum;
	}
	while (fcn_005373e0(fcn_004d6170, 0x7d6c6) != 0) {
		if (g_14ce8e0 != 0 || g_100f1dc == 2) {
			g_774654 = 1;
		}
	}
done:
	fcn_00412830(0x10);
	return fcn_00471e30(screen);
}
unsigned char _dpad_772d14[392];
