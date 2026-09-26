#include <string.h>

typedef struct
{
	int i[0x3cc / 4];
} fcn_0046f390_Win;
// SIZE 0x3cc

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int g_77259c;

void __cdecl fcn_0046b2b0(int id);
void __cdecl fcn_0041ddd0(int p);
void __cdecl fcn_00475f80(int surf);
void __cdecl fcn_0047ce50(int tex);
void __cdecl fcn_00469960(int id);

// FUNCTION: GOLDTL 0x46f390
// SIZE: 247
int __cdecl fcn_0046f390(int win)
{
	fcn_0046f390_Win* w;

	if (win > 0x60) {
		return 0;
	}
	w = &((fcn_0046f390_Win*)g_1015f40)[win];
	if (w->i[0x290 / 4] == 0) {
		return 0;
	}
	while (w->i[0x2c / 4] != 0) {
		fcn_0046b2b0(*(int*) w->i[0x28 / 4]);
	}
	if (w->i[0x28 / 4] != 0) {
		fcn_0041ddd0(w->i[0x28 / 4]);
		w->i[0x28 / 4] = 0;
	}
	if (w->i[0x30 / 4] != 0) {
		fcn_00475f80(w->i[0x30 / 4]);
	}
	if (w->i[0x34 / 4] != 0) {
		fcn_00475f80(w->i[0x34 / 4]);
	}
	if (w->i[0x38 / 4] != 0) {
		fcn_00475f80(w->i[0x38 / 4]);
	}
	if (w->i[0x3a0 / 4] != 0) {
		fcn_0047ce50(w->i[0x3a0 / 4]);
	}
	if (w->i[0x398 / 4] != -1) {
		fcn_00469960(w->i[0x398 / 4]);
	}
	if (w->i[0x3c / 4] != 0) {
		fcn_0041ddd0(w->i[0x3c / 4]);
		w->i[0x3c / 4] = 0;
	}
	memset(w, 0, sizeof(fcn_0046f390_Win));
	w->i[0] = win;
	w->i[0x3c0 / 4] = -1;
	g_77259c--;
	return 1;
}
