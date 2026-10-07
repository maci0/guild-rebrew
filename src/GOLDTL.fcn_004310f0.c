// FUNCTION: GOLD 0x00431510
// FUNCTION: GOLDTL 0x4310f0

extern int g_6b7fdc;
extern int g_6b7fec;
extern int g_6b7fe4;
extern char g_6b7fe0[];
extern char g_6b7fe8;
extern char g_67a0b8[];

void __cdecl fcn_0042fc50(int);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_0041d9e0(char*);
int __cdecl fcn_0041e3e0(int, void*);
int __cdecl fcn_0041e350(void*);
void __cdecl fcn_0041e410(int*);
int __cdecl CloseVfsStream(int handle);

void __cdecl fcn_004310f0(char verbose)
{
	int it[3];
	char buf[0x100];
	int s;

	if (g_6b7fdc != 0) {
		fcn_0042fc50(g_6b7fdc);
		g_6b7fdc = 0;
	}
	if (g_6b7fec != 0 && verbose != 0) {
		fcn_0064d41a(buf, g_67a0b8, g_6b7fec);
		fcn_0041d9e0(buf);
	}
	if (g_6b7fe4 != 0) {
		s = fcn_0041e3e0(g_6b7fe4, it);
		while (s != 0) {
			CloseVfsStream(s);
			s = fcn_0041e350(it);
		}
	}
	g_6b7fec = 0;
	if ((*(int*)g_6b7fe0) != 0) {
		fcn_0041e410(&(*(int*)g_6b7fe0));
	}
	g_6b7fe8 = 0;
}
