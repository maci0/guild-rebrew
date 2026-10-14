typedef struct
{
	int i[0x3cc / 4];
} fcn_004677e0_Win;
// SIZE 0x3cc

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char s_67d420[];

void __cdecl fcn_0041d9e0(const char* msg);
int __cdecl fcn_004675f0(int x, int y, int a3, int a4, int a5, int a6, int a7);
int __cdecl fcn_00465eb0(int id, int win);

/* ADDRESS: GOLDTL 0x004677e0 */
int __cdecl fcn_004677e0(int x, int y, int a3, int a4, int a5, int a6, int a7, int win)
{
	fcn_004677e0_Win* w;
	int id;

	if (win < 0 || win > 0x60) {
		return -1;
	}
	w = &((fcn_004677e0_Win*)g_1015f40)[win];
	if (w->i[0x290 / 4] == 0) {
		return -1;
	}
	if (w->i[0x2c / 4] >= 0x180) {
		fcn_0041d9e0(s_67d420);
		return -1;
	}
	id = fcn_004675f0(w->i[0x4 / 4] + x, w->i[0x8 / 4] - w->i[0x258 / 4] + y, a3, a4, a5, a6, a7);
	fcn_00465eb0(id, win);
	return id;
}
