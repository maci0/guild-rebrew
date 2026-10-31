extern int g_100f1e8;
extern int g_100f1ec;
extern int g_67d8cc;
extern short g_7725c4;

void* __cdecl d2_GetResourceData(int resource_id);
void __cdecl fcn_0047a2b0(int h);
int __cdecl fcn_0047a200(short x, short y, void* img, int a4);

/* ADDRESS: GOLDTL 0x00473a90 */
void __cdecl d2_SetOverlayAnimation(int unused_arg, int resource_id)
{
	if (resource_id) {
		if (g_67d8cc != -1) {
			fcn_0047a2b0(g_67d8cc);
			g_67d8cc = -1;
		}
		g_67d8cc = fcn_0047a200((short) g_100f1e8, (short) g_100f1ec, d2_GetResourceData(resource_id), 0);
	} else {
		if (g_67d8cc != -1) {
			fcn_0047a2b0(g_67d8cc);
			g_67d8cc = -1;
		}
		g_7725c4 = 0;
	}
}
