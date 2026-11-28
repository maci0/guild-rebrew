#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl d2_SetForm(int win, int layer);
int __cdecl d2_AddElementToWindow(int x, int y, int id, int win);
int __cdecl d2_PositionControl(int x, int y, int slot);
int __cdecl d2_GetControlValue(int element);
void __cdecl d2_SetDisplayCounter(int id, int value);
void __cdecl ResetDisplayCounters(void);
void __cdecl d2_UpdateProduktionSlotTile(int a0, int a1, int* rect, int w, int n,
                          unsigned int a5);

/* ADDRESS: GOLDTL 0x005963f0 */
/* ADDRESS: GOLDDE 0x0057beb0 */
void __cdecl d2_RefreshWorkshopInventoryGrids(int dialog, int form, int a2, unsigned int a3)
{
	int idx;
	int v1;
	int i;
	int n;
	int k;
	int* p;
	int* v;
	char* tbl;

	idx = *(int*) ((form + dialog * 0xaf) * 4 + 0x1038144);
	p = (int*) 0x1015f40 + idx * 0xf3;
	v1 = p[3];

	d2_SetForm(dialog, form);

	for (v = (int*) 0x778d50; (int) v < 0x778da0; v += 5) {
		if (*v == -1) {
			*v = d2_AddElementToWindow(0, 0, 0x743, *(int*) 0x772514);
		}
	}

	d2_SetForm(dialog, form);

	for (v = (int*) 0x779130; (int) v < 0x779158; v += 5) {
		if (*v == -1) {
			*v = d2_AddElementToWindow(0, 0, 0x743, *(int*) 0x772514);
		}
	}

	i = 0;
	v = (int*) 0x778d4c;
	do {
		if (v[-1] != *v) {
			d2_SetElementImage(v[1], *v + 0x741);
		}
		v[-1] = *v;
		if (*v > 1) {
			tbl = d2_FileObjTable;
			v[-3] = (v1 - *(short*) (tbl + 0x261a4 + *v * 0x54)) >> 1;
			v[-2] = (*(short*) (tbl + 0x2624e) + 0x16) * i;
		}
		v += 5;
		i++;
	} while ((int) v < 0x778d9c);

	i = 0;
	v = (int*) 0x77912c;
	do {
		if (v[-1] != *v) {
			d2_SetElementImage(v[1], *v + 0x741);
		}
		v[-1] = *v;
		if (*v >= 2) {
			tbl = d2_FileObjTable;
			v[-3] = (v1 - *(short*) (tbl + 0x261a4 + *v * 0x54)) >> 1;
			v[-2] = (*(short*) (tbl + 0x2624e) + 0x16) * i + 0xb6;
		}
		v += 5;
		i++;
	} while ((int) v < 0x779154);

	d2_SetForm(dialog, form);

	for (v = (int*) 0x778d50; (int) v < 0x778da0; v += 5) {
		if (v[-2] > 1) {
			((D2_CONTROL_TL*) (d2_Controls))[*v].value_048 = 0;
			d2_PositionControl(v[-4] + p[1], v[-3] + p[2], *v);
		} else {
			((D2_CONTROL_TL*) (d2_Controls))[*v].value_048 = 1;
		}
	}

	k = 0;
	n = 0;
	v = (int*) 0x778dac;
	do {
		n++;
		if (n > *(int*) ((char*) 0x778d48 + k * 0x14)) {
			n = 1;
			do {
				k++;
			} while (*(int*) ((char*) 0x778d48 + k * 0x14) < 1);
		}
		v[-1] = *(int*) ((char*) 0x778d40 + k * 0x14) + n * 0x44 - 0x44;
		*v = *(int*) ((char*) 0x778d44 + k * 0x14);
		d2_UpdateProduktionSlotTile(dialog, form, v - 3, a2, 2, a3);
		v += 0xe;
	} while ((int) v < 0x77912c);

	d2_SetForm(dialog, form);

	for (v = (int*) 0x77912c; (int) v < 0x779154; v += 5) {
		if (v[-1] != *v) {
			d2_SetElementImage(v[1], *v + 0x741);
		}
		v[-1] = *v;
		if (*v >= 2) {
			((D2_CONTROL_TL*) (d2_Controls))[v[1]].value_048 = 0;
			d2_PositionControl(v[-3] + p[1], v[-2] + p[2], v[1]);
		} else {
			((D2_CONTROL_TL*) (d2_Controls))[v[1]].value_048 = 1;
		}
	}

	n = 0;
	k = 0;
	v = (int*) 0x7796ec;
	do {
		n++;
		if (n > *(int*) ((char*) 0x779128 + k * 0x14)) {
			n = 1;
			do {
				k++;
			} while (*(int*) ((char*) 0x779128 + k * 0x14) < 1);
		}
		v[-1] = *(int*) ((char*) 0x779120 + k * 0x14) + n * 0x44 - 0x44;
		*v = *(int*) ((char*) 0x779124 + k * 0x14);
		d2_UpdateProduktionSlotTile(dialog, form, v - 3, a2, 2, a3);
		v += 0xe;
	} while ((int) v < 0x7798ac);

	if (a2) {
		ResetDisplayCounters();
		for (v = (int*) 0x778db0; (int) v < 0x779130; v += 0xe) {
			if (*v != -1) {
				d2_SetDisplayCounter(v[-4] + 0xdf, d2_GetControlValue(*v));
			}
		}
		for (v = (int*) 0x7796f0; (int) v < 0x7798b0; v += 0xe) {
			if (*v != -1) {
				d2_SetDisplayCounter(v[-4] + 0xdf, d2_GetControlValue(*v));
			}
		}
	}
}
