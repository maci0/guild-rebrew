// FUNCTION: GOLD 0x005ae800
// SIZE: 440
// FUNCTION: GOLDTL 0x005b9df0
// SIZE: 440

#include <string.h>
#pragma intrinsic(memset)

typedef struct {
	short s[7];
} Stamp5b9d;
// SIZE 0xe

typedef struct {
	int pad0;
	int f4;
	char pad8[0x214];
} Ent5b9d;
// SIZE 0x21c

extern char g_7f4ca0[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern char g_77531c;

char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl fcn_005462a0(void);
int __cdecl fcn_0057eba0(int, char*, int, int);
void __cdecl fcn_00500bb0(Stamp5b9d*, int, int, int);
void __cdecl fcn_004c5530(char*);
void __cdecl fcn_0050de80(char*, char*);
int __cdecl fcn_0050ddf0(int, int);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_0057e880(int, char*, int, int);

int __cdecl fcn_005b9df0(int idx, char* p, char* q, char* r)
{
	int res;
	char* e;
	char msg[0xf8];
	char info[0xb8];

	res = 0;
	for (e = fcn_005463a0(2, 3, *(int*) (p + 2), 0, 0x11); e != 0; e = fcn_005462a0()) {
		*(Stamp5b9d*) (e + 0x52) = (*(Stamp5b9d*)&g_7f4c00);
		*(int*) (e + 0x70) = -1;
	}
	if (fcn_0057eba0(0x24, r, 0, 0) == 1) {
		memset(msg, 0, sizeof(msg));
		msg[4] = 0xf;
		*(int*) (msg + 8) = ((Ent5b9d*)g_7f4ca0)[idx].f4;
		*(int*) (msg + 0xc) = -1;
		msg[0x36] = 2;
		*(Stamp5b9d*) (msg + 0x28) = (*(Stamp5b9d*)&g_7f4c00);
		fcn_00500bb0((Stamp5b9d*) (msg + 0x28), 0, 0, 1);
		*(int*) (msg + 0x58) = *(int*) (p + 2);
		*(int*) (msg + 0x5c) = *(int*) (q + 1);
		*(int*) (msg + 0x60) = *(int*) (r + 1);
		*(int*) (msg + 0x78) = p[0x28];
		g_77531c = (char) *(int*) (msg + 0x78);
		fcn_004c5530(msg);
		if (p[0x28] != 0) {
			fcn_0050de80(p, info);
			res = fcn_0050ddf0(*(int*) (info + 0xb0), p[0x28]);
			fcn_004c51a0(-1, ((Ent5b9d*)g_7f4ca0)[idx].f4, g_773d75, res);
		}
		if (idx == g_774970) {
			fcn_0057e880(0x24, r, 0, 0);
		}
	}
	return res;
}
