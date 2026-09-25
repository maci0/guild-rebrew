#include <string.h>
#pragma intrinsic(memset)

// FUNCTION: GOLDTL 0x591c30
// SIZE: 14

void __cdecl fcn_00591c30(char* p)
{
	*(int*) (p + 4) = -1;
	*(int*) (p + 8) = -1;
}

typedef struct {
	char c;
	char pad[3];
	int a;
	int b;
} Ent591c;
// SIZE 0xc

extern Ent591c g_779d00[11];

// FUNCTION: GOLD 0x5896e0
// SIZE: 63
// FUNCTION: GOLDTL 0x00591c40
// SIZE: 63

void __cdecl fcn_00591c40(void)
{
	int i;

	memset(g_779d00, 0, sizeof(g_779d00));
	for (i = 0; i < 11; i++) {
		g_779d00[i].c = (char) (i + 0x3b);
		if (i == 10) {
			g_779d00[10].c = 0x57;
		}
		fcn_00591c30((char*) &g_779d00[i]);
	}
}
