

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

extern char* d2_Controls;
extern char* d2_CurrentWindow;
extern int d2_CurrentWindowId;
extern char str_empty[];
extern int d2_ObjektNameTable[];
extern char g_6aac70[];

unsigned short* __cdecl gm_QueryEntities(int, int, int, ...);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_AddWindowField(int, int, int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SetElementFont(int, int);
void __cdecl d2_SetElementEnabled(int, int);
int __cdecl d2_GetControlValue(int);
int __cdecl gm_AmountToTradeUnits(int a, int b);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl d2_SetLabelText(int, char*);
void __cdecl d2_DestroyElement(int);
void __cdecl d2_AddDisplayCounter(int key, int amt);
void __cdecl d2_LayoutEntityList(int);

/* ADDRESS: GOLDDE 0x0058a150 */
int __cdecl d2_PopulateInventoryGrid(int list, Row* rows, int a3, int a4, char sel)
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
	int amount;
	char buf[0x20];

	result = -1;
	changed = 0;
	p = gm_QueryEntities(list, 1, 4, 9);
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
					d2_SetForm(a3, a4);
					r->icon = d2_AddWindowField((((Screen*)d2_CurrentWindow)->w - 0x30) >> 1, j * 76, r->key + 0xdf, 0x82, d2_CurrentWindowId);
					(*(int*)&((D2_CONTROL_TL*)d2_Controls)[r->icon].value_054) = 1;
					r->label = d2_ShowTxt((((Screen*)d2_CurrentWindow)->w - 0xbe) >> 1, j * 76 + 0x2e, str_empty, d2_CurrentWindowId);
					d2_SetElementFont(r->icon, 0x54);
					d2_SetElementFont(r->label, 0x54);
					(*(int*)&((D2_CONTROL_TL*)d2_Controls)[r->label].value_06c) = 1;
					(*(int*)&((D2_CONTROL_TL*)d2_Controls)[r->label].width) = 0xbe;
					if (sel) {
						(*(int*)&((D2_CONTROL_TL*)d2_Controls)[r->icon].disabled) = 1;
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
				d2_SetElementEnabled(rows[i].icon, 1);
			}
		}
	}
	for (i = 0; i < 16; i++) {
		r = &rows[i];
		if (r->icon == -1) {
			continue;
		}
		ent = d2_GetControlValue(r->icon);
		r->ent = ent;
		q = (char*) gm_QueryEntities(list, 1, 0, r->key);
		if (q != 0 && gm_AmountToTradeUnits(*(int*) (q + 0xe), r->key) != 0) {
			amount = gm_AmountToTradeUnits(*(int*) (q + 0xe), r->key);
			d2_SetElementValue(r->icon, 0, amount, ent);
			io_FormatTextBuffer(buf, (int) g_6aac70, amount, d2_ObjektNameTable[r->key * 2]);
			d2_SetLabelText(r->label, buf);
			(*(int*)&((D2_CONTROL_TL*)d2_Controls)[r->label].width) = 0xbe;
			r->count = amount;
		} else {
			d2_DestroyElement(r->label);
			r->label = -1;
			d2_DestroyElement(r->icon);
			r->icon = -1;
			r->count = 0;
			r->key = 0;
			changed = 1;
		}
		if (sel && ent) {
			d2_AddDisplayCounter(r->key + 0xdf, ent);
			for (j = 0; j < 16; j++) {
				if (rows[j].icon != -1 && i != j) {
					d2_SetElementEnabled(rows[j].icon, 0);
				}
			}
			result = i;
		}
	}
	if (changed) {
		d2_SetForm(a3, a4);
		d2_LayoutEntityList((int) rows);
	}
	return result;
}
