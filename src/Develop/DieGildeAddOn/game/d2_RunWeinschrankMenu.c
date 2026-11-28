extern char g_14abc4c[];
extern char sv_ClickedObjekt[];
void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(int a, int b);
int __cdecl RegisterStatusText(char* s, int a, int b);
void __cdecl d2_RunWeinkellerDialog(void);

/* ADDRESS: GOLDTL 0x005a4030 */
/* ADDRESS: GOLDDE 0x00588d40 */
void __cdecl d2_RunWeinschrankMenu(void)
{
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop((int) d2_RunWeinschrankMenu, 0x67fff) != 0) {
		int v;
		int cur;

		v = RegisterStatusText("contact_WEINSCHRANK", *(int*) &g_14abc4c, 0x16);
		cur = *(int*) &sv_ClickedObjekt;
		if (cur != 0 && cur == v) {
			d2_RunWeinkellerDialog();
		}
	}
}
