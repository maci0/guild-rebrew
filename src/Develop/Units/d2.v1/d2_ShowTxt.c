/* Private TL field views are inferred from native accesses; they allocate no storage. */
#include <string.h>
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/Units/Error/error_message.h"
#include "Develop/Units/m_alloc/m_alloc.h"

#ifdef REBREW_GOLD
typedef GuiWin D2_TEXT_WINDOW;
typedef GuiEnt D2_TEXT_ENTRY;
typedef short D2_TEXT_COORD;

extern GuiWin g_00f8f120[];
extern short g_00f8f084;
extern short g_005fe73c;
extern char s_5fe7ac[];

int __cdecl fcn_0046c9e0(void);
int __cdecl fcn_0046ea00(char* text, int font);
void __cdecl fcn_004730d0(int id, GuiWin* parent);

#define d2_TEXT_WINDOWS g_00f8f120
#define d2_TEXT_ENTRIES g_00f8f080
#define d2_TEXT_ERROR s_5fe7ac
#define d2_TEXT_DEFAULT_FONT g_005fe73c
#define d2_TEXT_TAG "d2:ShowTxt"
#define d2_TEXT_ALLOCATE_INDEX fcn_0046c9e0
#define d2_TEXT_MEASURE fcn_0046ea00
#define d2_TEXT_INSERT fcn_004730d0
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

typedef struct D2_TEXT_ENTRY {
	char pad00[0xc];
	char* data;
	int x;
	int y;
	int w;
	int f16;
	int kind;
	int f1c;
	int f1e;
	int f20;
	int f22;
	int f24;
	char pad38[0x40 - 0x38];
	D2_TEXT_WINDOW* parent;
	char pad44[0x50 - 0x44];
	int f40;
	char pad54[0x84 - 0x54];
	int font;
	int bild_offset;
	char pad8c[0x2f4 - 0x8c];
} D2_TEXT_ENTRY;

typedef int D2_TEXT_COORD;

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int g_67d398;
extern char g_67d5bc[];
extern char s_67d420[];

int __cdecl fcn_00469890(void);
int __cdecl fcn_0046b520(char* text, int font);
void __cdecl fcn_0046f650(int slot, D2_TEXT_WINDOW* parent);

#define d2_TEXT_WINDOWS ((D2_TEXT_WINDOW*)g_1015f40)
#define d2_TEXT_ENTRIES ((D2_TEXT_ENTRY*)g_1015ea0)
#define d2_TEXT_ERROR s_67d420
#define d2_TEXT_DEFAULT_FONT g_67d398
#define d2_TEXT_TAG g_67d5bc
#define d2_TEXT_ALLOCATE_INDEX fcn_00469890
#define d2_TEXT_MEASURE fcn_0046b520
#define d2_TEXT_INSERT fcn_0046f650
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
	d2_TEXT_ENTRIES[id].bild_offset = (int) m_alloc(0x101, d2_TEXT_TAG);
	if (d2_TEXT_ENTRIES[id].bild_offset == 0) {
		return -1;
	}
	strcpy((char*) d2_TEXT_ENTRIES[id].bild_offset, text);
	if (w->font != 0) {
		d2_TEXT_ENTRIES[id].font = w->font;
	} else {
		d2_TEXT_ENTRIES[id].font = d2_TEXT_DEFAULT_FONT;
	}
	d2_TEXT_ENTRIES[id].kind = 0x43;
	d2_TEXT_ENTRIES[id].x = w->x + x;
	d2_TEXT_ENTRIES[id].y = w->y - w->scroll + y;
	d2_TEXT_ENTRIES[id].w = d2_TEXT_MEASURE(text, d2_TEXT_ENTRIES[id].font) + 0x60;
#ifdef REBREW_GOLD
	d2_TEXT_ENTRIES[id].f16 = g_00f8f084;
#else
	d2_TEXT_ENTRIES[id].f16 = *(unsigned short*) ((char*) d2_GetResourceData(d2_TEXT_ENTRIES[id].font) + 8);
#endif
	d2_TEXT_ENTRIES[id].f1c = 2;
	d2_TEXT_ENTRIES[id].parent = w;
	d2_TEXT_ENTRIES[id].data = (char*) w;
	d2_TEXT_ENTRIES[id].f22 = w->y;
	d2_TEXT_ENTRIES[id].f24 = w->height + w->y;
	d2_TEXT_ENTRIES[id].f1e = w->x;
	d2_TEXT_ENTRIES[id].f20 = w->width + w->x;
	d2_TEXT_ENTRIES[id].f40 = d2_TEXT_ENTRIES[w->id].f40;
#ifdef REBREW_GOLD
	*(unsigned char*) ((char*) &d2_TEXT_ENTRIES[id] + 0x7c) = 0;
	if (d2_TEXT_ENTRIES[id].f16 + y > *(int*) ((char*) w + 0x244)) {
		*(int*) ((char*) w + 0x244) = d2_TEXT_ENTRIES[id].f16 + y;
	}
#else
	if (d2_TEXT_ENTRIES[id].f16 + y > w->max_height) {
		w->max_height = d2_TEXT_ENTRIES[id].f16 + y;
	}
#endif
	d2_TEXT_INSERT(id, w);
	w->list[w->count] = id;
	w->count++;
	return id;
}
