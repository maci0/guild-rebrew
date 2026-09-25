// FUNCTION: GOLDTL 0x005afd20
// SIZE: 376

extern int g_7746d8;
extern int g_7746a0;
extern int g_14abcbc;
extern int g_14abcd8;
extern int g_14a7b50;
extern int g_14a7d28;
extern int g_14abce4;
extern char s_6ab3a0[];
extern char s_6ab394[];
extern char s_6aa34c[];
extern char s_6a9924[];
extern char s_6ab384[];
extern char s_6ab368[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_005b6300(char*, char*);
void __cdecl fcn_005af4e0(char*);
void __cdecl fcn_005afa00(char*);
void __cdecl fcn_005afca0(char*);
void __cdecl fcn_005cf560(char*);

void __cdecl fcn_005afd20(char* arg)
{
	int a;
	int b;
	int c;
	int d;
	int e;

	a = 0;
	b = 0;
	e = 0;
	c = 0;
	d = 0;
	fcn_005338a0();
	if (fcn_005373e0((void*) fcn_005afd20, 0x67fff) != 0) {
		do {
			if (g_7746d8 & 0x200) {
				a = fcn_005338d0(s_6ab3a0, g_14abcbc, 0x16);
				b = fcn_005338d0(s_6ab394, g_14abcd8, 0x16);
				c = fcn_005338d0(s_6aa34c, g_14a7b50, 0xc);
				d = fcn_005338d0(s_6a9924, g_14a7d28, 0x16);
				if (fcn_00502cd0(*(int*) (arg + 0x5d), 2, 6, 0, 0x147) != 0) {
					e = fcn_005338d0(s_6ab384, g_14abce4, 0x16);
				}
				else if (fcn_00502cd0(*(int*) (arg + 0x5d), 2, 6, 0, 0x148) != 0) {
					e = fcn_005338d0(s_6ab368, g_14abce4, 0x16);
				}
			}
			if ((g_7746d8 & 0x200) && g_7746a0 != 0) {
				if (g_7746a0 == c) {
					fcn_005b6300(arg, s_6aa34c);
				}
				else if (g_7746a0 == a) {
					fcn_005af4e0(arg);
				}
				else if (g_7746a0 == b) {
					fcn_005afa00(arg);
				}
				else if (g_7746a0 == e) {
					fcn_005afca0(arg);
				}
				else if (g_7746a0 == d) {
					fcn_005cf560(arg);
				}
			}
		} while (fcn_005373e0((void*) fcn_005afd20, 0x67fff) != 0);
	}
}
