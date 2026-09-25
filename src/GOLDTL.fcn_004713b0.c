#include <string.h>

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

extern Obj g_1038140[];
extern int g_14ce86c;

char* __cdecl fcn_0045bde0(char* name);
void __cdecl fcn_0045d090(char* p, int a);
void __cdecl fcn_004767f0(int a, int b, int c, int d, int e, int f, int g, int h);

// FUNCTION: GOLDTL 0x4713b0
// SIZE: 216
void __cdecl fcn_004713b0(int k, char* a, char* b)
{
	Obj* o;
	char* p;
	char* q;

	o = &g_1038140[k];
	p = 0;
	if (a) {
		strcpy(o->name1, a);
		p = fcn_0045bde0(a);
		if (p) {
			fcn_0045d090(p, g_14ce86c);
			fcn_004767f0(0, 0, *(int*) (p + 0x64), *(int*) (p + 0x64), *(int*) (p + 0x50), 0, 0, o->h1);
		}
	}
	if (b) {
		strcpy(o->name2, b);
		q = fcn_0045bde0(b);
		if (q) {
			fcn_0045d090(q, g_14ce86c);
			fcn_004767f0(0, 0, *(int*) (q + 0x64), *(int*) (o->h2 + 8), *(int*) (q + 0x50), 0, *(int*) (p + 0x64), (int) o->h2);
		}
	}
}
