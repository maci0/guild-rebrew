// FUNCTION: GOLD 0x0048e360
// SIZE: 251
// FUNCTION: GOLDTL 0x48d910
// SIZE: 251

#include <string.h>

extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_773d75;
extern float g_66414c;
extern char g_67e968[];

void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
int __cdecl fcn_0050d170(int k);
void __cdecl fcn_004c5150(int a, int b, char c, int n);
void __cdecl fcn_004c5530(char* msg);
int __cdecl fcn_004a4d90(char* a1, char* a2, char* a3);

int __cdecl fcn_0048d910(char* a1, char* a2, char* a3)
{
	char msg[0xf8];

	if (*a3 == 4) {
		memset(msg, 0, sizeof(msg));
		msg[4] = 0x1e;
		*(int*) (msg + 8) = *(int*) (a1 + 4);
		*(int*) (msg + 0xc) = *(int*) (a3 + 4);
		msg[0x36] = 1;
		*(int*) (msg + 0x28) = g_7f4c00;
		*(int*) (msg + 0x2c) = g_7f4c04;
		*(int*) (msg + 0x30) = g_7f4c08;
		*(short*) (msg + 0x34) = g_7f4c0c;
		*(int*) (msg + 0x58) = *(int*) (a3 + 4);
		fcn_004c4eb0(g_67e968);
		fcn_004c5150(-1, *(int*) (a1 + 4), g_773d75, (int) (fcn_0050d170(*(int*) (a2 + 4)) * g_66414c));
		fcn_004c5530(msg);
		fcn_004c4ef0(g_67e968);
		return 0x40;
	}
	return fcn_004a4d90(a1, a2, a3) ? 0x40 : 0;
}
