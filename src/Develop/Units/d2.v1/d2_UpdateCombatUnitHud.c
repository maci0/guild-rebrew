#include <stdio.h>

typedef struct {
	int icon;
	int frame;
	int win;
	int unused0c;
	int text;
	int name;
	int label;
	char* unit;
} GUI_ENTRY;
/* SIZE 0x20 */

extern GUI_ENTRY d2_CombatUnitCards[6];
extern char d2_WindowElementIdView[];
#include "Develop/Units/d2.v1/d2_gui.h"
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;
extern int d2_CurrentWindowId;
extern char str_empty[];
extern double g_662c38;
extern char g_67d444[];

void __cdecl ResetDisplayCounters(void);
void __cdecl d2_AddDisplayCounter(int, int);
void __cdecl d2_SetElementValue(int, ...);
float __cdecl gm_GetEntityHealthRatio(char*);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
void __cdecl d2_SetLabelText(int, char*);
int __cdecl gm_GetUnitWeaponSpec(char*);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_SetElementScale(int, int);
char* __cdecl gm_FindEntityActiveItem(char*);
void __cdecl d2_DestroyElement(int);
void __cdecl d2_SetSlotVisibility(int, int);

/* ADDRESS: GOLDTL 0x004d0a20 */
void __cdecl d2_UpdateCombatUnitHud(void)
{
	char buf[0x100];
	GUI_ENTRY* q;
	char* v;
	int* r;

	if (d2_DialogButtonAction != -1) {
		q = d2_CombatUnitCards;
		do {
			if (q->win != -1 && d2_CurrentElementId == q->icon) {
				if (*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[q->icon].value_038)) != 0) {
					*(char*) ((int) q->unit + 0x188) = 1;
				} else {
					*(char*) ((int) q->unit + 0x188) = 0;
				}
			}
			q++;
		} while ((int) q < 0x9b4900);
	}
	ResetDisplayCounters();
	*(int*) 0x772eb8 = 0;
	q = d2_CombatUnitCards;
	do {
		if (q->win != -1) {
			v = q->unit;
			if (*(int*) (*(int*) (*(int*) (v + 0x184) + 0x34) + 0x218) == 1) {
				d2_SetSlotVisibility(*(int*) (d2_WindowElementIdView + q->win * 0x3cc), 0);
				d2_SetSlotVisibility(*(int*) (d2_WindowElementIdView + q->frame * 0x3cc), 0);
			} else {
				if (*(char*) (v + 0x188) != 0) {
					d2_AddDisplayCounter(*(int*) (v + 0x18c), 1);
					d2_SetElementValue(q->icon, 1);
					*(int*) 0x772eb8 += 1;
				} else {
					d2_SetElementValue(q->icon, 0);
				}
				io_FormatTextBuffer(buf, (char*) 0x68b838, *(unsigned short*) q->unit,
					(int) (gm_GetEntityHealthRatio(q->unit) * g_662c38));
				d2_SetLabelText(q->text, buf);
				r = (int*) gm_GetUnitWeaponSpec(q->unit);
				if (r != 0 && *r != 0) {
					if (q->name != -1) {
						if (*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[q->name].value_008)) != *r + 0xdf) {
							if (q->name != -1) {
								d2_DestroyElement(q->name);
							}
							goto relabel;
						}
					} else {
relabel:
						d2_CurrentWindowId = q->win;
						d2_SetElementScale(q->name = d2_AddElementToWindow(0x54, 0xf,
							*r + 0xdf, d2_CurrentWindowId), 0xfffffffe);
					}
					if (q->label != -1) {
						if (*(int*) (r + 0x16) == 1 || *(int*) (r + 0x16) == 2) {
							v = gm_FindEntityActiveItem(q->unit);
							if (v != 0) {
								sprintf(buf, "%i", *(int*) (v + 0x20));
								d2_SetLabelText(q->label, buf);
								goto next;
							}
						}
						if (q->label != -1) {
							d2_SetLabelText(q->label, str_empty);
						}
					}
				}
			}
		}
next:
		q++;
	} while ((int) q < 0x9b4900);
}
