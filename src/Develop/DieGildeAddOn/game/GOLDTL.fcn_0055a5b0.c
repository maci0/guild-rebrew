

#include <string.h>

#pragma pack(push, 2)
// SIZE 0xe
typedef struct {
	int a;
	int b;
	int c;
	short d;
} Pos55a5;
#pragma pack(pop)

// SIZE 0xf8
typedef struct {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x18];
	Pos55a5 at;
	unsigned char code;
	char pad37[0x21];
	int owner2;
	int other;
	Pos55a5 due;
	char pad6e[0x8a];
} Msg55a5;

extern char g_7f4ca0[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned char g_773d75;
extern char g_6b5c60[];

void __cdecl fcn_00500bb0(Pos55a5*, int, int, int);
void __cdecl fcn_004c5530(Msg55a5*);
void __cdecl fcn_00546190(char*);
#include "Develop/DieGildeAddOn/game/spiel.h"
float __cdecl fcn_004fef80(char*);
float __cdecl fcn_004ff210(unsigned short, int);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);

/* ADDRESS: GOLD 0x5524c0 */
void __cdecl fcn_0055a5b0(char* u)
{
	float f;
	int a;
	Msg55a5 m;
	char buf[0x800];
	char* h;
	int d;

	if (*(int*) (u + 0x70) >= 0 && *(int*) (u + 0x70) <= 1) {
		if (*(int*) (u + 0x70) == 0) {
			memset(&m, 0, sizeof(m));
			m.kind = 0x7e;
			m.owner = *(int*) (u + 0xac);
			m.target = -1;
			m.at = (*(Pos55a5*)&g_7f4c00);
			m.code = 9;
			m.owner2 = *(int*) (u + 0xac);
			m.other = *(int*) (u + 4);
			m.due = (*(Pos55a5*)&g_7f4c00);
			fcn_00500bb0(&m.due, 2, 0, 0);
			fcn_004c5530(&m);
			*(int*) (u + 0x70) = 1;
			*(Pos55a5*) (u + 0x52) = (*(Pos55a5*)&g_7f4c00);
			fcn_00500bb0((Pos55a5*) (u + 0x52), 8, 0, 0);
			return;
		}
		if (*(int*) (u + 0x70) != 1) {
			return;
		}
		if (*(int*) (u + 0xb0) != 0) {
			h = g_7f4ca0 + *(unsigned short*) (u + 8) * 0x21c;
			f = fcn_00507f10(h, 3) > 0.1f ? fcn_00507f10(h, 3) : 0.1f;
			a = gm_WalkEntityChain(*(unsigned short*) h);
			fcn_004ff210(*(unsigned short*) h, -(int) ((int) fcn_004fef80(h) * ((1.0f - f) * 0.5f)));
			d = (int) (a * f * 0.06f);
			fcn_004c51a0(*(int*) (u + 0xac), -1, g_773d75, d);
			fcn_0051af00(buf, 0x10ba, d);
			fcn_00545d40(*(int*) (u + 0xac), -1, buf, 0x20, 0x5fd, g_6b5c60);
			fcn_00546190(u);
			return;
		}
		fcn_0051af00(buf, 0x10bb);
		fcn_00545d40(*(int*) (u + 0xac), -1, buf, 0x20, 0x5fd, g_6b5c60);
	}
	fcn_00546190(u);
}
