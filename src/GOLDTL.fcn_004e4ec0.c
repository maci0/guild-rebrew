// FUNCTION: GOLDTL 0x4e4ec0
// SIZE: 65

extern char g_7f4c00[];
extern int g_67a370;

void __cdecl fcn_00500e20(char*);
void __cdecl fcn_00437ac0(int, int, int, void*);
void __cdecl fcn_00516550(void);
void __cdecl fcn_005165b0(void);
void __cdecl fcn_00516040(void);

void __cdecl fcn_004e4ec0(void)
{
	fcn_00500e20(g_7f4c00);
	fcn_00437ac0(g_67a370, 0, 0xc0, fcn_00516550);
	fcn_00437ac0(g_67a370, 0, 0xc0, fcn_005165b0);
	fcn_00516040();
}
