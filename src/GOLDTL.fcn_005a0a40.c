// FUNCTION: GOLD 0x00597860
// FUNCTION: GOLDTL 0x005a0a40

extern int g_772514;
extern char g_6a9694[];

void __cdecl fcn_0046f2c0(int, int);
int __cdecl fcn_00519190(char*, ...);
unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_0046f740(int, int, int, int);

void __cdecl fcn_005a0a40(int a)
{
	int i;
	int x;
	int y;

	fcn_0046f2c0(g_772514, 1);
	fcn_00519190(g_6a9694, a);
	i = 0;
	x = 0x1c;
	y = 0x1d;
	while (i < 3) {
		fcn_0046f740(x, y, fcn_0042e410(6) + 0x75b, g_772514);
		i++;
		if (i % 8 == 0) {
			x = 0;
		}
		else {
			x += 0x3a;
		}
		y = i > 7 ? 0x46 : 0x1d;
	}
}
