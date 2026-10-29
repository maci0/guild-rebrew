#include "client_types.h"
extern Loot_7774a0 g_7774a0[32];
extern Loot_7774a0 g_7774a0[32];



// SIZE 0x40
typedef struct {
	int a;
	int b;
	int c;
	int d;
	struct {
		int x;
		int y;
	} s[6];
} Rec;

void __cdecl fcn_005c69d0(void)
{
	int i;
	int j;
	Rec* r;

	for (i = 0; i < 32; i++) {
		r = (Rec*) g_7774a0 + i;
		r->a = 0;
		r->b = -1;
		r->c = -1;
		r->d = -1;
		for (j = 0; j < 6; j++) {
			r->s[j].x = -1;
			r->s[j].y = 0;
		}
	}
}
