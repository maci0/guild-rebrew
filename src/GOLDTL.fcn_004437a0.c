extern int g_6b8010;

// SIZE 0x3dc
typedef struct {
	int used;
	char p4[0x344];
	int res;
	char p34c[0x90];
} Slot;

#include "client_types.h"
extern Slot_1043340 g_1043340[64];
extern char* g_1043254;
extern char g_1042340[];
extern char* g_1040c74;
extern char g_1040640[];
extern int g_6b8300;
extern int g_6b89c0;
extern int g_6b8058;
extern int g_6b8484;

void __cdecl fcn_00442e30(void);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_004398d0(void*);
void __cdecl fcn_00452420(void*);
void __cdecl fcn_0043bcf0(int);
void __cdecl fcn_00459b40(int);
void __cdecl fcn_0041ddd0(int);

// FUNCTION: GOLDTL 0x004437a0
// SIZE: 272

char __cdecl fcn_004437a0(int idx)
{
	int prev;
	char ok;

	ok = 0;
	if (idx >= 0 && idx < 0x40) {
		if (idx != g_6b8010) {
			if (((Slot*)g_1043340)[idx].used != 0) {
				prev = g_6b8010;
				fcn_004432d0(idx, 1);
				while (((void*)g_1043254) != &(*(char*)g_1042340)) {
					fcn_004398d0(((void*)g_1043254));
				}
				while (((void*)g_1040c74) != &(*(char*)g_1040640)) {
					fcn_00452420(((void*)g_1040c74));
				}
				if (g_6b8300 != 0) {
					fcn_0043bcf0(g_6b8300);
					g_6b8300 = 0;
				}
				if (g_6b89c0 != 0) {
					fcn_00459b40(g_6b89c0);
					g_6b89c0 = 0;
				}
				if (((Slot*)g_1043340)[idx].res != 0) {
					fcn_0041ddd0(((Slot*)g_1043340)[idx].res);
					((Slot*)g_1043340)[idx].res = 0;
				}
				g_6b8058 = 0;
				g_6b8484 = 0;
				if (prev != g_6b8010) {
					fcn_004432d0(prev, 1);
				}
			}
		} else {
			fcn_00442e30();
		}
		ok = 1;
	}
	return ok;
}
