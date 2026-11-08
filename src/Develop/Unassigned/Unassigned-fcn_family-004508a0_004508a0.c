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
extern char* g_6b86e8;
extern int g_6b8708;
extern int g_6b8704;

void __cdecl fcn_004508a0(char* p);

/* ADDRESS: GOLDTL 0x004508a0 */
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

	now = *(int*) 0x6b7fac;
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
		s = (float)(o->base * a->scale / m);
		if (a->start == 0) {
			f = rand() * *(float*) 0x662a18 * s;
			o->prev = f + f - s + 1.0f;
		} else {
			o->prev = o->next;
		}
		f = rand() * *(float*) 0x662a18 * s;
		o->next = f + f - s + 1.0f;
		o->anim->start = now;
		t = 0;
	}
	f = (float)t / (float)period;
	o->anim->value = f * o->next + (1.0f - f) * o->prev;
}

/* ADDRESS: GOLDTL 0x004509c0 */
void __cdecl fcn_004509c0(void)
{
	char* p;

	for (p = g_6b86e8; p != 0 && g_6b8708 < g_6b8704; p = *(char**) (p + 0x1f0)) {
		if (*(int*) (p + 0x218) == 6) {
			fcn_004508a0(p);
		}
	}
}
