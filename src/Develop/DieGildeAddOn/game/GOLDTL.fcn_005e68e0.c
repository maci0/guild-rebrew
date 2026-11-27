

extern int g_7746a0;
extern int g_14b5a20;
extern char g_6ad4c0[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_RunBlutracheDialog(int);

/* ADDRESS: GOLD 0x5a3c70 */
void __cdecl d2_RunFortuneTellerHud(int a)
{
	int x;

	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunFortuneTellerHud, 0x67fff) != 0) {
		x = RegisterStatusText(g_6ad4c0, g_14b5a20, 0x16);
		if (g_7746a0 != 0 && g_7746a0 == x) {
			d2_RunBlutracheDialog(a);
		}
	}
}
