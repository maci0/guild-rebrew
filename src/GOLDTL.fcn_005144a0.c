extern char g_7e23ea[];
extern char g_7e240a[];
extern char g_7e1d00[];
extern int g_7e23e4;
extern char g_7e23e8;
extern char g_7e23e9;
extern char g_7e23e3;



#include <string.h>

void __cdecl fcn_0053d490(int, int);
void __cdecl fcn_0053cd40(int);

int __cdecl fcn_005144a0(char* p, char* s)
{
	strcpy(g_7e23ea, p + 0x30);
	strcpy(g_7e240a, s);
	strcpy(g_7e1d00, "Eurer Stadt");
	fcn_0053d490(0xc6, 1);
	fcn_0053cd40(0xc6);
	strcpy(p + 0x30, g_7e23ea);
	strcpy(s, g_7e240a);
	*(short*) (p + 0xa) = 0x12;
	*(int*) (p + 0x54) = g_7e23e4;
	p[9] = g_7e23e8;
	p[0xc] = g_7e23e9;
	p[0x164] = g_7e23e3;
	return 1;
}
