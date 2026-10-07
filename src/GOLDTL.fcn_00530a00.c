void __cdecl fcn_00402a00(char*, int);

// SIZE 0x21c
struct s_7f4ca0 {
	char pad[0x184];
	char* d;
	char pad2[0x94];
};

extern char g_7f4ca0[];
extern char* g_7e4260[32];

// FUNCTION: GOLD 0x0052b2d0
// FUNCTION: GOLDTL 0x530a00

#include <string.h>


void __cdecl fcn_00530a00(char* b)
{
	struct s_7f4ca0** out;
	int i;

	memset(((struct s_7f4ca0**)g_7e4260), 0, sizeof(struct s_7f4ca0*[32]));
	if (b != 0) {
		out = ((struct s_7f4ca0**)g_7e4260);
		for (i = 0; i < 768 && (int) out < (int) &((struct s_7f4ca0**)g_7e4260)[31]; i++) {
			if (((struct s_7f4ca0*)g_7f4ca0)[i].d != 0 && *(int*) (((struct s_7f4ca0*)g_7f4ca0)[i].d + 0x2c) == *(int*) (b + 1)) {
				*out++ = &((struct s_7f4ca0*)g_7f4ca0)[i];
				if ((int) out > (int) &((struct s_7f4ca0**)g_7e4260)[8]) {
					fcn_00402a00(((struct s_7f4ca0*)g_7f4ca0)[i].d, 0);
				}
			}
		}
	} else {
		out = ((struct s_7f4ca0**)g_7e4260);
		for (i = 0; i < 768 && (int) out < (int) &((struct s_7f4ca0**)g_7e4260)[31]; i++) {
			if (((struct s_7f4ca0*)g_7f4ca0)[i].d != 0 && *(int*) (((struct s_7f4ca0*)g_7f4ca0)[i].d + 0x2c) == -1) {
				*out++ = &((struct s_7f4ca0*)g_7f4ca0)[i];
			}
		}
	}
}
