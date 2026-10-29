#include "client_types.h"

extern char g_7f4ca0[];
extern pos14_7f4c00 g_7f4c00;

int __cdecl fcn_004a5fe0(char*, int, int, int, int, int, int, int*);
void __cdecl fcn_00500bb0(void*, int, int, int);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_004c5620(char, unsigned char*);

/* ADDRESS: GOLDTL 0x00578e10 */
void __cdecl fcn_00578e10(char* a0)
{
	int flag;
	int zero;
	int n;

	flag = 4;
	zero = 0;
	if ((*(unsigned char*) (a0 + 0x78) & flag) != 0) {
		return;
	}
	n = fcn_004a5fe0(g_7f4ca0 + *(unsigned short*) (a0 + 8) * 0x21c,
	    5, flag, zero, zero, zero, 5, (int*) (a0 + 0xb4));
	if (n == 0) {
		fcn_00546190(a0);
		return;
	}
	if (n < 5) {
		*(int*) (a0 + 0xb4 + n * 4) = 0;
	}
	*(int*) (a0 + 0xb0) = 0;
	*(pos14_7f4c00*) (a0 + 0x52) = *(pos14_7f4c00*) &g_7f4c00;
	fcn_00500bb0(a0 + 0x52, 0, 1, 0);
	*(int*) (a0 + 0x84) = fcn_004c5620(0, (unsigned char*) a0);
}
