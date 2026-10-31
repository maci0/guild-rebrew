/* Guard shift selection: validates the party's two linked id lists, then
 * either animates the choice (cutscene mode) or runs the modal dialog. */

typedef struct Ent {
	unsigned short id;
	char pad2[6];
	unsigned char live;
} Ent;

/* 0xb8-byte entity query accumulator filled by fcn_0050de80. */
typedef struct Query {
	int count;
	int f4;
	char pad8[0xa8];
	int total;
	int fbc;
} Query;

typedef struct ShiftDlg {
	char pad0[0xc];
	int rec;
	char pad10[4];
	int actor;
	char pad18[0x1c];
	int first;
	int second;
	char pad3c[0x40];
	unsigned char flags;
	char pad7d[3];
	int list_a[16];
	int list_b[16];
	int list_c[3];
	int owner;
} ShiftDlg;

int __cdecl fcn_004e6c80(void);
void __cdecl fcn_004e6c60(int);
Ent* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_FindRecordById(int);
void __cdecl fcn_0050de80(int, Query*);
int __cdecl gm_StartFilteredEntitySearch(int, int, int);
float __cdecl fcn_004ce8b0(Ent*);
void __cdecl fcn_004ce740(Ent*);
int __cdecl _ftol(void);
unsigned short __cdecl gm_RandomMod(int);
float __cdecl fcn_004ff210(unsigned short, int);
void __cdecl fcn_004d1ff0(ShiftDlg*);
void __cdecl fcn_004d1a80(void);
int __cdecl fcn_004d2c80(int*, int);
void __cdecl fcn_004d2e60(ShiftDlg*);
void __cdecl fcn_0052a960(void*);
void __cdecl fcn_00445f50(int, int, float, int);
void __cdecl fcn_004d5940(ShiftDlg*);
void __cdecl fcn_004e51d0(ShiftDlg*, int);
void __cdecl fcn_0046b2b0(int);
void __cdecl fcn_004d6170(ShiftDlg*);
void __cdecl fcn_004d2f10(ShiftDlg*);
void __cdecl fcn_004d2a60(ShiftDlg*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_004e6eb0(char*, unsigned int);
int __cdecl fcn_00502cd0(int, int, int, ...);
void __cdecl fcn_004d5110(int, int, int, int);
void __cdecl fcn_004d52a0(ShiftDlg*, int, int, int, float);

/* ADDRESS: GOLDTL 0x004d77e0 */
void __cdecl fcn_004d77e0(ShiftDlg* p)
{
	int changed;
	int flag;
	int saved;
	int i;
	int e;
	int v;
	int w;
	int t;
	Ent* ep;
	Query q;
	char buf[0x800];

	flag = 0;
	saved = fcn_004e6c80();
	changed = 0;
	for (i = 0; i < 0x10; i++) {
		if (p->list_a[i] != -1 && gm_LookupEntityRecordById(p->list_a[i]) == 0) {
			flag = 1;
			p->list_a[i] = -1;
		}
	}
	for (i = 0; i < 0x10; i++) {
		if (p->list_b[i] != -1) {
			if (gm_LookupEntityRecordById(p->list_b[i]) == 0) {
				flag = 1;
				p->list_b[i] = -1;
			} else {
				changed++;
			}
		}
	}
	if (p->flags & 1) {
		for (i = 0; i < 3; i++) {
			if (p->list_c[i] != -1) {
				e = gm_FindRecordById(p->list_c[i]);
				if (e == 0 || (fcn_0050de80(e, &q), q.total <= 0)) {
					flag = 2;
				}
			}
		}
	}
	if (gm_StartFilteredEntitySearch(1, 1, p->owner) == 0 || flag == 2 || changed == 0) {
		return;
	}
	if (*(int*) 0x772f3c == 0) {
		*(int*) 0x68bfbc = 0xc8;
		*(int*) 0x68b79c = p->rec;
		fcn_004d1ff0(p);
		fcn_004d1a80();
		fcn_004d2c80(p->list_b, 0x68becc);
		fcn_004d2c80(p->list_a, 0x68bec8);
		fcn_004d2e60(p);
		if (*(int*) 0x774804 != 0) {
			fcn_00445f50(2, 0, 1.0f, 1);
		} else {
			fcn_0052a960((void*) 0x7f4c00);
		}
		*(int*) 0x772ea4 = 0;
		*(int*) 0x772ea8 = 0;
		*(int*) 0x772eac = 0;
		fcn_004d5940(p);
		fcn_004e6c60(saved);
		fcn_004d1a80();
		fcn_004d1a80();
		fcn_004e51d0(p, 0);
		if (*(int*) 0x772ea4 == 0 && *(int*) 0x772ea8 == 0) {
			fcn_004e51d0(p, 0);
		}
		if (*(int*) 0x772ea8 == 0) {
			for (t = 0x9b4908; t < 0x9b4a48; t += 0x14) {
				if (*(int*) t != -1) {
					fcn_0046b2b0(*(int*) t);
				}
				*(int*) t = -1;
				*(int*) (t - 4) = 0;
				*(int*) (t + 4) = 0;
			}
			fcn_004d6170(p);
			fcn_004d2f10(p);
			fcn_004d2a60(p);
			return;
		}
		if (*(int*) 0x772eac != 0 && *(char*) (*(int*) 0x772e9c + 2) == 6) {
			v = 0;
			w = gm_StartFilteredEntitySearch(1, 1, *(int*) (*(int*) 0x772eb4 + 0x10c));
			if (w != 0) {
				v = fcn_00502cd0(*(int*) (w + 0x5d), 2, 6, 0, 0x116);
			}
			if (*(int*) 0x772eac <= 0) {
				io_FormatTextBuffer(buf, 0x1146);
			} else if (v == 0) {
				io_FormatTextBuffer(buf, 0x1144, *(int*) 0x772eac);
			} else {
				io_FormatTextBuffer(buf, 0x1145, *(int*) 0x772eac);
			}
			fcn_004e6eb0(buf, 0x10);
		}
		fcn_004d2a60(p);
		return;
	}
	changed = 0;
	saved = 0;
	*(int*) 0x772e9c = (int) gm_LookupEntityRecordById(p->first);
	*(int*) 0x772e98 = (int) gm_LookupEntityRecordById(p->second);
	for (i = 0; i < 0x10; i++) {
		if (p->list_a[i] != -1) {
			ep = gm_LookupEntityRecordById(p->list_a[i]);
			if (ep != 0 && ep->live != 0 && ep->live != 4) {
				changed = (int) (fcn_004ce8b0(ep) + changed);
				fcn_004ff210(ep->id, gm_RandomMod(10) * -20);
			}
		}
	}
	for (i = 0; i < 0x10; i++) {
		if (p->list_b[i] != -1) {
			ep = gm_LookupEntityRecordById(p->list_b[i]);
			if (ep != 0 && ep->live != 0 && ep->live != 4) {
				saved = (int) (fcn_004ce8b0(ep) + saved);
				fcn_004ff210(ep->id, gm_RandomMod(10) * -20);
			}
		}
	}
	if (gm_RandomMod(0x1e) + saved > gm_RandomMod(0x1e) + changed) {
		changed = *(int*) 0x772e9c;
	} else {
		changed = *(int*) 0x772e98;
	}
	for (i = 0; i < 0x10; i++) {
		if (p->list_a[i] != -1 && (ep = gm_LookupEntityRecordById(p->list_a[i])) != 0) {
			fcn_004ce740(ep);
		}
	}
	for (i = 0; i < 0x10; i++) {
		if (p->list_b[i] != -1 && (ep = gm_LookupEntityRecordById(p->list_a[i])) != 0) {
			fcn_004ce740(ep);
		}
	}
	if (p->flags & 2) {
		if (changed == *(int*) 0x772e9c) {
			fcn_004d5110(gm_StartFilteredEntitySearch(1, 1, p->actor), gm_StartFilteredEntitySearch(1, 1, p->owner),
			             *(int*) 0x772e9c, *(int*) 0x772e98);
		}
		return;
	}
	if (p->flags & 4) {
		return;
	}
	if (!(p->flags & 1)) {
		return;
	}
	if (changed == *(int*) 0x772e9c) {
		fcn_004d52a0(p, gm_StartFilteredEntitySearch(1, 1, p->owner), *(int*) 0x772e9c,
		             *(int*) 0x772e98, 100.0f);
	}
}
