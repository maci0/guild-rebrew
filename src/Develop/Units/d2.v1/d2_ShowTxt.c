/* Private TL field views are inferred from native accesses; they allocate no storage. */
#include <string.h>
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/Units/Error/error_message.h"
#include "Develop/Units/m_alloc/m_alloc.h"

#ifdef REBREW_GOLD
typedef GuiWin D2_TEXT_WINDOW;
typedef GuiEnt D2_TEXT_ENTRY;
#define D2E_w w
#define D2E_f16 f16
#define D2E_f1c f1c
#define D2E_f1e f1e
#define D2E_f20 f20
#define D2E_f22 f22
#define D2E_f24 f24
#define D2E_f40 f40
#define D2E_bild_offset bild_offset
typedef short D2_TEXT_COORD;

extern GuiWin g_00f8f120[];
extern short g_00f8f084;
extern short g_005fe73c;
extern char s_5fe7ac[];

int __cdecl d2_AllocGuiElement(void);
int __cdecl d2_CalcTextWidth(char* text, int font);
void __cdecl d2_ReorderControlInWindow(int id, GuiWin* parent);

#define d2_TEXT_WINDOWS g_00f8f120
#define d2_TEXT_ENTRIES g_00f8f080
#define d2_TEXT_ERROR s_5fe7ac
#define d2_TEXT_DEFAULT_FONT g_005fe73c
#define d2_TEXT_TAG "d2:ShowTxt"
#define d2_TEXT_ALLOCATE_INDEX d2_AllocGuiElement
#define d2_TEXT_MEASURE d2_CalcTextWidth
#define d2_TEXT_INSERT d2_ReorderControlInWindow
#else
/* Field spellings follow the existing Gold view's roles, not TL offsets. */
typedef struct D2_TEXT_WINDOW {
	char pad00[4];
	int x;
	int y;
	int width;
	int height;
	char pad14[0x28 - 0x14];
	int* list;
	int count;
	char pad30[0x254 - 0x30];
	int max_height;
	int scroll;
	char pad25c[0x27c - 0x25c];
	int id;
	char pad280[0x28c - 0x280];
	int font;
	int active;
	char pad294[0x3cc - 0x294];
} D2_TEXT_WINDOW;

typedef D2_CONTROL_TL D2_TEXT_ENTRY;
#define D2E_w width
#define D2E_f16 height
#define D2E_f1c mode
#define D2E_f1e clip_left
#define D2E_f20 clip_right
#define D2E_f22 clip_top
#define D2E_f24 clip_bottom
#define D2E_f40 value_050
#define D2E_bild_offset value_088




typedef int D2_TEXT_COORD;

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int d2_DefaultFont;
extern char g_67d5bc[];
extern char s_67d420[];

int __cdecl d2_AllocateElement(void);
int __cdecl d2_MeasureTextWidth(char* text, int font);
void __cdecl d2_InsertControlAfterWindow(int slot, D2_TEXT_WINDOW* parent);

#define d2_TEXT_WINDOWS ((D2_TEXT_WINDOW*)g_1015f40)
#define d2_TEXT_ENTRIES ((D2_TEXT_ENTRY*)g_1015ea0)
#define d2_TEXT_ERROR s_67d420
#define d2_TEXT_DEFAULT_FONT d2_DefaultFont
#define d2_TEXT_TAG g_67d5bc
#define d2_TEXT_ALLOCATE_INDEX d2_AllocateElement
#define d2_TEXT_MEASURE d2_MeasureTextWidth
#define d2_TEXT_INSERT d2_InsertControlAfterWindow
#endif

#ifdef REBREW_GOLD
typedef char D2_TEXT_WINDOW_SIZE_CHECK[sizeof(D2_TEXT_WINDOW) == 0x3c4 ? 1 : -1];
typedef char D2_TEXT_ENTRY_SIZE_CHECK[sizeof(D2_TEXT_ENTRY) == 0x2ec ? 1 : -1];
#else
typedef char D2_TEXT_WINDOW_SIZE_CHECK[sizeof(D2_TEXT_WINDOW) == 0x3cc ? 1 : -1];
typedef char D2_TEXT_ENTRY_SIZE_CHECK[sizeof(D2_TEXT_ENTRY) == 0x2f4 ? 1 : -1];
#endif

/* Inferred from allocation label d2:ShowTxt, not an attested C identifier. */
/* ADDRESS: GOLD 0x00473640 */
/* ADDRESS: GOLDTL 0x0046fac0 */
int __cdecl d2_ShowTxt(D2_TEXT_COORD x, D2_TEXT_COORD y, char* text, int win)
{
	D2_TEXT_WINDOW* w;
	int id;

	w = &d2_TEXT_WINDOWS[win];
	if (w->active == 0) {
		return -1;
	}
	if (w->count >= 0x180) {
		ReportClientMessage(d2_TEXT_ERROR);
		return -1;
	}
	id = d2_TEXT_ALLOCATE_INDEX();
	d2_TEXT_ENTRIES[id].D2E_bild_offset = (int) m_alloc(0x101, d2_TEXT_TAG);
	if (d2_TEXT_ENTRIES[id].D2E_bild_offset == 0) {
		return -1;
	}
	strcpy((char*) d2_TEXT_ENTRIES[id].D2E_bild_offset, text);
	if (w->font != 0) {
		d2_TEXT_ENTRIES[id].font = w->font;
	} else {
		d2_TEXT_ENTRIES[id].font = d2_TEXT_DEFAULT_FONT;
	}
	d2_TEXT_ENTRIES[id].kind = 0x43;
	d2_TEXT_ENTRIES[id].x = w->x + x;
	d2_TEXT_ENTRIES[id].y = w->y - w->scroll + y;
	d2_TEXT_ENTRIES[id].D2E_w = d2_TEXT_MEASURE(text, d2_TEXT_ENTRIES[id].font) + 0x60;
#ifdef REBREW_GOLD
	d2_TEXT_ENTRIES[id].D2E_f16 = g_00f8f084;
#else
	d2_TEXT_ENTRIES[id].D2E_f16 = *(unsigned short*) ((char*) d2_GetResourceData(d2_TEXT_ENTRIES[id].font) + 8);
#endif
	d2_TEXT_ENTRIES[id].D2E_f1c = 2;
	d2_TEXT_ENTRIES[id].parent = w;
	d2_TEXT_ENTRIES[id].data = (char*) w;
	d2_TEXT_ENTRIES[id].D2E_f22 = w->y;
	d2_TEXT_ENTRIES[id].D2E_f24 = w->height + w->y;
	d2_TEXT_ENTRIES[id].D2E_f1e = w->x;
	d2_TEXT_ENTRIES[id].D2E_f20 = w->width + w->x;
	d2_TEXT_ENTRIES[id].D2E_f40 = d2_TEXT_ENTRIES[w->id].D2E_f40;
#ifdef REBREW_GOLD
	*(unsigned char*) ((char*) &d2_TEXT_ENTRIES[id] + 0x7c) = 0;
	if (d2_TEXT_ENTRIES[id].D2E_f16 + y > *(int*) ((char*) w + 0x244)) {
		*(int*) ((char*) w + 0x244) = d2_TEXT_ENTRIES[id].D2E_f16 + y;
	}
#else
	if (d2_TEXT_ENTRIES[id].D2E_f16 + y > w->max_height) {
		w->max_height = d2_TEXT_ENTRIES[id].D2E_f16 + y;
	}
#endif
	d2_TEXT_INSERT(id, w);
	w->list[w->count] = id;
	w->count++;
	return id;
}
