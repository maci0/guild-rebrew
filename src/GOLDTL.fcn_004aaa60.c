#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char s_67fb2c[];

char* __cdecl fcn_00508e40(int id);
char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);
unsigned short __cdecl gm_RandomMod(int n);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c4ef0(char* s);

// FUNCTION: GOLD 0x004aa940
// FUNCTION: GOLDTL 0x4aaa60
int __cdecl fcn_004aaa60(char* a1, int a2, char* x)
{
	char msg[0xf8];
	char* p;

	if (x[0] != 7) {
		return 0;
	}
	p = fcn_00508e40(*(int*) (x + 4));
	if (!p) {
		return 0;
	}
	gm_StartFilteredEntitySearch(1, 5, 0xa);
	msg[4] = 0x35;
	msg[0x36] = 2;
	*(int*) (msg + 8) = *(int*) (a1 + 4);
	*(int*) (msg + 0xc) = *(int*) (a1 + 4);
	*(int*) (msg + 0x58) = (*(int*)&g_7f4c00);
	*(int*) (msg + 0x5c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x60) = g_7f4c08;
	*(short*) (msg + 0x64) = g_7f4c0c;
	msg[0x6d] = (char) gm_RandomMod(0x1d);
	*(int*) (msg + 0x68) = *(int*) (p + 4);
	fcn_004c4eb0(s_67fb2c);
	fcn_004c5530(msg);
	fcn_004c4ef0(s_67fb2c);
	return 1;
}
