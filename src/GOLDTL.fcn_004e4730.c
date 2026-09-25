extern int g_772f3c;
extern char* g_6b8300;
extern char g_77666a;
extern char* g_772f40;
extern int g_77250c;
extern int g_7f4c00;
extern int g_772f4c;
extern int g_6791c8;
extern char* g_67a370;
extern int g_6791d0;
extern int g_68bfc4;
extern int g_772f50;
extern int g_1040490;
extern int g_1040494;
extern char g_67d67c[];

typedef void(__cdecl* hook_4e4730)(char*, int, char*, int);

int __cdecl fcn_00413160(void);
void __cdecl fcn_004432d0(int, int);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_00448360(char*, int, int);
void __cdecl fcn_004428d0(char*, int, int);
void __cdecl fcn_00476970(int);
int __cdecl fcn_00500e20(int*);
void __cdecl fcn_0052a7d0(void);
void __cdecl fcn_00443230(int);
void __cdecl fcn_00473150(int);
void __cdecl fcn_004730c0(int, int, int, int, char*, int, int);

// FUNCTION: GOLDTL 0x4e4730
// SIZE: 376

void __cdecl fcn_004e4730(char* a1)
{
	char buf[0x80];
	char* ui;
	int n;

	if (g_772f3c != 0)
		return;
	{
		int s;

		s = fcn_00413160();
		fcn_004432d0(s, 0);
		fcn_0064d41a(buf, "scenes/*%s", a1);
		fcn_00448360(buf, 0, 0);
		fcn_004432d0(0, 1);
		fcn_004432d0(s, 0);
	}
	if (g_6b8300 != 0) {
		if (g_77666a == 0) {
			n = 2;
			g_6b8300[0x8036] = (g_6b8300[0x8036] & 0xeb) | 8;
		} else {
			n = 1;
			g_6b8300[0x8036] = (g_6b8300[0x8036] & 0xe7) | 4;
		}
		fcn_004428d0(g_6b8300, n >> 1, 1);
	}
	if ((g_772f40[0x26] & 0x20) != 0)
		fcn_00476970(g_77250c);
	if (fcn_00500e20(&g_7f4c00) == 3)
		fcn_0052a7d0();
	g_6791c8 = -2;
	g_772f4c++;
	if (g_67a370 != 0) {
		ui = *(char**) (g_67a370 + 0x3c8);
		if (ui != 0 && *(hook_4e4730*) (ui + 0x210) != 0)
			(*(hook_4e4730*) (ui + 0x210))(g_67a370, 4, ui + 0x214, 0);
	}
	g_68bfc4 = g_6791d0;
	fcn_00443230(1);
	if (g_772f50 != 0) {
		fcn_00473150(g_772f50);
		g_772f50 = 0;
	}
	fcn_004730c0(0, 0, g_1040494, g_1040490, g_67d67c, 0x5a, 0xa);
}
