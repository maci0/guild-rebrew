#include <stdlib.h>

typedef struct Spin {
	char pad0[0x18];
	int max;
	int min;
	char pad20[0x28 - 0x20];
	unsigned char flags;
	char pad29[3];
	char text[0x100];
	int value;
} Spin;
// SIZE 0x130

#include "Develop/Units/d2.v1/d2_gui.h"

/* ADDRESS: GOLDTL 0x00473f50 */
void __cdecl fcn_00473f50(Spin* p, int v, int a3, int a4)
{
	int step;

	step = d2_GetValueStep((char*) p);
	p->value = v - step * ((a4 - a3) / 4);
	if (p->value > p->max) {
		p->value = p->max;
	} else if (p->value < p->min) {
		if ((p->flags & 0x40) && p->value == -1 && p->min == 0 && p->max == 0) {
			p->value = p->value;
		} else {
			p->value = p->min;
		}
	}
	_itoa(p->value, p->text, 10);
}
