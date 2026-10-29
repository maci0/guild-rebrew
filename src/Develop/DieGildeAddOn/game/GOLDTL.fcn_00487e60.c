


typedef struct Ent {
	unsigned short id;
	char pad2[0x17c - 2];
	char* host;
	char pad180[0x21c - 0x180];
} Ent;
// SIZE 0x21c

typedef struct Order {
	int id;
	char pad4[0x54 - 4];
	int flags;
} Order;
// SIZE 0x58

extern char g_7f4ca0[];
#include "client_types.h"
extern entry_100d0c0 g_100d0c0[];
extern int g_100b0ac;

char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl fcn_00529160(char* o, int a, int id, int b);

void __cdecl fcn_00487e60(char* e, int k)
{
	char* q;
	int found;
	int i;

	for (q = fcn_005463a0(2, 0, k, 3, *(int*) (*(char**) (e + 0x16c) + 1)); q != 0; q = he_fn_Handlung()) {
		found = 0;
		if (k == 4) {
			for (i = 0; i < g_100b0ac; i++) {
				if (((Order*)g_100d0c0)[i].id == *(unsigned short*) (q + 0xac) && !(((Order*)g_100d0c0)[i].flags & 8)) {
					found = 1;
				}
			}
		} else if (k == 8) {
			for (i = 0; i < g_100b0ac; i++) {
				if (((Order*)g_100d0c0)[i].id == *(unsigned short*) (q + 0xac) && !(((Order*)g_100d0c0)[i].flags & 0x10)) {
					found = 1;
				}
			}
		} else if (k == 3) {
			for (i = 0; i < g_100b0ac; i++) {
				if (((Order*)g_100d0c0)[i].id == *(unsigned short*) (q + 0xac) && !(((Order*)g_100d0c0)[i].flags & 8)) {
					found = 1;
				}
			}
		}
		if (found) {
			for (i = 0; i < 768; i++) {
				if (((Ent*)g_7f4ca0)[i].id != 0xffff && ((Ent*)g_7f4ca0)[i].host == q) {
					fcn_00529160(*(char**) (e + 0x16c), 0, ((Ent*)g_7f4ca0)[i].id, 0);
				}
			}
		}
	}
}
