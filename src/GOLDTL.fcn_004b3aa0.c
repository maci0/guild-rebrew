// FUNCTION: GOLD 0x004b3960
// SIZE: 132
// FUNCTION: GOLDTL 0x4b3aa0
// SIZE: 132

extern int g_77494c;
extern int g_14cbca0;
extern int g_1007cd0;
extern int g_14cbcb0;
extern char g_7728d4;

__declspec(dllimport) unsigned long __stdcall GetTickCount(void);
void __cdecl fcn_004c5790(int, int*);
void __cdecl fcn_00535960(void);
void __cdecl fcn_004b3490(void);
void __cdecl fcn_004b3810(int);

void __cdecl fcn_004b3aa0(int a1)
{
	int buf[0x1f];

	if (((*(unsigned char*)&g_77494c) & 8) != 0 || g_14cbca0 == -1) {
		buf[0] = GetTickCount();
		fcn_004c5790(5, buf);
	}
	while (g_1007cd0 != 0 && g_14cbcb0 == 0)
		fcn_00535960();
	if (g_14cbcb0 == 0 && g_7728d4 != 0) {
		if (g_7728d4 == 1)
			fcn_004b3490();
		else if (g_7728d4 == 2)
			fcn_004b3810(a1);
	}
}
