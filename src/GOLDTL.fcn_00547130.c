extern unsigned short g_774970;

#pragma pack(2)
// SIZE 0xe
struct pos14_00547130 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// SIZE 0xf8
struct msg_00547130 {
	int f0;
	char b4;
	char pad[3];
	int f8;
	int fc;
	char pad2[0x18];
	struct pos14_00547130 pos;
	char b36;
	char pad3[0xc1];
};

// SIZE 0x21c
struct s_7f4ca0 {
	int f0;
	int f4;
	char pad[0x214];
};

extern char g_7f4ca0[];

// FUNCTION: GOLD 0x0053f360
// FUNCTION: GOLDTL 0x547130

#include <string.h>

int __cdecl fcn_005463a0(int, int, int);
void __cdecl fcn_004c5530(struct msg_00547130*);

void __cdecl fcn_00547130(void)
{
	struct msg_00547130 m;

	if (fcn_005463a0(1, 0, 0x7a) == 0) {
		memset(&m, 0, sizeof(m));
		m.b4 = 0x7a;
		m.fc = -1;
		m.b36 = 2;
		m.f8 = ((struct s_7f4ca0*)g_7f4ca0)[g_774970].f4;
		m.pos = (*(struct pos14_00547130*)&g_7f4c00);
		fcn_004c5530(&m);
	}
}
