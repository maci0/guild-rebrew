

typedef struct {
	int icon;
	int label;
	int pad8;
	int key;
	int pad10;
	int ent;
	int count;
} Row;
// SIZE 0x1c

typedef struct {
	char pad0[0x18];
	int f18;
	char pad1c[0x4c - 0x1c];
	int f4c;
	char pad50[4];
	int f54;
	char pad58[0x6c - 0x58];
	int f6c;
	char pad70[0x2f4 - 0x70];
} Ent;
// SIZE 0x2f4

typedef struct {
	char pad0[0xc];
	int w;
} Screen;
// SIZE 0x10

typedef struct {
	int name;
	int pad4;
} Name;
// SIZE 0x8

extern char* g_1015ea0;
extern char* g_77255c;
extern int g_772514;
extern char g_6b5c60[];
extern int g_14a79c0[];
extern char g_6aac70[];

unsigned short* __cdecl fcn_00502cd0(int, int, int, ...);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00466ee0(int, int, int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_00472900(int, int);
void __cdecl fcn_00472640(int, int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_00508640(int a, int b);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_0046f940(int, char*);
void __cdecl fcn_0046b2b0(int);
void __cdecl fcn_00473690(int key, int amt);
void __cdecl fcn_005a51c0(int);

int __cdecl fcn_005a5440(int list, Row* rows, int a3, int a4, char sel)
{
	int changed;
	int result;
	unsigned short* p;
	char* q;
	Row* r;
	int key;
	int i;
	int j;
	int ent;
	int v;
	char buf[0x20];

	result = -1;
	changed = 0;
	p = fcn_00502cd0(list, 1, 4, 9);
	while (p != 0) {
		for (i = 0, key = *p; i < 16; i++) {
			if (rows[i].key == key) {
				break;
			}
		}
		if (i >= 16) {
			for (j = 0; j < 16; j++) {
				if (rows[j].key == 0) {
					r = &rows[j];
					r->key = key;
					fcn_004727a0(a3, a4);
					r->icon = fcn_00466ee0((((Screen*)g_77255c)->w - 0x30) >> 1, j * 76, r->key + 0xdf, 0x82, g_772514);
					((Ent*)g_1015ea0)[r->icon].f54 = 1;
					r->label = d2_ShowTxt((((Screen*)g_77255c)->w - 0xbe) >> 1, j * 76 + 0x2e, g_6b5c60, g_772514);
					fcn_00472900(r->icon, 0x54);
					fcn_00472900(r->label, 0x54);
					((Ent*)g_1015ea0)[r->label].f6c = 1;
					((Ent*)g_1015ea0)[r->label].f18 = 0xbe;
					if (sel) {
						((Ent*)g_1015ea0)[r->icon].f4c = 1;
					}
					break;
				}
			}
			changed = 1;
		}
		p = gm_NextEntityQueryMatch();
	}
	if (sel) {
		for (i = 0; i < 16; i++) {
			if (rows[i].icon != -1) {
				fcn_00472640(rows[i].icon, 1);
			}
		}
	}
	for (i = 0; i < 16; i++) {
		r = &rows[i];
		if (r->icon == -1) {
			continue;
		}
		ent = fcn_00471f80(r->icon);
		r->ent = ent;
		q = (char*) fcn_00502cd0(list, 1, 0, r->key);
		if (q != 0 && fcn_00508640(*(int*) (q + 0xe), r->key) != 0) {
			v = fcn_00508640(*(int*) (q + 0xe), r->key);
			d2_SetElementValue(r->icon, 0, v, ent);
			fcn_0051af00(buf, (int) g_6aac70, v, g_14a79c0[r->key * 2]);
			fcn_0046f940(r->label, buf);
			((Ent*)g_1015ea0)[r->label].f18 = 0xbe;
			r->count = v;
		} else {
			fcn_0046b2b0(r->label);
			r->label = -1;
			fcn_0046b2b0(r->icon);
			r->icon = -1;
			r->count = 0;
			r->key = 0;
			changed = 1;
		}
		if (sel && ent) {
			fcn_00473690(r->key + 0xdf, ent);
			for (j = 0; j < 16; j++) {
				if (rows[j].icon != -1 && i != j) {
					fcn_00472640(rows[j].icon, 0);
				}
			}
			result = i;
		}
	}
	if (changed) {
		fcn_004727a0(a3, a4);
		fcn_005a51c0((int) rows);
	}
	return result;
}
