// FUNCTION: GOLD 0x004d1eb0
// FUNCTION: GOLDTL 0x4d2f10

extern int g_772efc;
extern int g_7e46ac;
extern int g_7725c8;
extern char g_68bd78[];

void __cdecl fcn_00420840(int);
char* __cdecl fcn_00426fd0(char*);
void __cdecl fcn_00428230(char*);
void __cdecl fcn_004cfa00(int);

void __cdecl fcn_004d2f10(void)
{
	char* p;

	if (g_772efc != 0) {
		fcn_00420840(g_772efc);
	}
	g_7e46ac = 0x7d6c6;
	g_7725c8 = 1;
	p = fcn_00426fd0(g_68bd78);
	if (p != 0) {
		fcn_00428230(p);
		fcn_004cfa00(*(int*) (p + 0x100));
	}
	g_7725c8 = 0;
}
