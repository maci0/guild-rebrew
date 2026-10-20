extern int g_67a370;
extern int g_6f1c28;

void __cdecl fcn_00438e60(int, int, int, void*);
void __cdecl fcn_00454560(int);
int __cdecl fcn_00454c00(int, int, int, int);

/* ADDRESS: GOLD 0x00511870 */
void __cdecl fcn_00511870(void)
{
	if (g_6f1c28 != 0) {
		fcn_00454560(g_6f1c28);
		g_6f1c28 = 0;
	}
	fcn_00438e60(g_67a370, 0, 0x40, (void*) 0x511840);
	g_6f1c28 = fcn_00454c00(0, 0x40, 8, 7);
}
