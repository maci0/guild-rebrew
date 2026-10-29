/* Handler control block handed to the privilege callbacks. */
typedef struct Query {
	int kind;              /* 0x000 */
	char pad4[0x10];       /* 0x004 */
	char name[0x208];      /* 0x014 */
	char* p;               /* 0x21c */
} Query;
// SIZE 0x220

/* House record in the g_7f4ca0 slot table. */
typedef struct House {
	char pad0[4];                /* 0x000 */
	int f4;                      /* 0x004 */
	char pad8[0x1b1 - 8];        /* 0x008 */
	unsigned char f1b1;          /* 0x1b1 */
	char pad1b2[0x1c8 - 0x1b2];  /* 0x1b2 */
	int f1c8;                    /* 0x1c8 */
	char pad1cc[0x21c - 0x1cc];  /* 0x1cc */
} House;
// SIZE 0x21c

/* Display record in the g_1015ea0 table. */
typedef struct Slot {
	char pad0[0x4c];             /* 0x000 */
	int f4c;                     /* 0x04c */
	char pad50[0x60 - 0x50];     /* 0x050 */
	int f60;                     /* 0x060 */
	char pad64[0x2f4 - 0x64];    /* 0x064 */
} Slot;
// SIZE 0x2f4

extern char g_7f4ca0[];
extern char* g_1015ea0;
extern char g_6811b0[];
extern char g_68b300[];
extern unsigned short g_774970;
extern int g_6b7fac;
extern int g_772514;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;

int __cdecl fcn_0057ec20(int);
void __cdecl fcn_0057e880(int, int, int, int);
char* __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_004fa5b0(int, char*, Query*);
void __cdecl fcn_004fa5f0(char*, int, int);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_0046e830(int, int, int, int, int);
char* __cdecl fcn_005463a0(int, ...);
char* __cdecl he_fn_Handlung(void);
char* __cdecl fcn_00508e40(int);
int __cdecl fcn_005373e0(void*, int);

/* ADDRESS: GOLDTL 0x005d4a20 */
void __cdecl fcn_005d4a20(void)
{
	char* ptr = 0;
	int changed;
	int sel = -1;
	unsigned now;
	char fmt[8] = "%ia[%s]";
	Query q;
	int state[0x3a];
	int keys[0x3a];
	char* dlg;
	char* e;
	int i;
	int count;
	char* prev;
	int r;
	int h;
	int win;
	int mode = 2;

	if (((House*) g_7f4ca0)[g_774970].f1b1 != 0) {
		fcn_004fa5f0((char*) 0x14ac69c, 0, 0x657c7);
		return;
	}
	if (!fcn_0057ec20(2)) {
		return;
	}
	fcn_0057e880(8, 0, 0, 0);
	for (i = 0; i < 0x88; i++) {
		((int*) &q)[i] = 0;
	}
	q.kind = 1;
	dlg = fcn_00470820(0, 0, "panel\\privilegien");
	fcn_00473a90(0, 0);
	fcn_00471b60((int) dlg);
	changed = 1;
	for (i = 0; i < 0x3a; i++) {
		state[i] = 1;
	}
	g_100f1dc = -1;
	now = g_6b7fac;
	do {
		count = 0;
		if (now <= (unsigned) g_6b7fac || changed) {
			now = g_6b7fac + 500;
			prev = ptr;
			if (((((House*) g_7f4ca0)[g_774970].f1c8) & 0x100) != 0 || ptr != 0) {
				e = fcn_005463a0(1, 0, 0x45);
				while (e != 0) {
					if (*(int*) (e + 0xac) == ((House*) g_7f4ca0)[g_774970].f4) {
						ptr = fcn_00508e40(*(int*) (e + 0xb0));
						goto have;
					}
					e = he_fn_Handlung();
				}
				ptr = 0;
			}
		have:
			q.p = ptr;
			if (ptr != prev || (ptr == 0 && (q.kind == 2 || sel != -1))) {
				changed = 1;
				mode = 2;
				q.kind = 1;
			} else {
				q.kind = (mode != 2) + 1;
			}
			for (i = 0; i < 0x3a; i++) {
				r = fcn_004fa5b0(i, (char*) &((House*) g_7f4ca0)[g_774970], &q);
				if (r != state[i]) {
					changed = 1;
				}
				state[i] = r;
			}
			if (changed) {
				changed = 0;
				d2_SetForm((int) dlg, 2);
				fcn_00519190((int) g_6811b0);
				sel = -1;
				*(int*) (g_772514 * 0x3cc + 0x1016194) = 0;
				*(int*) (g_772514 * 0x3cc + 0x1016198) = 0;
				if (mode == 2) {
					d2_SetForm((int) dlg, 1);
					fcn_00519190(0x1cdd);
					if (ptr != 0) {
						d2_SetForm((int) dlg, 3);
						sel = fcn_00472250((int) dlg, 3,
							fcn_00519190(0x1cdc, *(unsigned short*) ptr));
					}
				} else if (mode == 10) {
					if (ptr != 0) {
						d2_SetForm((int) dlg, 1);
						fcn_00519190(0x1cde);
						d2_SetForm((int) dlg, 3);
						sel = fcn_00472250((int) dlg, 3,
							fcn_00519190(0x1cdb, *(unsigned short*) ptr));
					} else {
						d2_SetForm((int) dlg, 1);
						fcn_00519190(0x1cdd);
						mode = 2;
					}
				}
				d2_SetForm((int) dlg, 2);
				for (i = 0; i < 0x3a; i++) {
					keys[i] = -1;
					q.kind = (mode != 2) + 1;
					r = fcn_004fa5b0(i, (char*) &((House*) g_7f4ca0)[g_774970], &q);
					state[i] = r;
					if (r == mode) {
						if (count) {
							fcn_00519190((int) g_68b300);
						}
						keys[i] = fcn_00472250((int) dlg, 2,
							fcn_00519190((int) fmt, q.name));
						count++;
					} else if (mode == 2 && r == 9) {
						if (count) {
							fcn_00519190((int) g_68b300);
						}
						h = fcn_00472250((int) dlg, 2,
							fcn_00519190((int) fmt, q.name));
						keys[i] = -1;
						((Slot*) g_1015ea0)[h].f4c = 1;
						((Slot*) g_1015ea0)[h].f60 = 1;
						count++;
					}
				}
				if (count > 9) {
					d2_SetForm((int) dlg, 2);
					win = g_772514;
					d2_SetForm((int) dlg, 4);
					fcn_00519190((int) g_6811b0);
					fcn_0046e830(-1, -1, g_772514, win, 0x767);
				} else {
					d2_SetForm((int) dlg, 4);
					fcn_00519190((int) g_6811b0);
				}
			}
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == sel) {
				changed = 1;
				mode = (mode == 2) ? 10 : 2;
			} else {
				for (i = 0; i < 0x3a; i++) {
					if (keys[i] == g_67d370) {
						fcn_00471af0((int) dlg, 0);
						q.kind = (mode != 2) + 3;
						r = fcn_004fa5b0(i, (char*) &((House*) g_7f4ca0)[g_774970], &q);
						if ((char) r < 0) {
							changed = 1;
							state[i] = r & 0xa;
						}
						q.kind = (mode != 2) + 1;
						fcn_00471af0((int) dlg, 1);
						break;
					}
				}
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005d4a20, 0x657c7) != 0);
	fcn_00471e30((int) dlg);
	fcn_0057e880(8, 0, 1, 0);
}
