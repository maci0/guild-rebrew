


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
	char p37[0xc1];
} Msg;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

void __cdecl fcn_004c5530(Msg*);

int __cdecl fcn_005df5a0(char* a1)
{
	Msg msg;

	msg.kind = 0xa4;
	msg.owner = *(int*) (a1 + 4);
	msg.entity = -1;
	msg.a = (*(int*)&g_7f4c00);
	msg.b = (*(int*)&g_7f4c04);
	msg.c = g_7f4c08;
	msg.d = g_7f4c0c;
	msg.flag = 1;
	fcn_004c5530(&msg);
	return 1;
}
