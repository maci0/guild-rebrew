extern unsigned char io_LastKeyScancode;
extern int g_77480c;

extern int __cdecl gm_DispatchDebugSubsystemKeys(void);
extern int __cdecl gm_DispatchDebugActionKeys(void);
extern int __cdecl d2_DispatchDebugHotkey(void);

/* Mode byte g_14cf950 selects O/P/R; every other value re-dispatches the
 * cached mode in g_77480c. The cached dispatch is the switch default: that
 * places the case bodies before it, as the reference does. */
/* ADDRESS: GOLDTL 0x005365d0 */
int __cdecl gm_DispatchDebugMode(void)
{
	switch (io_LastKeyScancode) {
	case 0x4f:
		g_77480c = 1;
		return gm_DispatchDebugActionKeys();
	case 0x50:
		g_77480c = 2;
		return d2_DispatchDebugHotkey();
	case 0x52:
		g_77480c = 0;
		return gm_DispatchDebugSubsystemKeys();
	default:
		if (g_77480c == 0) {
			return gm_DispatchDebugSubsystemKeys();
		}
		if (g_77480c == 1) {
			return gm_DispatchDebugActionKeys();
		}
		if (g_77480c == 2) {
			return d2_DispatchDebugHotkey();
		}
		return g_77480c;
	}
}
