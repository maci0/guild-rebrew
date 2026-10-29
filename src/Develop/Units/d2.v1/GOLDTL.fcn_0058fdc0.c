extern int g_7746d8;
extern int g_14b5874;
extern int g_14ad100;
extern int g_14a7d28;
extern int g_14a7b50;
extern int g_14ad0f0;
extern int g_7746a0;

extern char g_6a9934[];
extern char g_6a956c[];
extern char g_6a9924[];
extern char g_6a9914[];
extern char g_6a9580[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_00590500(char*);
void __cdecl fcn_0058f020(char*);
void __cdecl fcn_005944d0(char*);
void __cdecl fcn_005ba8e0(char*);
void __cdecl fcn_005b88b0(char*, char*);
void __cdecl fcn_005be140(char*, int);
void __cdecl fcn_005cf560(char*);

/* ADDRESS: GOLDTL 0x0058fdc0 */
void __cdecl fcn_0058fdc0(char* e)
{
	int r1;
	int r2;
	int r3;
	int r4;
	int r5;

	r1 = 0;
	r2 = 0;
	r3 = 0;
	r4 = 0;
	r5 = 0;
	fcn_005338a0();
	while (fcn_005373e0((void*) fcn_0058fdc0, 0x67fff) != 0) {
		fcn_00590500(e);
		if (g_7746d8 & 0x200) {
			r1 = fcn_005338d0(g_6a9934, g_14b5874, 0x13);
			r2 = fcn_005338d0(g_6a956c, g_14ad100, 0x15);
			r3 = fcn_005338d0(g_6a9924, g_14a7d28, 0xc);
			r4 = fcn_005338d0(g_6a9914, g_14a7b50, 0xc);
			r5 = fcn_005338d0(g_6a9580, g_14ad0f0, 0xe);
			fcn_0058f020(e);
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == r1) {
				fcn_005944d0(e);
			} else if (g_7746a0 == r2) {
				fcn_005ba8e0(e);
			} else if (g_7746a0 == r3) {
				fcn_005cf560(e);
			} else if (g_7746a0 == r4) {
				fcn_005b88b0(e, g_6a9914);
			} else if (g_7746a0 == r5) {
				fcn_005be140(e, *(int*) (e + 0x5d));
			}
		}
	}
}
