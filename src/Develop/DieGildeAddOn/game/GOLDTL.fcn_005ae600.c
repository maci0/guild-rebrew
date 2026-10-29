


extern int g_7746d8;
extern int g_7746a0;
extern int g_14abc2c;
extern int g_14abc30;
extern char s_6aa3b0[];
extern char s_6ab2a0[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005c79a0(int);

void __cdecl fcn_005ae600(int arg)
{
	int a;
	int b;

	a = 0;
	b = 0;
	fcn_005338a0();
	if (fcn_005373e0((void*) fcn_005ae600, 0x67fff) != 0) {
		do {
			if (g_7746d8 & 0x200) {
				a = fcn_005338d0(s_6aa3b0, g_14abc2c, 0xc);
				b = fcn_005338d0(s_6ab2a0, g_14abc30, 0xc);
			}
			if ((g_7746d8 & 0x200) && g_7746a0 != 0) {
				if (g_7746a0 == a || g_7746a0 == b) {
					fcn_005c79a0(arg);
				}
			}
		} while (fcn_005373e0((void*) fcn_005ae600, 0x67fff) != 0);
	}
}
