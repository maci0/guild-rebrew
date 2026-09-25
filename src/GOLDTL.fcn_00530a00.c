void __cdecl fcn_00402a00(char*, int);

// SIZE 0x21c
struct s_7f4ca0 {
	char pad[0x184];
	char* d;
	char pad2[0x94];
};

extern struct s_7f4ca0 g_7f4ca0[768];
extern struct s_7f4ca0* g_7e4260[32];

// FUNCTION: GOLD 0x0052b2d0
// SIZE: 166
// FUNCTION: GOLDTL 0x530a00
// SIZE: 166

#include <string.h>


void __cdecl fcn_00530a00(char* b)
{
	struct s_7f4ca0** out;
	int i;

	memset(g_7e4260, 0, sizeof(g_7e4260));
	if (b != 0) {
		out = g_7e4260;
		for (i = 0; i < 768 && (int) out < (int) &g_7e4260[31]; i++) {
			if (g_7f4ca0[i].d != 0 && *(int*) (g_7f4ca0[i].d + 0x2c) == *(int*) (b + 1)) {
				*out++ = &g_7f4ca0[i];
				if ((int) out > (int) &g_7e4260[8]) {
					fcn_00402a00(g_7f4ca0[i].d, 0);
				}
			}
		}
	} else {
		out = g_7e4260;
		for (i = 0; i < 768 && (int) out < (int) &g_7e4260[31]; i++) {
			if (g_7f4ca0[i].d != 0 && *(int*) (g_7f4ca0[i].d + 0x2c) == -1) {
				*out++ = &g_7f4ca0[i];
			}
		}
	}
}
