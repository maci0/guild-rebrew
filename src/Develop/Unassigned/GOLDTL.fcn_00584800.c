

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

int __cdecl io_AppendText(char*, ...);

void __cdecl fcn_00584800(void)
{
	if (g_774a14 == 0) {
		io_AppendText(g_6a935c);
		return;
	}
	io_AppendText(g_6a9340, g_6a8204[g_665f08[0]]);
	io_AppendText(g_6a9324, g_6a8204[g_665f08[1]]);
	io_AppendText(g_6a9308, g_665f08[21]);
	io_AppendText(g_6a92ec, g_6a8238[g_665f08[22]]);
	io_AppendText(g_6a92d0, g_665f08[23]);
	io_AppendText(g_6a92b4, g_665f08[24]);
}
