// FUNCTION: GOLDTL 0x00584800
// SIZE: 164

extern int* g_665f08;
extern int g_774a14;
extern char* g_6a8204[];
extern char* g_6a8238[];
extern char g_6a935c[];
extern char g_6a9340[];
extern char g_6a9324[];
extern char g_6a9308[];
extern char g_6a92ec[];
extern char g_6a92d0[];
extern char g_6a92b4[];

int __cdecl fcn_00519190(char*, ...);

void __cdecl fcn_00584800(void)
{
	if (g_774a14 == 0) {
		fcn_00519190(g_6a935c);
		return;
	}
	fcn_00519190(g_6a9340, g_6a8204[g_665f08[0]]);
	fcn_00519190(g_6a9324, g_6a8204[g_665f08[1]]);
	fcn_00519190(g_6a9308, g_665f08[21]);
	fcn_00519190(g_6a92ec, g_6a8238[g_665f08[22]]);
	fcn_00519190(g_6a92d0, g_665f08[23]);
	fcn_00519190(g_6a92b4, g_665f08[24]);
}
