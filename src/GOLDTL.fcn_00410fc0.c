// FUNCTION: GOLD 0x004100b0
// FUNCTION: GOLDTL 0x00410fc0

extern char* g_6b7e98;
extern int g_6791c8;
int __cdecl fcn_00422460(int a, int b);
int __cdecl fcn_00423670(int o, int a, int b);
void __cdecl fcn_004238f0(int o, int v);
#include "client_sound.h"

int __cdecl fcn_00410fc0(int* a, int* b, int* c, int* d)
{
	int o;

	if (*(int*) (g_6b7e98 + 0x104) != g_6791c8) {
		return 0;
	}
	o = fcn_00422460(0, *c);
	if (o != 0) {
		if (*d == 1) {
			fcn_004193f0((char*)o, (void*)*a, 0x3c, (float) *b);
		} else {
			fcn_004238f0(o, *d);
			fcn_00423670(o, 0, 0);
		}
	}
	return o;
}
