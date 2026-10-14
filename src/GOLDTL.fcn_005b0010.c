


extern int g_7746d8;
extern int g_7746a0;
extern int g_14abc2c;
extern int g_14abc30;
extern int g_14ad168;
extern char g_6aa3b0[];
extern char g_6ab2a0[];
extern char g_6aa514[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005c79a0(int);

void __cdecl fcn_005b0010(int a)
{
	int x;
	int y;
	int z;

	x = 0;
	y = 0;
	z = 0;
	fcn_005338a0();
	while (fcn_005373e0(fcn_005b0010, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			x = fcn_005338d0(g_6aa3b0, g_14abc2c, 0xc);
			y = fcn_005338d0(g_6ab2a0, g_14abc30, 0xc);
			z = fcn_005338d0(g_6aa514, g_14ad168, 0x17);
		}
		if ((g_7746d8 & 0x200) && g_7746a0 != 0 &&
		    (g_7746a0 == x || g_7746a0 == y || g_7746a0 == z)) {
			fcn_005c79a0(a);
		}
	}
}
