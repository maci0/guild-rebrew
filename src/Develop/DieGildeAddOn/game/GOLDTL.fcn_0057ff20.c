


void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

// SIZE 0x114
typedef struct {
	int h0;
	int h4;
	unsigned char kind;
	char p9[3];
	int owner;
	int h10;
	int target;
	int a;
	int b;
	int c;
	short d;
	unsigned char flags;
	char p27[9];
	unsigned char count;
	char p31[3];
	int ids[56];
} Msg;

extern char g_7f4ca0[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

int __cdecl fcn_004e9ee0(void);
void __cdecl fcn_004c5980(Msg*);

void __cdecl fcn_0057ff20(int a)
{
	Msg msg;
	int i;
	unsigned int n;
	char t;

	if (a == 0 && fcn_004e9ee0() != 0) {
		memset(&msg, 0, sizeof(msg));
		n = 0;
		for (i = 0; i < 768; i++) {
			t = g_7f4ca0[i * 540 + 2];
			if (t == 6) {
				msg.owner = *(int*) (g_7f4ca0 + i * 540 + 4);
				msg.ids[n] = *(int*) (g_7f4ca0 + i * 540 + 4);
				n++;
			}
			else if (t == 7) {
				msg.ids[n] = *(int*) (g_7f4ca0 + i * 540 + 4);
				n++;
			}
		}
		msg.count = (unsigned char) n;
		msg.kind = 1;
		msg.flags = 0xa0;
		msg.target = -1;
		msg.a = (*(int*)&g_7f4c00);
		msg.b = (*(int*)&g_7f4c04);
		msg.c = g_7f4c08;
		msg.d = g_7f4c0c;
		fcn_004c5980(&msg);
	}
}
