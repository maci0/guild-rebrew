#include <string.h>

typedef struct
{
	int i[0x3cc / 4];
} fcn_00472510_Win;
// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_00472510_Ent;
// SIZE 0x2f4

#include "client_types.h"
typedef Page_1038144 fcn_00472510_Page;
// SIZE 0x2bc

extern Win_1015f40 g_1015f40[0x60];
#include "Develop/Units/d2.v1/d2_gui.h"
extern Page_1038144 g_1038144[];
extern int g_772534;

/* ADDRESS: GOLDTL 0x00472510 */
void __cdecl fcn_00472510(int idx, int slot, int a3, int a4, int a5, int a6)
{
	fcn_00472510_Win* w;
	D2_CONTROL_TL* e;
	char* sub;

	w = &((fcn_00472510_Win*)g_1015f40)[g_1038144[g_772534].i[slot]];
	if (idx > w->i[0x2c / 4]) {
		return;
	}
	e = &((D2_CONTROL_TL*)g_1015ea0)[((int*) w->i[0x28 / 4])[idx]];
	if ((*(int*)&e->kind) == 0x41) {
		sub = (char*) (*(int*)&e->data);
		if (*(int*) (sub + 0x28) & 1) {
			if (strlen((char*) a3) > 0xfe) {
				return;
			}
			strcpy(sub + 0x2c, (char*) a3);
			return;
		}
		if (*(int*) (sub + 0x28) & 2) {
			*(int*) (sub + 0x1c) = a3;
			*(int*) (sub + 0x18) = a4;
			*(int*) (sub + 0x12c) = a5;
			return;
		}
	}
	if ((*(int*)&e->kind) == 0x45) {
		(*(int*)&e->payload.fields.value_090) = a3;
		(*(int*)&e->payload.fields.value_094) = a4;
		(*(int*)&e->payload.fields.value_08c) = a5;
		if (*((unsigned char*)&e->payload.fields.value_098) & 0x10) {
			(*(int*)&e->payload.fields.value_0a0) = a6;
		}
	} else if ((*(int*)&e->value_058) != 0 || (*(int*)&e->value_05c) != 0) {
		(*(int*)&e->value_03c) = (*(int*)&e->value_038) = (unsigned char) a3;
	}
}
