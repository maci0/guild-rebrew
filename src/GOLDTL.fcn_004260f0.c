#include <string.h>

// SIZE 0x30
struct sym_4260f0 {
	int kind;
	char name[0x2c];
};

extern char* g_6b7eb8;
extern struct sym_4260f0* g_14cb8e0;
extern int g_14cb8e4;

// FUNCTION: GOLD 0x4278d0
// SIZE: 336
// FUNCTION: GOLDTL 0x4260f0
// SIZE: 328
void* __cdecl fcn_004260f0(char* ctx, char* name)
{
	char* scope;
	char** locals;
	int i;

	scope = g_6b7eb8 != 0 ? g_6b7eb8 : ctx;
	i = 0;
	locals = *(char***) (ctx + 0xc28);
	if (locals != 0) {
		while (1) {
			if (i >= 8) {
				break;
			}
			if (locals[i + 4] != 0 && strcmp(locals[i + 4] + 4, name) == 0) {
				return locals[i + 4];
			}
			i++;
		}
	}
	for (i = 0; i < *(int*) (scope + 0x114); i++) {
		if (strcmp((*(struct sym_4260f0**) (scope + 0x108))[i].name, name) == 0) {
			return &(*(struct sym_4260f0**) (scope + 0x108))[i];
		}
	}
	for (i = 0; i < g_14cb8e4; i++) {
		if (strcmp(g_14cb8e0[i].name, name) == 0) {
			return &g_14cb8e0[i];
		}
	}
	return 0;
}
