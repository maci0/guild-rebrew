extern int g_77250c;
extern int g_67a370;

// SIZE 0xc8

#include "client_types.h"
extern s_7e46c0 g_7e46c0[32];

// FUNCTION: GOLDTL 0x532900
// SIZE: 157

void __cdecl fcn_00472880(int);
char __cdecl fcn_00443e10(char*, int*);
void __cdecl fcn_0046bd20(int, int, int, int, int, char*, int);
void __cdecl fcn_00437ac0(int, int, int, void*);
void __cdecl fcn_00532750(void);

void __cdecl fcn_00532900(void)
{
	int r[4];
	s_7e46c0* p;
	char* e;

	fcn_00472880(0x54);
	for (p = g_7e46c0; (int) p < (int) &g_7e46c0[32]; p++) {
		e = p->e;
		if (e != 0 && (*(int*) (e + 0x1cc) != 0 || *(int*) (e + 0x218) == 0) &&
		    fcn_00443e10(e, r) != 0) {
			fcn_0046bd20(r[0] + (r[2] - r[0]) / 2 - 0x50, r[1], 0xa0, 0x60, g_77250c,
			             p->name, 0x28);
		}
	}
	fcn_00437ac0(g_67a370, 0, 0x20, (void*) fcn_00532750);
}
