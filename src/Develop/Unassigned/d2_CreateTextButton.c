#include "gold_gui.h"

typedef struct
{
	char pad00[0x52];
	short f52;
} D2_RES_DEF;
// SIZE 0x54

typedef struct
{
	int i[0x2f4 / 4];
} D2_TEXT_BTN_ENT;
// SIZE 0x2f4

typedef struct
{
	char pad00[0x52];
	short f52;
} D2_TEXT_BTN_DEF;
// SIZE 0x54

extern GuiEnt* g_00f8f080; /* 0x00f8f080 */
extern D2_RES_DEF* g_006ed918; /* 0x006ed918 */
extern short g_00fb9070; /* 0x00fb9070 */
extern short g_00fb9072; /* 0x00fb9072 */
extern short g_005fe73c; /* 0x005fe73c */

extern char* g_1015ea0;
extern char* g_772500;
extern int d2_ScreenHeight;
extern int g_1040494;
extern int d2_DefaultFont;

int __cdecl d2_AllocGuiElement(void);
int __cdecl d2_AllocateElement(void);
int __cdecl d2_GetResourceData(int);
void __cdecl d2_SetControlText(int, int);
void __cdecl d2_AddRefcount(int);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x0046bdf0 */
int __cdecl d2_CreateTextButton(int x, int y, int a3, int a4)
{
	int idx;

	idx = d2_AllocGuiElement();
	g_00f8f080[idx].kind = 9;
	g_00f8f080[idx].f4c = 1;
	g_00f8f080[idx].flags = 3;
	g_00f8f080[idx].x = x;
	g_00f8f080[idx].f16 = g_006ed918[a3].f52;
	g_00f8f080[idx].y = y;
	g_00f8f080[idx].f08 = a3;
	g_00f8f080[idx].f22 = 0;
	g_00f8f080[idx].f24 = g_00fb9070;
	g_00f8f080[idx].f1e = 0;
	g_00f8f080[idx].f20 = g_00fb9072;
	g_00f8f080[idx].font = g_005fe73c;
	g_00f8f080[idx].data = (char*) d2_GetResourceData(a3);
	d2_SetControlText(idx, a4);
	d2_AddRefcount(a3);
	return idx;
}
#else
/* ADDRESS: GOLDTL 0x00468cf0 */
int __cdecl d2_CreateTextButton(int x, int y, int resourceId, int text)
{
	int idx;

	idx = d2_AllocateElement();
	((D2_TEXT_BTN_ENT*)g_1015ea0)[idx].i[0x20 / 4] = 9;
	((D2_TEXT_BTN_ENT*)g_1015ea0)[idx].i[0x5c / 4] = 1;
	((D2_TEXT_BTN_ENT*)g_1015ea0)[idx].i[0x1d0 / 4] = 3;
	((D2_TEXT_BTN_ENT*)g_1015ea0)[idx].i[0x10 / 4] = x;
	((D2_TEXT_BTN_ENT*)g_1015ea0)[idx].i[0x1c / 4] = ((D2_TEXT_BTN_DEF*)g_772500)[resourceId].f52;
	((D2_TEXT_BTN_ENT*)g_1015ea0)[idx].i[0x14 / 4] = y;
	((D2_TEXT_BTN_ENT*)g_1015ea0)[idx].i[0x8 / 4] = resourceId;
	((D2_TEXT_BTN_ENT*)g_1015ea0)[idx].i[0x30 / 4] = 0;
	((D2_TEXT_BTN_ENT*)g_1015ea0)[idx].i[0x34 / 4] = d2_ScreenHeight;
	((D2_TEXT_BTN_ENT*)g_1015ea0)[idx].i[0x28 / 4] = 0;
	((D2_TEXT_BTN_ENT*)g_1015ea0)[idx].i[0x2c / 4] = g_1040494;
	((D2_TEXT_BTN_ENT*)g_1015ea0)[idx].i[0x84 / 4] = d2_DefaultFont;
	((D2_TEXT_BTN_ENT*)g_1015ea0)[idx].i[0xc / 4] = d2_GetResourceData(resourceId);
	d2_SetControlText(idx, text);
	d2_AddRefcount(resourceId);
	return idx;
}
#endif
