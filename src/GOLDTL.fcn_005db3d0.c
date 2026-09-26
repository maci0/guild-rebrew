// FUNCTION: GOLD 0x005ceea0
// SIZE: 144
// FUNCTION: GOLDTL 0x005db3d0
// SIZE: 144

void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

// SIZE 0xf8
typedef struct {
	int h0;
	unsigned char kind;
	char p5[3];
	int owner;
	int entity;
	char p10[0x18];
	int a;
	int b;
	int c;
	short d;
	unsigned char flag;
	char p37[0x21];
	int v58;
	int v5c;
	int v60;
	char p64[0x94];
} Msg;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

void __cdecl fcn_004c5530(Msg*);

void __cdecl fcn_005db3d0(char* a1, char* a2, int a3)
{
	Msg msg;

	memset(&msg, 0, sizeof(msg));
	msg.kind = 0x45;
	msg.owner = *(int*) (a1 + 4);
	msg.entity = -1;
	msg.a = (*(int*)&g_7f4c00);
	msg.b = (*(int*)&g_7f4c04);
	msg.c = g_7f4c08;
	msg.d = g_7f4c0c;
	msg.flag = 2;
	msg.v58 = *(int*) (a1 + 4);
	msg.v5c = *(int*) (a2 + 4);
	msg.v60 = a3;
	fcn_004c5530(&msg);
}
