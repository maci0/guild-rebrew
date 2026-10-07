int __cdecl fcn_00530ab0(int key, char* name, int a, int v, int w);

// SIZE 0x20
struct s_7e2ac0 {
	int key;
	char name[16];
	int a;
	int v;
	int w;
};

#include "client_types.h"
extern s_7e2ac0 g_7e2ac0[48];

// FUNCTION: GOLD 0x0052b380
// FUNCTION: GOLDTL 0x530ab0

#include <string.h>

int __cdecl fcn_00530ab0(int key, char* name, int a, int v, int w)
{
	int i;

	for (i = 0; i < 48; i++) {
		if (((struct s_7e2ac0*)g_7e2ac0)[i].key == 0) {
			if (name != 0) {
				strcpy(((struct s_7e2ac0*)g_7e2ac0)[i].name, name);
			}
			((struct s_7e2ac0*)g_7e2ac0)[i].key = key;
			((struct s_7e2ac0*)g_7e2ac0)[i].a = a;
			((struct s_7e2ac0*)g_7e2ac0)[i].v = v;
			((struct s_7e2ac0*)g_7e2ac0)[i].w = w;
			return 1;
		}
	}
	return 0;
}
