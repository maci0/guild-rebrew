// FUNCTION: GOLD 0x00586a80
// SIZE: 114
// FUNCTION: GOLDTL 0x0058f020
// SIZE: 114

extern char* g_7746b4;
extern int g_14ce8cc;
extern unsigned short g_774970;
extern char g_7f4ca0[];
extern char g_6a9834[];

void __cdecl fcn_005904a0(char*, int);
void __cdecl fcn_004c54c0(int, int, int, int);
char* __cdecl fcn_00530bf0(char*, char*);

void __cdecl fcn_0058f020(void)
{
	char* r;

	if (g_7746b4 != 0 && (g_7746b4[0x1b4] & 1) && g_14ce8cc != 0) {
		fcn_005904a0(g_7746b4, 0);
		fcn_004c54c0(*(int*) (g_7f4ca0 + g_774970 * 540 + 4), *(int*) (g_7746b4 + 4), -5, 0);
		r = fcn_00530bf0(g_7746b4, g_6a9834);
		if (r != 0) {
			*(int*) (r + 0xc8c) = 1;
		}
	}
}
