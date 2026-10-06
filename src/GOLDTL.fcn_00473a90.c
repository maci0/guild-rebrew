extern int g_100f1e8;
extern int g_100f1ec;
extern int g_67d8cc;
extern short g_7725c4;

void* __cdecl fcn_00466190(int idx);
void __cdecl fcn_0047a2b0(int h);
int __cdecl fcn_0047a200(short x, short y, void* img, int a4);

// FUNCTION: GOLD 0x00476f70
// FUNCTION: GOLDTL 0x473a90
void __cdecl fcn_00473a90(int a1, int idx)
{
	if (idx) {
		if (g_67d8cc != -1) {
			fcn_0047a2b0(g_67d8cc);
			g_67d8cc = -1;
		}
		g_67d8cc = fcn_0047a200((short) g_100f1e8, (short) g_100f1ec, fcn_00466190(idx), 0);
	} else {
		if (g_67d8cc != -1) {
			fcn_0047a2b0(g_67d8cc);
			g_67d8cc = -1;
		}
		g_7725c4 = 0;
	}
}
