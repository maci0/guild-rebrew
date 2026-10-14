


extern int g_7746d8;
extern int g_7746a0;
extern char* g_7746cc;
extern int g_14ad0f0;
extern int g_14ad118;
extern int g_14ad160;
extern int g_14ad140;
extern int g_14a5554;
extern int g_14ad100;
extern char s_6a9580[];
extern char s_6aa5ac[];
extern char s_6ab3cc[];
extern char s_6aa544[];
extern char s_6ab3b0[];
extern char s_6a956c[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005be140(int, int);
void __cdecl fcn_005c72f0(int);
void __cdecl fcn_005af770(int);
void __cdecl fcn_005ad950(int);
void __cdecl fcn_005ada30(int);
void __cdecl fcn_005ba8e0(int);

void __cdecl fcn_005afea0(int arg)
{
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;

	a = 0;
	b = 0;
	c = 0;
	f = 0;
	d = 0;
	e = 0;
	fcn_005338a0();
	if (fcn_005373e0((void*) fcn_005afea0, 0x67fff) != 0) {
		do {
			if (g_7746d8 & 0x200) {
				a = fcn_005338d0(s_6a9580, g_14ad0f0, 0xe);
				b = fcn_005338d0(s_6aa5ac, g_14ad118, 0xd);
				c = fcn_005338d0(s_6ab3cc, g_14ad160, 0x16);
				d = fcn_005338d0(s_6aa544, g_14ad140, 0x17);
				e = fcn_005338d0(s_6ab3b0, g_14a5554, 0xc);
				f = fcn_005338d0(s_6a956c, g_14ad100, 0x15);
			}
			if (g_7746a0 != 0 && (g_7746d8 & 0x200)) {
				if (g_7746a0 == a) {
					fcn_005be140(arg, *(int*) (g_7746cc + 0x14));
				}
				else if (g_7746a0 == b) {
					fcn_005c72f0(arg);
				}
				else if (g_7746a0 == c) {
					fcn_005af770(arg);
				}
				else if (g_7746a0 == d) {
					fcn_005ad950(arg);
				}
				else if (g_7746a0 == e) {
					fcn_005ada30(arg);
				}
				else if (g_7746a0 == f) {
					fcn_005ba8e0(arg);
				}
			}
		} while (fcn_005373e0((void*) fcn_005afea0, 0x67fff) != 0);
	}
}
