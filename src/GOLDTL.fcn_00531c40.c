extern char* g_67a370;
extern volatile int g_6b7fac;

// SIZE 0x10c
struct s_7e6060 {
	int a;
	int t;
	char* o;
	char name[0x100];
};

extern struct s_7e6060 g_7e6060[64];

// FUNCTION: GOLDTL 0x531c40
// SIZE: 212

#include <string.h>

void __cdecl fcn_00531c00(void);

void __cdecl fcn_00531c40(char* o, int a, char* name)
{
	int i;
	int k;
	struct s_7e6060* p;

	if (o == 0) {
		return;
	}
	if (*(char**) (o + 0x88) != g_67a370) {
		return;
	}
	for (i = 0; i < 64; i++) {
		if (g_7e6060[i].o == o) {
			return;
		}
	}
	for (k = 0; k < 64; k++) {
		if (g_7e6060[k].o == 0) {
			break;
		}
	}
	if (k >= 64) {
		int now;

		now = g_6b7fac;
		k = -1;
		for (i = 0; i < 64; i++) {
			if (g_7e6060[i].t < now) {
				k = i;
			}
		}
		if (k == -1) {
			return;
		}
	}
	p = &g_7e6060[k];
	p->t = g_6b7fac;
	p->o = o;
	p->a = a;
	*(void**) (o + 0x228) = (void*) fcn_00531c00;
	if (name != 0) {
		strcpy(p->name, name);
	} else {
		p->name[0] = 0;
	}
}
