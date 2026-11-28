#include <string.h>

typedef struct
{
	int i[0x3cc / 4];
} D2_FORM_WINDOW;
// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} D2_FORM_ENTRY_VIEW;
// SIZE 0x2f4

#include "Develop/client_types.h"
typedef Page_1038144 D2_FORM_PAGE_VIEW;
// SIZE 0x2bc

extern Win_1015f40 g_1015f40[0x60];
#include "Develop/Units/d2.v1/d2_gui.h"
extern Page_1038144 g_1038144[];
extern int g_772534;

/* ADDRESS: GOLDTL 0x00472510 */
void __cdecl d2_SetFormElementValue(int idx, int slot, int value1, int value2, int value3, int value4)
{
	D2_FORM_WINDOW* w;
	D2_CONTROL_TL* e;
	char* sub;

	w = &((D2_FORM_WINDOW*)g_1015f40)[g_1038144[g_772534].i[slot]];
	if (idx > w->i[0x2c / 4]) {
		return;
	}
	e = &((D2_CONTROL_TL*)g_1015ea0)[((int*) w->i[0x28 / 4])[idx]];
	if ((*(int*)&e->kind) == 0x41) {
		sub = (char*) (*(int*)&e->data);
		if (*(int*) (sub + 0x28) & 1) {
			if (strlen((char*) value1) > 0xfe) {
				return;
			}
			strcpy(sub + 0x2c, (char*) value1);
			return;
		}
		if (*(int*) (sub + 0x28) & 2) {
			*(int*) (sub + 0x1c) = value1;
			*(int*) (sub + 0x18) = value2;
			*(int*) (sub + 0x12c) = value3;
			return;
		}
	}
	if ((*(int*)&e->kind) == 0x45) {
		(*(int*)&e->payload.fields.value_090) = value1;
		(*(int*)&e->payload.fields.value_094) = value2;
		(*(int*)&e->payload.fields.value_08c) = value3;
		if (*((unsigned char*)&e->payload.fields.value_098) & 0x10) {
			(*(int*)&e->payload.fields.value_0a0) = value4;
		}
	} else if ((*(int*)&e->value_058) != 0 || (*(int*)&e->value_05c) != 0) {
		(*(int*)&e->value_03c) = (*(int*)&e->value_038) = (unsigned char) value1;
	}
}
