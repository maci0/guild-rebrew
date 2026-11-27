


extern int g_7746d8;
extern int g_7746a0;
extern int g_14b57fc;
extern int g_14b55f0;
extern char g_6a99a8[];
extern char g_6a998c[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_RunFriedhofUpgradeWorkerDialog(int);
void __cdecl d2_OpenFriedhofFogDialog(int);

void __cdecl d2_RunFriedhofInteriorHud(int a)
{
	int x;
	int y;

	x = 0;
	y = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunFriedhofInteriorHud, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			x = RegisterStatusText(g_6a99a8, g_14b57fc, 0x28);
			y = RegisterStatusText(g_6a998c, g_14b55f0, 0x13);
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == x) {
				d2_RunFriedhofUpgradeWorkerDialog(a);
			}
			else if (g_7746a0 == y) {
				d2_OpenFriedhofFogDialog(a);
			}
		}
	}
}
