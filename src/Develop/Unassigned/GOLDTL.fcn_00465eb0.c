typedef struct
{
	int i[0x3cc / 4];
} fcn_00465eb0_Win;
// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_00465eb0_Ent;
// SIZE 0x2f4

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern char s_67d420[];

#include "Develop/Units/Error/error_message.h"
void __cdecl fcn_0046f650(int slot, fcn_00465eb0_Win* parent);

/* ADDRESS: GOLDTL 0x00465eb0 */
int __cdecl fcn_00465eb0(int id, int win)
{
	fcn_00465eb0_Win* w;
	int bottom;

	if (win < 0 || win > 0x60) {
		return 0;
	}
	w = &((fcn_00465eb0_Win*)g_1015f40)[win];
	if (w->i[0x290 / 4] == 0) {
		return 0;
	}
	if (w->i[0x2c / 4] >= 0x180) {
		ReportClientMessage(s_67d420);
		return 0;
	}
	fcn_0046f650(id, w);
	((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x40 / 4] = (int) w;
	((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x50 / 4] = ((fcn_00465eb0_Ent*)g_1015ea0)[w->i[0x27c / 4]].i[0x50 / 4];
	((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x30 / 4] = w->i[0x8 / 4];
	((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x34 / 4] = w->i[0x10 / 4] + w->i[0x8 / 4];
	((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x28 / 4] = w->i[0x4 / 4];
	((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x2c / 4] = w->i[0xc / 4] + w->i[0x4 / 4];
	((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x48 / 4] = ((fcn_00465eb0_Ent*)g_1015ea0)[w->i[0x27c / 4]].i[0x48 / 4];
	bottom = ((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x1c / 4] + ((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x14 / 4] - w->i[0x8 / 4];
	if (bottom > w->i[0x254 / 4]) {
		w->i[0x254 / 4] = bottom + 4;
	}
	((int*) w->i[0x28 / 4])[w->i[0x2c / 4]] = id;
	w->i[0x2c / 4]++;
	return 1;
}
