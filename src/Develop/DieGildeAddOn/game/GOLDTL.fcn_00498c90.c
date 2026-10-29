


#include <string.h>

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_773d75;
extern float g_66414c;
extern char g_67e968[];

char* __cdecl fcn_005463a0(int, int, int);
void __cdecl fcn_00505e20(int, int, int, char*, int);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
int __cdecl fcn_0050d170(int k);
void __cdecl fcn_004c5150(int a, int b, char c, int n);
void __cdecl fcn_004c5530(char* msg);
int __cdecl amt_ExecGebaeudeBauen(char* a1, char* a2, char* a3);
void __cdecl fcn_004c5420(int, int, int, int, int);

int __cdecl fcn_00498c90(char* a1, char* a2, char* a3)
{
	char msg[0xf8];
	char* q;

	if (*a2 == 4 && *a3 == 8) {
		q = fcn_005463a0(1, 1, *(int*) (a3 + 4));
		if (q == 0) {
			return 0;
		}
		fcn_00505e20(*(int*) (a2 + 4), *(int*) (a1 + 4), *(int*) (q + 0xb0), q, 1);
		return 0x13;
	}
	if (*a3 == 4) {
		memset(msg, 0, sizeof(msg));
		msg[4] = 0x1e;
		*(int*) (msg + 8) = *(int*) (a1 + 4);
		*(int*) (msg + 0xc) = *(int*) (a3 + 4);
		msg[0x36] = 1;
		*(int*) (msg + 0x28) = (*(int*)&g_7f4c00);
		*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
		*(int*) (msg + 0x30) = g_7f4c08;
		*(short*) (msg + 0x34) = g_7f4c0c;
		*(int*) (msg + 0x58) = *(int*) (a3 + 4);
		fcn_004c4eb0(g_67e968);
		fcn_004c5150(-1, *(int*) (a1 + 4), (*(char*)&g_773d75), (int) (fcn_0050d170(*(int*) (a2 + 4)) * g_66414c));
		fcn_004c5530(msg);
		fcn_004c4ef0(g_67e968);
		return 0x13;
	}
	if (amt_ExecGebaeudeBauen(a1, a2, a3) != 0) {
		fcn_004c5420(*(int*) (a1 + 4), 0x1c8, 4, 0x1000000, 0);
		return 0x13;
	}
	return 0;
}
