#include "Develop/Units/d2.v1/gold_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"
#include "Develop/Units/d2.v1/d2_win.h"
#include "Develop/client_types.h"
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/Units/Error/error_message.h"

// SIZE 0x3cc
typedef struct
{
	int i[0x2f4 / 4];
} D2_WIN_IMAGE_ENT;
// SIZE 0x2f4

extern GOLD_GUI_WINDOW g_00f8f120[];
extern GuiEnt* g_00f8f080;
extern short g_00fb9070;
extern short g_00fb9072;
extern Win_1015f40 d2_Windows[0x60];
extern int d2_ScreenHeight;
extern int g_1040494;
extern char s_67d420[];

int __cdecl d2_CreateElementAt(short, short, int);
void __cdecl d2_ReorderControlInWindow(int, GuiWin*);
void __cdecl d2_SetElementScale(int id, int a2);
void __cdecl d2_GetWindowBorderSize(GuiWin*, int*, int*);
int __cdecl d2_CreateElement(int x, int y, int a3);
void __cdecl d2_InsertControlAfterWindow(int slot, void* parent);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00473340 */
int __cdecl d2_AddWindowImage(int x, int y, int image, int window_id, int context)
{
    GOLD_GUI_WINDOW* window;
    int element;

    window = &g_00f8f120[window_id];
    if (window->active == 0) {
        return -1;
    }
    if (window->count >= 0x180) {
        ReportClientMessage("Too many objects on window!");
        return -1;
    }
    window->list[window->count] = d2_CreateElementAt((short)(window->x + x), (short)(window->y - (short) window->scroll + y), image);
    element = window->list[window->count];
    if (element != -1) {
        d2_ReorderControlInWindow(element, (void*) window);
        g_00f8f080[element].parent = (void*) window;
        g_00f8f080[element].f22 = 0;
        g_00f8f080[element].f24 = g_00fb9070;
        g_00f8f080[element].f1e = 0;
        g_00f8f080[element].f20 = g_00fb9072;
        g_00f8f080[element].f40 = g_00f8f080[window->id].f40;
        *(int*)((char*)&g_00f8f080[element] + 0x38) = *(int*)((char*)&g_00f8f080[window->id] + 0x38);
        d2_SetElementScale(element, context);
        window->count++;
        d2_GetWindowBorderSize((void*) window, &x, &window_id);
        if ((short)y + g_00f8f080[element].f16 > *(int*)((char*)window + 0x244)) {
            *(int*)((char*)window + 0x244) = (short)y + x * 2 + g_00f8f080[element].f16;
        }
    }
    return element;
}
#else
/* ADDRESS: GOLDTL 0x0046f7e0 */
int __cdecl d2_AddWindowImage(int x, int y, int resourceId, int win, int scaleType)
{
	D2_WIN* w;
	int id;

	w = &((D2_WIN*)d2_Windows)[win];
	if (w->active == 0) {
		return -1;
	}
	if (w->count >= 0x180) {
		ReportClientMessage(s_67d420);
		return -1;
	}
	w->children[w->count] = d2_CreateElement((short) (w->left + x), (short) (w->top - (*(int*) &w->pad3c[0x21c]) + y), resourceId);
	id = w->children[w->count];
	if (id != -1) {
		d2_InsertControlAfterWindow(id, w);
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].parent) = (int) w;
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].clip_top) = 0;
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].clip_bottom) = d2_ScreenHeight;
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].clip_left) = 0;
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].clip_right) = g_1040494;
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].value_050) = (*(int*)&((D2_CONTROL_TL*)d2_Controls)[w->slot].value_050);
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].value_048) = (*(int*)&((D2_CONTROL_TL*)d2_Controls)[w->slot].value_048);
		d2_SetElementScale(id, scaleType);
		w->count++;
		if ((*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].height) + y > (*(int*) &w->pad3c[0x218])) {
			(*(int*) &w->pad3c[0x218]) = (*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].height) + y;
		}
	}
	return id;
}
#endif
