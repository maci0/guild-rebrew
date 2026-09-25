#include <stdlib.h>
#include <string.h>

typedef struct
{
	int i[0x2ec / 4];
} fcn_00475ca0_Ent;
// SIZE 0x2ec

extern fcn_00475ca0_Ent* g_00f8f080; /* 0x00f8f080 */

int __cdecl fcn_00475be0(char* sub);

// FUNCTION: GOLD 0x00475ca0
// SIZE: 390
void __cdecl fcn_00475ca0(int id, int a2, int a3, int a4, int a5)
{
	fcn_00475ca0_Ent* e;
	char* sub;
	int fl;
	int step;
	int v;
	int n;

	if (id == -1 || id > 0x300) {
		return;
	}
	e = &g_00f8f080[id];
	if (e->i[0x18 / 4] == 0x41) {
		sub = (char*) e->i[0xc / 4];
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
	if (e->i[0x18 / 4] == 0x45) {
		e->i[0x80 / 4] = a2;
		e->i[0x84 / 4] = a3;
		e->i[0x7c / 4] = a4;
		if (*((unsigned char*) e + 0x88) & 0x10) {
			e->i[0x90 / 4] = a5;
		}
	} else if (e->i[0x48 / 4] != 0 || e->i[0x4c / 4] != 0) {
		e->i[0x2c / 4] = e->i[0x28 / 4] = (unsigned char) a2;
	}
}
