int __cdecl fcn_00530ab0(int key, char* name, int a, int v, int w);

// SIZE 0x20
struct s_7e2ac0 {
	int key;
	char name[16];
	int a;
	int v;
	int w;
};

extern struct s_7e2ac0 g_7e2ac0[48];

// FUNCTION: GOLDTL 0x530ab0
// SIZE: 109

#include <string.h>

int __cdecl fcn_00530ab0(int key, char* name, int a, int v, int w)
{
	int i;

	for (i = 0; i < 48; i++) {
		if (g_7e2ac0[i].key == 0) {
			if (name != 0) {
				strcpy(g_7e2ac0[i].name, name);
			}
			g_7e2ac0[i].key = key;
			g_7e2ac0[i].a = a;
			g_7e2ac0[i].v = v;
			g_7e2ac0[i].w = w;
			return 1;
		}
	}
	return 0;
}
