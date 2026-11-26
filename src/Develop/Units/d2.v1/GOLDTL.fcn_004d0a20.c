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

extern GUI_ENTRY g_9b4840[6];
extern char g_10161bc[];
#include "Develop/Units/d2.v1/d2_gui.h"
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern int d2_CurrentWindowId;
extern char g_6b5c60[];
extern double g_662c38;
extern char g_67d444[];

void __cdecl ResetDisplayCounters(void);
void __cdecl fcn_00473690(int, int);
void __cdecl d2_SetElementValue(int, ...);
float __cdecl fcn_004ff040(char*);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
void __cdecl fcn_0046f940(int, char*);
int __cdecl gm_GetUnitWeaponSpec(char*);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl fcn_00472680(int, int);
char* __cdecl gm_FindEntityActiveItem(char*);
void __cdecl d2_DestroyElement(int);
void __cdecl d2_SetSlotVisibility(int, int);

/* ADDRESS: GOLDTL 0x004d0a20 */
void __cdecl fcn_004d0a20(void)
{
	char buf[0x100];
	GUI_ENTRY* q;
	char* v;
	int* r;

	if (g_100f1dc != -1) {
		q = g_9b4840;
		do {
			if (q->win != -1 && d2_CurrentElementId == q->icon) {
				if (*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[q->icon].value_038)) != 0) {
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
	q = g_9b4840;
	do {
		if (q->win != -1) {
			v = q->unit;
			if (*(int*) (*(int*) (*(int*) (v + 0x184) + 0x34) + 0x218) == 1) {
				d2_SetSlotVisibility(*(int*) (g_10161bc + q->win * 0x3cc), 0);
				d2_SetSlotVisibility(*(int*) (g_10161bc + q->frame * 0x3cc), 0);
			} else {
				if (*(char*) (v + 0x188) != 0) {
					fcn_00473690(*(int*) (v + 0x18c), 1);
					d2_SetElementValue(q->icon, 1);
					*(int*) 0x772eb8 += 1;
				} else {
					d2_SetElementValue(q->icon, 0);
				}
				io_FormatTextBuffer(buf, (char*) 0x68b838, *(unsigned short*) q->unit,
					(int) (fcn_004ff040(q->unit) * g_662c38));
				fcn_0046f940(q->text, buf);
				r = (int*) gm_GetUnitWeaponSpec(q->unit);
				if (r != 0 && *r != 0) {
					if (q->name != -1) {
						if (*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[q->name].value_008)) != *r + 0xdf) {
							if (q->name != -1) {
								d2_DestroyElement(q->name);
							}
							goto relabel;
						}
					} else {
relabel:
						d2_CurrentWindowId = q->win;
						fcn_00472680(q->name = d2_AddElementToWindow(0x54, 0xf,
							*r + 0xdf, d2_CurrentWindowId), 0xfffffffe);
					}
					if (q->label != -1) {
						if (*(int*) (r + 0x16) == 1 || *(int*) (r + 0x16) == 2) {
							v = gm_FindEntityActiveItem(q->unit);
							if (v != 0) {
								sprintf(buf, "%i", *(int*) (v + 0x20));
								fcn_0046f940(q->label, buf);
								goto next;
							}
						}
						if (q->label != -1) {
							fcn_0046f940(q->label, g_6b5c60);
						}
					}
				}
			}
		}
next:
		q++;
	} while ((int) q < 0x9b4900);
}
