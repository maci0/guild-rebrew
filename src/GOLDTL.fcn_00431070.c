// FUNCTION: GOLD 0x00431490
// SIZE: 119
// FUNCTION: GOLDTL 0x431070
// SIZE: 119

extern int g_6b7fec;
extern char g_6b7fe8;
extern int g_6b7fdc;
extern int g_6b7fe0;
extern char g_67a090[];

int __cdecl fcn_0042f6d0(char*, int);
char* __cdecl fcn_0066096a(char*, int);
int __cdecl fcn_0064d41a(char*, char*, ...);

int __cdecl fcn_00431070(char* name, char flag)
{
	char cwd[0x100];
	char buf[0x100];

	g_6b7fec = 0;
	g_6b7fe8 = flag;
	g_6b7fdc = fcn_0042f6d0(name, 0);
	fcn_0066096a(cwd, 0x100);
	fcn_0064d41a(buf, g_67a090, name, cwd);
	g_6b7fe0 = 0;
	return g_6b7fdc != 0;
}
