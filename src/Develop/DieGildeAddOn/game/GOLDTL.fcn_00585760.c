


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
	char p60[8];
	int v68;
	char p6c[0x8c];
} Msg;

extern char g_7f4ca0[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

int __cdecl fcn_004ecf00(char*, int*, int*, int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_004c5530(Msg*);

int __cdecl fcn_00585760(char* e, int* list, int idx)
{
	int x;
	int y;
	Msg msg;

	if (fcn_004ecf00(e, &x, &y, 0) != 0) {
		return 0;
	}
	memset(&msg, 0, sizeof(msg));
	msg.kind = 0x96;
	msg.owner = *(int*) (g_7f4ca0 + *(unsigned short*) (e + 0x27) * 540 + 4);
	msg.entity = *(int*) (e + 1);
	msg.a = (*(int*)&g_7f4c00);
	msg.b = (*(int*)&g_7f4c04);
	msg.c = g_7f4c08;
	msg.d = g_7f4c0c;
	msg.flag = 1;
	msg.v5c = list[idx * 2 + 3];
	msg.v58 = list[0];
	msg.v68 = gm_RandomMod(0x5a0) + 1000;
	fcn_004c5530(&msg);
	return 1;
}
