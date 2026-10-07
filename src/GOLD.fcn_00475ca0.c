#include <stdlib.h>
#include <string.h>

#include "gold_gui.h"

extern GuiEnt* g_00f8f080; /* 0x00f8f080 */

int __cdecl fcn_00475be0(char* sub);

// FUNCTION: GOLD 0x00475ca0
void __cdecl fcn_00475ca0(int id, int a2, int a3, int a4, int a5)
{
	GuiEnt* e;
	char* sub;
	int fl;
	int step;
	int v;
	int n;

	if (id == -1 || id > 0x300) {
		return;
	}
	e = &g_00f8f080[id];
	if (e->kind == 0x41) {
		sub = e->data;
		if (*(int*) (sub + 0x28) & 1) {
			if (strlen((char*) a2) > 0xfe) {
				return;
			}
			strcpy(sub + 0x2c, (char*) a2);
			return;
		}
		if (*(int*) (sub + 0x28) & 2) {
			*(int*) (sub + 0x1c) = a2;
			*(int*) (sub + 0x18) = a3;
			*(int*) (sub + 0x12c) = a4;
			_itoa(a4, sub + 0x2c, 10);
			fl = *(int*) (sub + 0x28);
			if (fl & 0x80) {
				step = fcn_00475be0(sub);
				*(int*) (sub + 0x18) -= (*(int*) (sub + 0x18) - *(int*) (sub + 0x1c)) % step;
				*(int*) (sub + 0x1c) += (*(int*) (sub + 0x18) - *(int*) (sub + 0x1c)) % step;
				v = *(int*) (sub + 0x12c) / step * step;
				n = (*(int*) (sub + 0x18) - *(int*) (sub + 0x1c)) / step;
				*(int*) (sub + 0x12c) = v;
				if (n > 0x19) {
					*(int*) (sub + 0x18) = step * 25;
				}
				if (v == -1 && (fl & 0x40)) {
					return;
				}
				*(int*) (sub + 0x12c) = *(int*) (sub + 0x1c) > v ? *(int*) (sub + 0x1c) : v;
			}
			return;
		}
	}
	if (e->kind == 0x45) {
		e->u.num.f80 = a2;
		e->u.num.f84 = a3;
		e->buf = (char*) a4;
		if (e->u.num.f88 & 0x10) {
			e->u.num.f90 = a5;
		}
	} else if (e->dirty != 0 || e->f4c != 0) {
		e->f2c = e->f28 = (unsigned char) a2;
	}
}
