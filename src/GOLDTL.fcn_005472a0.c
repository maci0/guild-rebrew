extern char* g_773da8;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad[3];
	int f8;
	int fc;
	char pad2[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad3[0x21];
	char b58;
	char pad4[3];
	char b5c;
	char pad5[0x9b];
};

// FUNCTION: GOLD 0x0053f4d0
// FUNCTION: GOLDTL 0x5472a0

#include <string.h>

char* __cdecl fcn_005463a0(int, int, int, ...);
void __cdecl fcn_004c5530(struct msg*);

void __cdecl fcn_005472a0(void)
{
	struct msg m;

	if (fcn_005463a0(1, 0, 0x86) == 0) {
		memset(&m, 0, sizeof(m));
		m.b4 = (char) 0x86;
		m.f8 = *(int*) (g_773da8 + 4);
		m.fc = -1;
		m.b36 = 2;
		m.pos = g_7f4c00;
		fcn_004c5530(&m);
	}
	if (fcn_005463a0(1, 0, 0xa2) == 0) {
		memset(&m, 0, sizeof(m));
		m.b4 = (char) 0xa2;
		m.f8 = *(int*) (g_773da8 + 4);
		m.fc = -1;
		m.b36 = 2;
		m.pos = g_7f4c00;
		fcn_004c5530(&m);
	}
}
