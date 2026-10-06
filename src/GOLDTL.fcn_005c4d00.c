// FUNCTION: GOLDTL 0x005c4d00

#include <string.h>
#pragma intrinsic(memset)

typedef struct {
	int w;
	char* p;
} Btn5c4d;
// SIZE 0x8

typedef struct {
	char pad[0x194];
	int name;
	char pad2[0x84];
} Ent5c4d;
// SIZE 0x21c

extern Btn5c4d g_776ca0[256];
extern char g_7f4ca0[];

void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_0050e380(int, char*);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, int);

void __cdecl fcn_005c4d00(int win, int sub, int idx)
{
	char buf[0x220];
	int k;
	char* r;

	fcn_004727a0(win, sub);
	memset(g_776ca0, 0, sizeof(g_776ca0));
	fcn_0050e380(idx, buf);
	fcn_00519190(0x1efa, ((Ent5c4d*)g_7f4ca0)[idx].name);
	k = 0;
	while (*(int*) (buf + 0x35 + k * 0x1e) != 0 && k < 256) {
		r = buf + 0x35 + k * 0x1e;
		g_776ca0[k].w = fcn_00472250(win, sub, fcn_00519190(0x1efb, 2, *(int*) (r + 8), *(int*) (r + 0xc)));
		g_776ca0[k].p = *(char**) (r + 4);
		fcn_00472380(g_776ca0[k].w, *(int*) (g_776ca0[k].p + 8));
		k++;
	}
}
