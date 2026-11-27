extern unsigned char g_14cf950;
extern int g_77480c;

extern int __cdecl fcn_00535bd0(void);
extern int __cdecl gm_DispatchDebugActionKeys(void);
extern int __cdecl fcn_00535ec0(void);

/* Mode byte g_14cf950 selects O/P/R; every other value re-dispatches the
 * cached mode in g_77480c. The cached dispatch is the switch default: that
 * places the case bodies before it, as the reference does. */
/* ADDRESS: GOLDTL 0x005365d0 */
int __cdecl fcn_005365d0(void)
{
	switch (g_14cf950) {
	case 0x4f:
		g_77480c = 1;
		return gm_DispatchDebugActionKeys();
	case 0x50:
		g_77480c = 2;
		return fcn_00535ec0();
	case 0x52:
		g_77480c = 0;
		return fcn_00535bd0();
	default:
		if (g_77480c == 0) {
			return fcn_00535bd0();
		}
		if (g_77480c == 1) {
			return gm_DispatchDebugActionKeys();
		}
		if (g_77480c == 2) {
			return fcn_00535ec0();
		}
		return g_77480c;
	}
}
