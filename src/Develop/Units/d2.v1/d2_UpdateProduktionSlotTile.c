extern int d2_CurrentWindowId;
extern unsigned int d2_SelectedEntityUiFlags;
extern unsigned char gm_ActiveTownIndex;
extern char* d2_Controls;
extern char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
/* Private layout views inferred from native accesses; they allocate no
 * storage and are visible only to this translation unit. */

// SIZE 0x38
typedef struct {
	int id;
	int f04;
	int x;
	int y;
	int icon;
	int icon2;
	int text1;
	int text2;
	int title;
	int obj;
	int f28;
	int f2c;
	int f30;
	int f34;
} PRODUKTION_SLOT_ROW;

#include "Develop/Units/d2.v1/d2_win.h"








/* g_1038144 is the page index table; g_1015f40 the window pool. */
extern int d2_FormPageWindows[];
extern char d2_Windows[];
extern int d2_ObjektNameTable[];
extern char* g_14b52c0;

int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
int __cdecl d2_AddWindowField(int, int, int, int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_SetElementFont(int, int);
void __cdecl d2_DestroyElement(int);
void __cdecl d2_CloseWindow(int);
void __cdecl d2_SetLabelText(int, char*);
int __cdecl d2_ShowTxt(int, int, char*, int);
float __cdecl gm_GetSeasonPrice(int, unsigned char);
void __cdecl d2_FormatCurrencyString(int, unsigned char, char*);
void* __cdecl he_StartHandlungSearch(int, int, int, int, int);
void* __cdecl he_fn_Handlung(void);
int __cdecl d2_GetControlValue(int);
void __cdecl d2_SetElementValue(int, ...);
void __cdecl d2_PositionControl(int, int, int);
int __cdecl sprintf(char*, const char*, ...);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00596d70 */
void __cdecl d2_UpdateProduktionSlotTile(int dialog, int form, PRODUKTION_SLOT_ROW* r, int makeIcon,
                          unsigned int flags, unsigned char* p)
{
	D2_WIN* w;
	char text[0x20];
	char* obj;
	double f;
	int v;
	int n;

	d2_SetForm(dialog, form);
	w = &((D2_WIN*) d2_Windows)[d2_FormPageWindows[dialog * 175 + form]];
	if (r->id != 0) {
		if (r->title == -1) {
			r->title = d2_AddWindowValueGauge(r->x + 6, r->y, 0x30, 0, 100, 0x6a, 0x3d, d2_CurrentWindowId);
		}
		if (r->icon == -1) {
			if (makeIcon) {
				v = 0x8a;
				if (d2_SelectedEntityUiFlags & 0x200) {
					v = 0xca;
				}
				r->icon = d2_AddWindowField(r->x + 0xf, r->y + 6, r->id + 0xdf, v, d2_CurrentWindowId);
				d2_SetElementFont(r->icon, 0x54);
			} else {
				r->icon = d2_AddElementToWindow(r->x + 0xf, r->y + 6, r->id + 0xdf, d2_CurrentWindowId);
				((D2_CONTROL_TL*) (d2_Controls))[r->icon].value_05c = 1;
			}
		}
		if (r->icon2 == -1) {
			if (flags & 1) {
				r->icon2 = d2_AddElementToWindow(r->x + 0xf, r->y + 0x3a, 0x747, d2_CurrentWindowId);
			} else if (flags & 2) {
				r->icon2 = d2_AddElementToWindow(r->x + 0xf, r->y + 0x3a, 0x746, d2_CurrentWindowId);
			}
		}
		if (flags & 2) {
			if (*p == 0x47) {
				f = gm_GetSeasonPrice(r->id, p[0x65]);
			} else if (*((char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*p]) == '\n') {
				f = gm_GetSeasonPrice(r->id, gm_ActiveTownIndex) * 1.1;
			} else {
				f = gm_GetSeasonPrice(r->id, gm_ActiveTownIndex) * *(float*) (p + 0x49);
			}
			d2_FormatCurrencyString((int) f, gm_ActiveTownIndex, text);
			if (r->text1 == -1) {
				r->text1 = d2_ShowTxt(r->x + 0x10, r->y + 0x40, text, d2_CurrentWindowId);
			} else {
				d2_SetLabelText(r->text1, text);
			}
			((D2_CONTROL_TL*) (d2_Controls))[r->text1].width = 0x2d;
			((D2_CONTROL_TL*) (d2_Controls))[r->text1].font = 0x54;
			((D2_CONTROL_TL*) (d2_Controls))[r->text1].value_070 = 1;
		}
		if (flags & 1) {
			if (*p == 0x47) {
				f = gm_GetSeasonPrice(r->id, p[0x65]);
			} else {
				f = gm_GetSeasonPrice(r->id, gm_ActiveTownIndex) * 0.9;
			}
			d2_FormatCurrencyString((int) f, gm_ActiveTownIndex, text);
			if (r->text2 == -1) {
				r->text2 = d2_ShowTxt(r->x + 0x10, r->y + 0x49, text, d2_CurrentWindowId);
			} else {
				d2_SetLabelText(r->text2, text);
			}
			((D2_CONTROL_TL*) (d2_Controls))[r->text2].width = 0x2d;
			((D2_CONTROL_TL*) (d2_Controls))[r->text2].font = 0x54;
			((D2_CONTROL_TL*) (d2_Controls))[r->text2].value_070 = 1;
		}
		obj = (char*) he_StartHandlungSearch(2, 0, 4, 3, *(unsigned int*) (p + 1));
		while (obj != 0) {
			if (*(unsigned short*) (obj + 0xac) == r->id) {
				break;
			}
			obj = (char*) he_fn_Handlung();
		}
		if (obj == 0) {
			obj = (char*) he_StartHandlungSearch(2, 0, 3, 3, *(unsigned int*) (p + 1));
			while (obj != 0) {
				if (*(unsigned short*) (obj + 0xac) == r->id) {
					break;
				}
				obj = (char*) he_fn_Handlung();
			}
		}
		if (obj != 0 && (*(int*) (obj + 0x14) != 0 || *(int*) (obj + 0x18) != 0)) {
			if (*obj == 4) {
				((D2_CONTROL_TL*) (d2_Controls))[r->icon].value_1f4.real =
					1.0 - *(float*) (obj + 0xb4) / *(float*) (obj + 0xb8);
			} else if (*obj == 3) {
				((D2_CONTROL_TL*) (d2_Controls))[r->icon].value_1f4.real =
					1.0 - *(int*) (obj + 0xb0) / *(float*) (obj + 0xb4);
			}
		} else if (r->icon != -1) {
			((D2_CONTROL_TL*) (d2_Controls))[r->icon].value_1f4.bits = 0;
		}
		if (makeIcon) {
			v = d2_GetControlValue(r->icon);
			if (v > r->f30) {
				v = r->f30;
			}
			n = r->f30;
			if (!(d2_SelectedEntityUiFlags & 0x200)) {
				n -= r->f2c;
			}
			n = n < 0 ? 0 : n;
			d2_SetElementValue(r->icon, 0, n, v);
			if (r->f30) {
				((D2_CONTROL_TL*) (d2_Controls))[r->icon].value_060 = 0;
			} else {
				((D2_CONTROL_TL*) (d2_Controls))[r->icon].value_060 = 1;
			}
			v = d2_GetControlValue(r->icon);
			if (v < 0) {
				v = 0;
			}
			d2_SetElementValue(r->title, 0, r->f34, r->f30 - v, r->f2c);
		} else {
			if (r->f30) {
				((D2_CONTROL_TL*) (d2_Controls))[r->icon].value_060 = 0;
			} else {
				((D2_CONTROL_TL*) (d2_Controls))[r->icon].value_060 = 1;
			}
			d2_SetElementValue(r->title, 0, r->f34, r->f30, r->f2c);
		}
		((D2_CONTROL_TL*) (d2_Controls))[r->icon].flags_1d0 = 0x22;
		((D2_CONTROL_TL*) (d2_Controls))[r->icon].value_1dc = 4;
		((D2_CONTROL_TL*) (d2_Controls))[r->icon].value_1e0 = 0;
		sprintf((char*) &((D2_CONTROL_TL*) d2_Controls)[r->icon] + 0xcc, "%s~ %li %s",
				((unsigned int*) d2_ObjektNameTable)[r->id * 2], r->f30, g_14b52c0);
		if (r->icon >= 0) {
			d2_PositionControl(w->left + r->x + 0xf, w->top + r->y + 6, r->icon);
		}
		if (r->icon2 >= 0) {
			d2_PositionControl(w->left + r->x + 0xf, w->top + r->y + 0x3a, r->icon2);
		}
		if (r->text1 >= 0) {
			d2_PositionControl(w->left + r->x + 0x12, w->top + r->y + 0x3f, r->text1);
		}
		if (r->text2 >= 0) {
			d2_PositionControl(w->left + r->x + 0x12, w->top + r->y + 0x49, r->text2);
		}
		if (r->title >= 0) {
			d2_PositionControl(w->left + r->x + 6, w->top + r->y, r->title);
		}
		if (r->obj >= 0) {
			d2_PositionControl(w->left + r->x + 0xf, w->top + r->y + 6,
					*(int*) (d2_Windows + r->obj * 0x3cc + 0x27c));
		}
		return;
	}
	if (r->icon != -1) {
		d2_DestroyElement(r->icon);
		r->icon = -1;
	}
	if (r->icon2 != -1) {
		d2_DestroyElement(r->icon2);
		r->icon2 = -1;
	}
	if (r->text1 != -1) {
		d2_DestroyElement(r->text1);
		r->text1 = -1;
	}
	if (r->text2 != -1) {
		d2_DestroyElement(r->text2);
		r->text2 = -1;
	}
	if (r->title != -1) {
		d2_DestroyElement(r->title);
		r->title = -1;
	}
	if (r->obj != -1) {
		d2_CloseWindow(r->obj);
		r->obj = -1;
	}
}
