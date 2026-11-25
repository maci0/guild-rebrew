#include <stdarg.h>
#include <string.h>
#include "client_types.h"
#include "Develop/Units/d2.v1/d2_win.h"

extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;

int __cdecl fcn_0046b520(char* s, int font);
int __cdecl fcn_00468df0(int a1, int a2, int a3, int a4, int i);
void __cdecl fcn_00469110(int a1, int a2);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00533a60 */
void __cdecl fcn_00533a60(int windowId, int a1, int* a2, int labelCount, ...)
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
		w = fcn_0046b520(src, *(int*) ((char*) winp + 0x28c)) + 0x20;
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
		w = fcn_00468df0(start + step * i - maxw / 2, a1, 0xbf, (int) buf[i], windowId);
		a2[i] = w;
		*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[w].font)) = 0x53;
		fcn_00469110(w, maxw);
	}
}
