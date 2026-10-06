extern int g_67a370;
extern int g_699b10;
extern int g_6b86d8;
extern int g_6b86dc;
extern int g_67530c;

// FUNCTION: GOLDTL 0x516ed0

void __cdecl fcn_00437ac0(int, int, int, void*);
void __cdecl fcn_00515f30(void);
void __cdecl fcn_00516000(void);
char* __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(char*);
void __cdecl fcn_005312d0(int);
void __cdecl fcn_0040c300(int);

void __cdecl fcn_00516ed0(void)
{
	char* p;

	fcn_00437ac0(g_67a370, 0, 0xa0, (void*) fcn_00515f30);
	fcn_00516000();
	g_6b86d8 = 0x400;
	g_6b86dc = 0x40;
	if (g_699b10 != -1) {
		p = fcn_00426cc0(g_699b10);
		if (p != 0) {
			fcn_00428720(p);
			fcn_005312d0(*(int*) (p + 0x100));
			g_699b10 = -1;
		}
	}
	fcn_0040c300(g_67a370);
	g_67530c = -1;
}
