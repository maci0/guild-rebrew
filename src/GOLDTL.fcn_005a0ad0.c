extern int g_772514;
extern char g_6a9694[];

void __cdecl fcn_0046f2c0(int, int);
int __cdecl fcn_00519190(char*, ...);
void __cdecl fcn_0046f740(int, int, int, int);
unsigned short __cdecl gm_RandomMod(unsigned short);

/* ADDRESS: GOLDTL 0x005a0ad0 */
void __cdecl fcn_005a0ad0(int a, unsigned char* p)
{
	int i;
	int y;
	int x;

	fcn_0046f2c0(g_772514, 1);
	fcn_00519190(g_6a9694, a);
	i = 0;
	y = 0x1d;
	x = 0x1c;
	if (*(char*) (*(int*) p + 2) == 6) {
		while (i < p[4]) {
			fcn_0046f740(x, y, p[0xc + i] + 0x75a, g_772514);
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
	else {
		while (i < p[4]) {
			fcn_0046f740(x, y, 0x761, g_772514);
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
	fcn_0046f740(x, y, gm_RandomMod(6) + 0x75b, g_772514);
}
