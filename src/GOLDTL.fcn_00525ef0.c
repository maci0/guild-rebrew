#include "client_types.h"
extern char g_6b5c60[];
extern int g_6772c4;
extern int g_6b5c80;
extern int g_6b5c84;
extern int g_6772bc;
extern int g_6772c0;
extern int g_1040494;
extern int g_1040490;
// FUNCTION: GOLDTL 0x00525ef0

void __cdecl fcn_00473a90(int, int);

void __cdecl fcn_004116d0(void);
void __cdecl fcn_00533a40(char*);
void __cdecl fcn_00475220(char*);

void __cdecl fcn_00525ef0(void)
{
	fcn_00473a90(0, 0);
	ResetDisplayCounters();
	fcn_004116d0();
	fcn_00533a40(g_6b5c60);
	fcn_00475220(g_6b5c60);
	g_6772c4 = 1;
	g_6b5c80 = 0;
	g_6b5c84 = 0;
	g_6772bc = g_1040494 - 8;
	g_6772c0 = g_1040490;
}
