extern unsigned char* lpGebaeudePROT;
extern signed char g_7f3b00[];
extern unsigned char* g_7746c8;

// SIZE 0x3dc
struct s_10432c0 {
	char name[0x3d5];
	char used;
	char pad[6];
};

extern char g_10432c0[];



#include <string.h>

int __cdecl fcn_00413160(void);
void __cdecl init_LoadGebaeudeScene(int);

int __cdecl fcn_005155e0(unsigned char* e)
{
	int k;
	int r;

	k = lpGebaeudePROT[*e * 0x24d];
	if (((volatile signed char*)g_7f3b00)[k] == -1) {
		if (e != g_7746c8 && *e != 0x1e) {
			r = fcn_00413160();
			if (r == -1) {
				return r;
			}
			((volatile signed char*)g_7f3b00)[k] = (signed char) r;
			((struct s_10432c0*)g_10432c0)[r].used = 1;
			strcpy(((struct s_10432c0*)g_10432c0)[r].name, (char*) lpGebaeudePROT + *e * 0x24d + 1);
			return ((volatile signed char*)g_7f3b00)[k];
		}
		init_LoadGebaeudeScene(*e);
	}
	return ((volatile signed char*)g_7f3b00)[k];
}
