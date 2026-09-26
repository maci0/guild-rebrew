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

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern Page_1038144 g_1038144[];
extern int g_772534;

// FUNCTION: GOLDTL 0x472510
// SIZE: 289
void __cdecl fcn_00472510(int idx, int slot, int a3, int a4, int a5, int a6)
{
	fcn_00472510_Win* w;
	fcn_00472510_Ent* e;
	char* sub;

	w = &((fcn_00472510_Win*)g_1015f40)[g_1038144[g_772534].i[slot]];
	if (idx > w->i[0x2c / 4]) {
		return;
	}
	e = &((fcn_00472510_Ent*)g_1015ea0)[((int*) w->i[0x28 / 4])[idx]];
	if (e->i[0x20 / 4] == 0x41) {
		sub = (char*) e->i[0xc / 4];
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
	if (e->i[0x20 / 4] == 0x45) {
		e->i[0x90 / 4] = a3;
		e->i[0x94 / 4] = a4;
		e->i[0x8c / 4] = a5;
		if (*((unsigned char*) e + 0x98) & 0x10) {
			e->i[0xa0 / 4] = a6;
		}
	} else if (e->i[0x58 / 4] != 0 || e->i[0x5c / 4] != 0) {
		e->i[0x3c / 4] = e->i[0x38 / 4] = (unsigned char) a3;
	}
}
