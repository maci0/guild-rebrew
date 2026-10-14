


#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_6a59fc[];

void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
char* __cdecl fcn_00508e40(int);
void __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);
int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_005502d0(char* u)
{
	char text[0x400];
	char* a;
	char* b;

	*(int*) (u + 0x84) = -1;
	if (u[0x78] & 4) {
		return;
	}
	*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (u + 0x52), 0x18, 0, 0);
	if (u[0x78] & 2) {
		b = fcn_00508e40(*(int*) (u + 0xb0));
		a = fcn_00508e40(*(int*) (u + 0xac));
		if (a == 0 || b == 0) {
			*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
			fcn_004c5620(-1, u);
			return;
		}
		if (b[2] == 6 || b[2] == 7) {
			fcn_0051af00(text, 0x1d64, *(unsigned short*) a, (pos14_7f4c00*) (u + 0x52), *(unsigned short*) a);
			fcn_00545d40(*(int*) (b + 4), -1, text, 0, 0x5fb, g_6a59fc);
		}
	}
	fcn_004c5620(0, u);
}
