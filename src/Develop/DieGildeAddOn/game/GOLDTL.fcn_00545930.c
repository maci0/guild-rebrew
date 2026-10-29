extern int g_77e8a0;



typedef struct {
	int a;
	int b;
	int c;
} Rec545930;
// SIZE 0xc

#include "client_types.h"
extern s_77e8c0 g_77e8c0[16];

void __cdecl fcn_00545780(int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_00545930(void)
{
	int i;

	for (i = 0; i < 0x10; i++) {
		if (((Rec545930*)g_77e8c0)[i].b != -1) {
			fcn_00545780(((Rec545930*)g_77e8c0)[i].a);
		}
	}
	fcn_00471e30(g_77e8a0);
}
