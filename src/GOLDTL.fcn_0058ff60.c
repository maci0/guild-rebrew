


#include <string.h>

typedef struct
{
	char b[14];
} Name14;
// SIZE 0xe

typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	int xc;
	char pad10[0x18];
	Name14 name;
	unsigned char x36;
	char pad37[0x21];
	int x58;
	int x5c;
	int x60;
	char pad64[0x94];
} Packet;
// SIZE 0xf8

extern unsigned short g_774970;
extern char g_7f4ca0[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_0051af00(void*, int, ...);
int __cdecl fcn_00526120(char*, int);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_004c5530(Packet*);

int __cdecl fcn_0058ff60(char* a1, unsigned short* a2, int a3)
{
	Packet pkt;
	char buf[0x400];
	char* d;

	fcn_0051af00(buf, 0x413a, *a2);
	if (fcn_00526120(buf, 1) != 0) {
		d = fcn_00502cd0(*(int*) (a1 + 0x5d), 1, 0, 0x211);
		memset(&pkt, 0, sizeof(pkt));
		pkt.type = 0x8f;
		pkt.x36 = 1;
		pkt.x8 = *(int*) (g_7f4ca0 + g_774970 * 540 + 4);
		pkt.xc = *(int*) (a1 + 1);
		pkt.name = (*(Name14*)&g_7f4c00);
		if (d != 0) {
			pkt.x60 = *(int*) (d + 2);
		} else {
			pkt.x60 = -1;
		}
		pkt.x58 = *(int*) (a2 + 2);
		pkt.x5c = a3;
		fcn_004c5530(&pkt);
		return 1;
	}
	return 0;
}
