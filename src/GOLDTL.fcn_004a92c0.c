typedef struct Ent {
	unsigned short id;
	char pad2[2];
	int seed;
	char pad8[0x21c - 8];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

char* __cdecl fcn_00508e40(int id);
char* __cdecl fcn_005463a0(int a, int b, int c);
char* __cdecl fcn_005462a0(void);
int __cdecl fcn_004a5960(char* e, int a2, int kind, float lo, float hi, unsigned short* ids);
unsigned short __cdecl gm_RandomMod(int n);

// FUNCTION: GOLD 0x004a91a0
// FUNCTION: GOLDTL 0x4a92c0
int __cdecl fcn_004a92c0(int a1, char* e, int a3, int a4, char* out)
{
	unsigned short ids[12];
	char* p;
	int n;
	int kind;

	if ((*(int*)&g_7f4c00) % 4 == (*(int*) (e + 4) & 3) && !fcn_00508e40(*(int*) (e + 0x5c))) {
		for (p = fcn_005463a0(1, 0, 0x41); p; p = fcn_005462a0()) {
			if (*(int*) (p + 0xb0) == *(int*) (e + 4) || *(int*) (p + 0xac) == *(int*) (e + 4)) {
				return 0;
			}
		}
		kind = (e[9] ? -1 : 0) + 0xc0140a;
		n = fcn_004a5960(e, 0xc, kind, 30.0f, 100.0f, ids);
		if (n) {
			out[0] = 7;
			*(int*) (out + 4) = ((Ent*)g_7f4ca0)[ids[gm_RandomMod(n)]].seed;
			return 1;
		}
	}
	return 0;
}
