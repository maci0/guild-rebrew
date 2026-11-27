#include "Develop/Units/d2.v1/d2_gui.h"

#if defined(REBREW_GOLD)
int __cdecl d2_GetResourceBankEntry(int, unsigned int);
int __cdecl d2_CalcTextWidth(const char*, int);
int __cdecl d2_QueryElementResourceSize(int, int*, int*);
#include <string.h>

/* ADDRESS: GOLD 0x00473530 */
void __cdecl d2_SetControlText(int id, char* text)
{
    GuiEnt* entry;
    char* left;
    char* right;
    int offset;
    int unused;
    int width;
    int data;

    offset = id * 0x2ec;
    entry = (GuiEnt*) ((char*) g_00f8f080 + offset);
    if (entry->kind == 9) {
        data = (int) entry->data;
        left = (char*) d2_GetResourceBankEntry(data, 0);
        right = (char*) d2_GetResourceBankEntry(data, 1);
        id = d2_CalcTextWidth(text, *(int*) 0x5fe73c)
            + *(unsigned short*) (right + 6) + 4
            + *(unsigned short*) (left + 6);
        strncpy((char*) entry + 0x7c, text, 0x3f);
        ((GuiEnt*) ((char*) g_00f8f080 + offset))->w = (short) id;
        return;
    }
    if (!d2_QueryElementResourceSize(id, &id, &unused))
        id = 0x18;
    strncpy((char*) g_00f8f080 + offset + 0x7c, text, 0x3f);
    entry = (GuiEnt*) ((char*) g_00f8f080 + offset);
    if (*(int*) ((char*) entry + 0x5c) == 0) {
        width = d2_CalcTextWidth(text, entry->font) + 6 + id;
        ((GuiEnt*) ((char*) g_00f8f080 + offset))->w = (short) width;
    } else {
        entry->w = (short) id;
    }
}
#else
typedef struct
{
	int i[0x2f4 / 4];
} D2_CTRL_TEXT_ENT;
// SIZE 0x2f4

extern char* g_1015ea0;
#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl d2_GetBankEntry(int p, int i);
int __cdecl d2_MeasureTextWidth(char* s, int font);
int __cdecl d2_GetElementResourceSize(int slot, int* w, int* h);
void __cdecl fcn_0064d530(char* dst, char* src, int n);
/* ADDRESS: GOLDTL 0x0046f9b0 */
void __cdecl d2_SetControlText(int idx, char* text)
{
	D2_CTRL_TEXT_ENT* e;
	int w;
	int h;
	int c;
	char* p0;
	char* p1;

	e = (D2_CTRL_TEXT_ENT*) &((D2_CONTROL_TL*) g_1015ea0)[idx];
	if (((D2_CONTROL_TL*) e)->kind == 9) {
		c = *(int*) &((D2_CONTROL_TL*) e)->data;
		p0 = d2_GetBankEntry(c, 0);
		p1 = d2_GetBankEntry(c, 1);
		w = d2_MeasureTextWidth(text, d2_DefaultFont) + *(unsigned short*) (p1 + 2) + *(unsigned short*) (p0 + 2) + 4;
		fcn_0064d530((char*) e + 0x8c, text, 0x3f);
		((D2_CONTROL_TL*) g_1015ea0)[idx].width = w;
		return;
	}
	if (d2_GetElementResourceSize(idx, &w, &h) == 0) {
		w = 0x18;
	}
	fcn_0064d530((char*) (D2_CTRL_TEXT_ENT*) &((D2_CONTROL_TL*) g_1015ea0)[idx] + 0x8c, text, 0x3f);
	if (((D2_CONTROL_TL*) g_1015ea0)[idx].value_06c == 0) {
		((D2_CONTROL_TL*) g_1015ea0)[idx].width = d2_MeasureTextWidth(text, ((D2_CONTROL_TL*) g_1015ea0)[idx].font) + w + 6;
	} else {
		((D2_CONTROL_TL*) g_1015ea0)[idx].width = w;
	}
}
#endif
