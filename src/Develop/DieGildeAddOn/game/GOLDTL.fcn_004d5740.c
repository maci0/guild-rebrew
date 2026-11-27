typedef struct {
	char pad0[0xc];
	int f_c;
} Screen;
// SIZE 0x10

extern char* g_77255c;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* g_1015ea0;
extern char g_6b5c60[];

char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl d2_ShowTxt(int, int, char*, int);
int __cdecl gm_GetScaledEntitySkill(char*, int);
void __cdecl fcn_00534160(int, int, int, int);
float __cdecl gm_GetEntityHealthRatio(char*);
int __cdecl io_FormatTextBuffer(char*, char*, ...);
void __cdecl fcn_0046f940(int, char*);
int* __cdecl gm_GetEquippedCombatGear(char*);
void __cdecl d2_SetElementScale(int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x004d5740 */
void __cdecl d2_DrawCombatParticipants(char* ids, int originX, int originY)
{
	char buf[0x100];
	int total;
	int i;
	int div;
	int id;
	int x;
	int y;
	int h;
	char* rec;
	int* p;
	float f;
	int v;

	total = 0;
	for (i = 0; i < 0x10; i++)
		if (*(int*) (ids + i * 4) != -1)
			total++;
	div = (((Screen*) g_77255c)->f_c - 0x30) / (total + 1);
	for (i = 0; i < 0x10; i++) {
		id = *(int*) (ids + i * 4);
		if (id == -1)
			continue;
		rec = gm_LookupEntityRecordIn32SlotTable(id);
		x = (i % 6 + 1) * div + originX;
		y = originY + (i / 6) * 100;
		d2_AddElementToWindow(x - 0x10, y, 0x5da, d2_CurrentWindowId);
		d2_AddElementToWindow(x - 4, y, *(int*) (rec + 0x18c), d2_CurrentWindowId);
		f = (float) gm_GetScaledEntitySkill(rec, 3);
		fcn_00534160(x, y + 0x3c, (int) f, 0x4eb);
		h = d2_ShowTxt(x - 0x24, y - 0x11, g_6b5c60, d2_CurrentWindowId);
		((D2_CONTROL_TL*) (g_1015ea0))[h].width = 0x78;
		((D2_CONTROL_TL*) (g_1015ea0))[h].value_06c = 1;
		((D2_CONTROL_TL*) (g_1015ea0))[h].font = 0x56;
		io_FormatTextBuffer(buf, "%1N1 %i%", *(unsigned short*) rec,
			     (int) (gm_GetEntityHealthRatio(rec) * 100.0));
		fcn_0046f940(h, buf);
		p = gm_GetEquippedCombatGear(rec);
		if (p != 0 && *p != 0) {
			v = d2_AddElementToWindow(x + 0x28, y + 0xf, *p + 0xdf, d2_CurrentWindowId);
			d2_SetElementScale(v, -2);
		}
		if (*(char*) (rec + 8) == 0) {
			v = (int) -(*(float*) (rec + 0x1c));
			if (*(int*) (rec + 0x24) == (float) v - 20.0) {
				d2_AddElementToWindow(x, y + 6, 0x3b, d2_CurrentWindowId);
			} else {
				d2_AddElementToWindow(x, y + 6, 0x37, d2_CurrentWindowId);
			}
		}
	}
}
