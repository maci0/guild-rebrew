// SIZE 0x50
struct s_7dcae0 {
	char b0;
	char pad[3];
	int f4;
	int f8;
	int fc;
	char name[0x40];
};

extern struct s_7dcae0 g_7dcae0[256];

// FUNCTION: GOLDTL 0x546ef0
// SIZE: 137

#include <string.h>

void __cdecl fcn_0041d9e0(char*);

struct s_7dcae0* __cdecl fcn_00546ef0(int a, char* name, int b, int c)
{
	int i;
	struct s_7dcae0* r;

	for (i = 0; i < 256; i++) {
		if (g_7dcae0[i].f8 == 0 && g_7dcae0[i].fc == 0 && g_7dcae0[i].name[0] == 0) {
			break;
		}
	}
	if (i >= 256) {
		fcn_0041d9e0("he_RegisterApEvent(): Too many ApEvents...");
		return 0;
	}
	r = &g_7dcae0[i];
	r->f4 = a;
	r->f8 = b;
	r->fc = c;
	r->b0 = 2;
	strncpy(r->name, name, 0x3f);
	return r;
}
