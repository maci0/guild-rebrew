// FUNCTION: GOLD 0x0059a860
// FUNCTION: GOLDTL 0x005a3a40

extern char* g_7e2aa0;
extern char* g_7746c0;
extern int g_7746d4;
extern int g_6a25b8;
extern char* g_773d78;
extern char* g_7746cc;

void __cdecl fcn_0052f710(void);
void __cdecl fcn_005305a0(void);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_0057e880(int, int, int, int);
void __cdecl fcn_005ba910(int, int);

void __cdecl fcn_005a3a40(int a1, int a2)
{
	(*(int*)&g_7e2aa0) = 0;
	g_7746c0 = 0;
	fcn_0052f710();
	fcn_005305a0();
	g_7746d4 = 1;
	if (g_6a25b8 != -1) {
		fcn_00471af0(g_6a25b8, 0);
	}
	(*(int*)&g_7746cc) = fcn_00502cd0(*(int*) (g_773d78 + 0x5d), 1, 0, a2);
	if ((*(int*)&g_7746cc) != 0) {
		fcn_0057e880(0x17, (*(int*)&g_7746cc), 0, a2);
		while ((*(int*)&g_7746cc) != 0) {
			g_7746d4 = 1;
			fcn_005ba910(a1, 9);
		}
	}
	fcn_0057e880(0x18, (*(int*)&g_7746cc), 0, a2);
	fcn_0057e880(0x17, (*(int*)&g_7746cc), 1, a2);
	(*(int*)&g_7746cc) = 0;
	if (g_6a25b8 != -1) {
		fcn_00471af0(g_6a25b8, 1);
	}
}
