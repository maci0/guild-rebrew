#include "client_types.h"

extern char g_7f4ca0[];
extern pos14_7f4c00 gm_GameTime;

int __cdecl fcn_004a5fe0(char*, int, int, int, int, int, int, int*);
void __cdecl fcn_00500bb0(void*, int, int, int);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_004c5620(char, unsigned char*);

/* ADDRESS: GOLDTL 0x00578e10 */
void __cdecl fcn_00578e10(char* action)
{
	int flag;
	int zero;
	int n;
	char* rec;

	flag = 4;
	zero = 0;
	if ((*(unsigned char*) (action + 0x78) & flag) != 0) {
		return;
	}
	rec = g_7f4ca0 + *(unsigned short*) (action + 8) * 0x21c;
	n = fcn_004a5fe0(rec,
	    5, flag, zero, zero, zero, 5, (int*) (action + 0xb4));
	if (n == 0) {
		fcn_00546190(action);
		return;
	}
	if (n < 5) {
		*(int*) (action + 0xb4 + n * 4) = 0;
	}
	*(int*) (action + 0xb0) = 0;
	*(pos14_7f4c00*) (action + 0x52) = *(pos14_7f4c00*) &gm_GameTime;
	fcn_00500bb0(action + 0x52, 0, 1, 0);
	*(int*) (action + 0x84) = fcn_004c5620(0, (unsigned char*) action);
}
