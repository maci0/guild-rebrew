extern int g_67a370;
extern int g_6f1c28;

void __cdecl fcn_00438e60(int, int, int, void*);
void __cdecl fcn_00454560(int);
int __cdecl fcn_00454c00(int, int, int, int);
void __cdecl UpdateSceneLighting(unsigned char flag);

/* ADDRESS: GOLD 0x005116e0 */

void __cdecl fcn_005116e0(void)
{
	fcn_00438e60(g_67a370, 0, 0xc0, (void*) 0x511630);
	if (g_6f1c28 != 0) {
		fcn_00454560(g_6f1c28);
		g_6f1c28 = fcn_00454c00(0, 0x40, 8, 7);
	}
	UpdateSceneLighting(1);
}
