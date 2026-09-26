extern unsigned char* g_7e3f30;
extern signed char g_76fa60[];
extern unsigned char* g_6f230c;

// SIZE 0x3e0
struct s_fd7ba0 {
	char name[0x3d5];
	char used;
	char pad[0xa];
};

extern struct s_fd7ba0 g_fd7ba0[];

// FUNCTION: GOLD 0x00511e90
// SIZE: 177
/* Twin of GOLDTL 0x5155e0; the GOLD slot records are 0x3e0 bytes, not 0x3dc. */

#include <string.h>

int __cdecl fcn_00413160(void);
void __cdecl fcn_0050dc30(int);

int __cdecl fcn_00511e90(unsigned char* e)
{
	int k;
	int r;

	k = g_7e3f30[*e * 0x24d];
	if (((volatile signed char*) g_76fa60)[k] == -1) {
		if (e != g_6f230c && *e != 0x1e) {
			r = fcn_00413160();
			if (r == -1) {
				return r;
			}
			((volatile signed char*) g_76fa60)[k] = (signed char) r;
			g_fd7ba0[r].used = 1;
			strcpy(g_fd7ba0[r].name, (char*) g_7e3f30 + *e * 0x24d + 1);
			return ((volatile signed char*) g_76fa60)[k];
		}
		fcn_0050dc30(*e);
	}
	return ((volatile signed char*) g_76fa60)[k];
}
