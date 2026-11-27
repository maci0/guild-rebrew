void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(int a, int b);
int __cdecl RegisterStatusText(char* s, int a, int b);
void __cdecl d2_RunWeinkellerDialog(void);

/* ADDRESS: GOLDTL 0x005a4030 */
void __cdecl d2_RunWeinschrankMenu(void)
{
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(0x5a4030, 0x67fff) != 0) {
		int v;
		int cur;

		v = RegisterStatusText("contact_WEINSCHRANK", *(int*) 0x14abc4c, 0x16);
		cur = *(int*) 0x7746a0;
		if (cur != 0 && cur == v) {
			d2_RunWeinkellerDialog();
		}
	}
}
