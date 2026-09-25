// FUNCTION: GOLDTL 0x4508a0
// SIZE: 274
// m is a double compared as !(m > *p): that spelling loads the float first and
// copies m (fld/fld st(1)/fcompp) with the and eax,0x4100 mask, as in the reference.

#include <stdlib.h>

typedef struct Anim04508a0 {
	char pad0[0x24];
	float peak;
	char pad28[0x194 - 0x28];
	int start;
	float scale;
	unsigned int period;
	float value;
} Anim04508a0;
// SIZE 0x1a4

typedef struct Obj04508a0 {
	char pad0[0x58];
	float next;
	char pad5c[4];
	float base;
	char pad64[4];
	float prev;
	char pad6c[0x1e8 - 0x6c];
	Anim04508a0* anim;
} Obj04508a0;

extern int g_6b7fac;
extern float g_662a18;

void __cdecl fcn_004508a0(Obj04508a0* o)
{
	Anim04508a0* a;
	float* p;
	double m;
	float s;
	float f;
	unsigned int t;
	unsigned int period;
	int now;
	int i;

	now = g_6b7fac;
	a = o->anim;
	period = a->period;
	t = now - a->start;
	if (t >= period) {
		m = o->base;
		p = &a->peak;
		for (i = 7; i != 0; i--) {
			if (!(m > *p)) {
				m = *p;
			}
			p += 14;
		}
		s = o->base * a->scale / m;
		if (a->start == 0) {
			f = rand() * g_662a18 * s;
			o->prev = f + f - s + 1.0f;
		} else {
			o->prev = o->next;
		}
		f = rand() * g_662a18 * s;
		o->next = f + f - s + 1.0f;
		o->anim->start = now;
		t = 0;
	}
	f = (float)t / (float)period;
	o->anim->value = f * o->next + (1.0f - f) * o->prev;
}
