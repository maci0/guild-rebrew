// FUNCTION: GOLDTL 0x4e48b0

extern int g_772f3c;
extern unsigned char* g_772f50;
extern int g_1040490;
extern int g_1040494;
extern char g_67d67c[];
extern int g_68bfb8;

unsigned char* __cdecl fcn_004730c0(int, int, int, int, char*, int, int);
int __cdecl fcn_005373e0(int, int);

void __cdecl fcn_004e48b0(void)
{
	if (g_772f3c == 0) {
		g_772f50 = fcn_004730c0(0, 0, g_1040494, g_1040490, g_67d67c, 0x5a, 1);
		while ((*g_772f50 & 4) == 0) {
			fcn_005373e0(0, g_68bfb8 | 0x80);
		}
	}
}
