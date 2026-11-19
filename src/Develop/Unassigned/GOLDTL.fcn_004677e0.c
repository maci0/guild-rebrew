#include "Develop/Units/d2.v1/d2_win.h"




// SIZE 0x3cc

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char s_67d420[];

#include "Develop/Units/Error/error_message.h"
int __cdecl fcn_004675f0(int x, int y, int a3, int a4, int a5, int a6, int a7);
int __cdecl fcn_00465eb0(int id, int win);

/* ADDRESS: GOLDTL 0x004677e0 */
int __cdecl fcn_004677e0(int x, int y, int a3, int a4, int a5, int a6, int a7, int win)
{
	D2_WIN* window;
	int id;

	if (win < 0 || win > 0x60) {
		return -1;
	}
	window = &((D2_WIN*)g_1015f40)[win];
	if (window->active == 0) {
		return -1;
	}
	if (window->count >= 0x180) {
		ReportClientMessage(s_67d420);
		return -1;
	}
	id = fcn_004675f0(window->left + x, window->top - (*(int*) &window->pad3c[0x21c]) + y, a3, a4, a5, a6, a7);
	fcn_00465eb0(id, win);
	return id;
}
