extern int g_67a370;
extern int g_773dd8;


void __cdecl fcn_00437ac0(int, int, int, void (__cdecl*)(void));
void __cdecl fcn_00514d80(void);
void __cdecl fcn_00454560(int);
int __cdecl fcn_00454c00(int, int, int, int);
void __cdecl fcn_00450a00(int);

void __cdecl fcn_00514e30(void)
{
	fcn_00437ac0(g_67a370, 0, 0xc0, fcn_00514d80);
	if (g_773dd8) {
		fcn_00454560(g_773dd8);
		g_773dd8 = fcn_00454c00(0, 0x40, 8, 7);
	}
	fcn_00450a00(1);
}
