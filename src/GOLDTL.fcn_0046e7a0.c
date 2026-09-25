#include <stdio.h>

typedef struct Win {
	char pad0[0x3a0];
	void* tex;
	float alpha;
	char pad3a8[0x3cc - 0x3a8];
} Win;
// SIZE 0x3cc

extern Win g_1015f40[];
extern char s_67d54c[];

void __cdecl fcn_0047ce50(void* tex);
void* __cdecl fcn_0047ce00(const char* name, int a2);
void __cdecl fcn_0041d9e0(const char* msg);

// FUNCTION: GOLDTL 0x46e7a0
// SIZE: 140
void __cdecl fcn_0046e7a0(const char* name, int win)
{
	char msg[0x400];
	Win* w;

	w = &g_1015f40[win];
	if (w->tex) {
		fcn_0047ce50(w->tex);
		w->tex = 0;
	}
	if (name && *name) {
		w->tex = fcn_0047ce00(name, 1);
		if (!w->tex) {
			sprintf(msg, s_67d54c);
			fcn_0041d9e0(msg);
		}
		w->alpha = 0.5f;
	}
}
