extern int g_772f3c;
extern int g_772f4c;
extern int g_68bfc4;
extern int g_67a370;
extern int g_6791d0;
extern int g_68bfb8;
extern int g_6b8014;
extern int g_6b5cc0;
extern int g_6b5cbc;

typedef void(__cdecl* hook_4e4910)(char*, int, char*, int);

char* __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(char*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_004e4640(void);
void __cdecl fcn_004e4680(void);
void __cdecl gv_Free3Fields(int);
void __cdecl fcn_00433780(int);
void __cdecl fcn_00442e30(void);

// FUNCTION: GOLDTL 0x4e4910
// SIZE: 336
// FUNCTION: GOLD 0x004e30c0
// SIZE: 336

void __cdecl fcn_004e4910(void)
{
	char* w;
	char* ui;

	if (g_772f3c != 0)
		return;
	if (g_772f4c <= 0)
		return;
	if (g_68bfc4 != -1) {
		w = fcn_00426cc0(g_68bfc4);
		if (w != 0)
			fcn_00428720(w);
	}
	if (((char*)g_67a370) != 0) {
		ui = *(char**) (((char*)g_67a370) + 0x3c8);
		if (ui != 0 && *(hook_4e4910*) (ui + 0x294) != 0)
			(*(hook_4e4910*) (ui + 0x294))(((char*)g_67a370), 5, ui + 0x298, 0);
	}
	if (g_6791d0 != -1) {
		for (w = fcn_00426cc0(g_6791d0); w != 0 && (w[0x124] & 1) != 0; w = fcn_00426cc0(g_6791d0))
			fcn_005373e0(0, g_68bfb8 | 0x80);
	}
	fcn_004e4640();
	fcn_004e4680();
	if (g_68bfc4 != -1) {
		for (w = fcn_00426cc0(g_68bfc4); w != 0 && (w[0x124] & 1) != 0; w = fcn_00426cc0(g_68bfc4))
			fcn_005373e0(0, g_68bfb8 | 0x80);
	}
	if (*(int*) (((char*)g_67a370) + 0xb0) != 0) {
		gv_Free3Fields(*(int*) (((char*)g_67a370) + 0xb0));
		*(int*) (((char*)g_67a370) + 0xb0) = 0;
	}
	fcn_00433780(g_6b8014);
	g_6b5cc0 = 0;
	g_6b5cbc = 0;
	fcn_00442e30();
	g_772f4c--;
}
