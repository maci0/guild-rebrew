extern int sv_ClickedObjekt;
extern int g_14ab9d0;
extern char g_6ab158[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_RunKerkerplanDialog(int);
extern int main_LoopFlags;
extern volatile int tb_TimerPaused;
extern char gm_InWorldHud;
extern char io_LastKeyScancode;
extern char g_6a2e68[];
extern char str_empty[];

void __cdecl d2_ShowStatusBanner(char*);
int __cdecl main_RunFrameLoop(void*, int);

/* ADDRESS: GOLD 0x5d9c70 */
/* ADDRESS: GOLDTL 0x005acf90 */
void __cdecl d2_RunKerkerplanHotspot(int a)
{
	int x;

	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunKerkerplanHotspot, 0x67fff) != 0) {
		x = RegisterStatusText(g_6ab158, g_14ab9d0, 0x16);
		if (sv_ClickedObjekt != 0 && sv_ClickedObjekt == x) {
			d2_RunKerkerplanDialog(a);
		}
	}
}

/* ADDRESS: GOLD 0x5d7fe0 */

/* ADDRESS: GOLDTL 0x005e4c50 */
void __cdecl d2_PauseGameLoop(void)
{
	int flags;

	flags = (main_LoopFlags & ~0x2000) | 0x100000;
	tb_TimerPaused = 1;
	d2_ShowStatusBanner(g_6a2e68);
	(*(unsigned char*)&gm_InWorldHud) = 0;
	while (main_RunFrameLoop(0, flags) != 0) {
		if (io_LastKeyScancode == 0x39) {
			break;
		}
	}
	d2_ShowStatusBanner(str_empty);
	tb_TimerPaused = 0;
	(*(unsigned char*)&gm_InWorldHud) = 1;
}
