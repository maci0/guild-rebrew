// FUNCTION: GOLD 0x594f30
// FUNCTION: GOLDTL 0x0059de00

extern int g_7746d8;
extern int g_7746a0;
extern int g_14ad118;
extern int g_14ad110;
extern int g_14ad108;
extern int g_14abc30;
extern int g_14abc2c;
extern int g_14ad170;
extern int g_14ad140;
extern int g_14abd28;
extern int g_14ad168;
extern int g_14ad0f0;
extern int g_14ad0e8;
extern int g_14ad100;
extern char s_6aa5ac[];
extern char s_6aa594[];
extern char s_6aa584[];
extern char s_6aa3c0[];
extern char s_6aa3b0[];
extern char s_6aa564[];
extern char s_6aa544[];
extern char s_6aa52c[];
extern char s_6aa514[];
extern char s_6a9580[];
extern char s_6aa3d0[];
extern char s_6aa508[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_0059a0e0(void);
void __cdecl fcn_005be140(char*, int);
void __cdecl fcn_005c5b10(char*);
void __cdecl fcn_005ba8e0(char*);
void __cdecl fcn_005c72f0(char*);
void __cdecl fcn_005c79a0(char*);
void __cdecl fcn_0059d020(char*);
void __cdecl fcn_0059d310(char*);
void __cdecl fcn_0059d630(char*);
void __cdecl fcn_0059d9b0(char*);
void __cdecl fcn_0059dc50(char*);

void __cdecl fcn_0059de00(char* e)
{
	int a;
	int b;
	int c;
	int d;
	int f;
	int g;
	int h;
	int i;
	int j;
	int k;
	int l;
	int m;

	k = 0;
	j = 0;
	h = 0;
	i = 0;
	a = 0;
	f = 0;
	d = 0;
	b = 0;
	c = 0;
	g = 0;
	l = 0;
	m = 0;
	fcn_005338a0();
	if (fcn_005373e0((void*) fcn_0059de00, 0x67fff) != 0) {
		do {
			if (g_7746d8 & 0x200) {
				a = fcn_005338d0(s_6aa5ac, g_14ad118, 0xd);
				b = fcn_005338d0(s_6aa594, g_14ad110, 0x15);
				c = fcn_005338d0(s_6aa584, g_14ad108, 0x17);
				if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x35) != 0) {
					d = fcn_005338d0(s_6aa3c0, g_14abc30, 0x17);
				}
				if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x34) != 0) {
					f = fcn_005338d0(s_6aa3b0, g_14abc2c, 0x17);
				}
				k = fcn_005338d0(s_6aa564, g_14ad170, 0x17);
				l = fcn_005338d0(s_6aa544, g_14ad140, 0x17);
				m = fcn_005338d0(s_6aa52c, g_14abd28, 0x17);
				g = fcn_005338d0(s_6aa514, g_14ad168, 0x17);
			}
			if (g_7746d8 & 0x400) {
				h = fcn_005338d0(s_6a9580, g_14ad0f0, 0xe);
				i = fcn_005338d0(s_6aa3d0, g_14ad0e8, 0xe);
				j = fcn_005338d0(s_6aa508, g_14ad100, 0x15);
			}
			fcn_0059a0e0();
			if (g_7746a0 != 0) {
				if (g_7746a0 == h) {
					fcn_005be140(e, *(int*) (e + 0x5d));
				}
				else if (g_7746a0 == i) {
					fcn_005c5b10(e);
				}
				else if (g_7746a0 == j) {
					fcn_005ba8e0(e);
				}
				else if (g_7746a0 == a) {
					fcn_005c72f0(e);
				}
				else if (g_7746a0 == f || g_7746a0 == d || g_7746a0 == g) {
					fcn_005c79a0(e);
				}
				else if (g_7746a0 == b) {
					fcn_0059d020(e);
				}
				else if (g_7746a0 == c) {
					fcn_0059d310(e);
				}
				else if (g_7746a0 == k) {
					fcn_0059d630(e);
				}
				else if (g_7746a0 == l) {
					fcn_0059d9b0(e);
				}
				else if (g_7746a0 == m) {
					fcn_0059dc50(e);
				}
			}
		} while (fcn_005373e0((void*) fcn_0059de00, 0x67fff) != 0);
	}
}
