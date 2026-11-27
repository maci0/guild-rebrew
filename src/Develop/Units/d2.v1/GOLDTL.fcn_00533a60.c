#include <stdarg.h>
#include <string.h>
#include "client_types.h"
#include "Develop/Units/d2.v1/d2_win.h"

extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;

int __cdecl d2_MeasureTextWidth(char* s, int font);
int __cdecl d2_AddWindowTextButton(int a1, int a2, int a3, int a4, int i);
void __cdecl d2_SetElementWidth(int a1, int a2);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00533a60 */
void __cdecl d2_CreateButtonRow(int windowId, int y, int* outIds, int labelCount, ...)
{
	D2_WIN* winp;
	va_list ap;
	char buf[32][64];
	char* src;
	int maxw;
	int i;
	int w;
	int step;
	int start;

	winp = &((D2_WIN*) g_1015f40)[windowId];
	maxw = 0;
	va_start(ap, labelCount);
	for (i = 0; i < labelCount; i++) {
		src = va_arg(ap, char*);
		strcpy(buf[i], src);
		w = d2_MeasureTextWidth(src, *(int*) ((char*) winp + 0x28c)) + 0x20;
		if (w > maxw) {
			maxw = w;
		}
	}
	va_end(ap);
	start = winp->width / (labelCount + 1);
	if (maxw > start) {
		step = maxw + 8;
		if (step * labelCount > winp->width) {
			start = (step * labelCount - winp->width) / 2 + step / 2;
		} else {
			start = (winp->width - step * labelCount) / 2 + step / 2;
		}
	} else {
		step = start;
	}
	for (i = 0; i < labelCount; i++) {
		w = d2_AddWindowTextButton(start + step * i - maxw / 2, y, 0xbf, (int) buf[i], windowId);
		outIds[i] = w;
		*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[w].font)) = 0x53;
		d2_SetElementWidth(w, maxw);
	}
}
