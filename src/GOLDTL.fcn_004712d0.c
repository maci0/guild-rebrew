typedef struct Obj {
	char pad0[0x190];
	int used;
	int pad194;
	int ready;
	char pad19c[0x1ac - 0x19c];
	int h1;
	char* h2;
	char name1[0x40];
	char name2[0x40];
	char pad234[0x2bc - 0x234];
} Obj;
// SIZE 0x2bc

#include "client_types.h"
extern Obj_1038140 g_1038140[];

void __cdecl fcn_00471340(int k);
void __cdecl fcn_004713b0(int k, char* a, char* b);
void __cdecl fcn_00471490(int k);

// FUNCTION: GOLDTL 0x4712d0
int __cdecl fcn_004712d0(int k, char* a, char* b)
{
	Obj* o;

	o = &((Obj*)g_1038140)[k];
	if (!o->used) {
		return 0;
	}
	if (!o->ready) {
		return 0;
	}
	if (a && b) {
		fcn_00471340(k);
		fcn_004713b0(k, a, b);
		fcn_00471490(k);
	}
	return 1;
}
