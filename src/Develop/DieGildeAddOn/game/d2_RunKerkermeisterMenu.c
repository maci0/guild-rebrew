extern char g_14ab9e0[];
extern char sv_ClickedObjekt[];
extern void __cdecl d2_ClearStatusTextSlots(void);
extern int __cdecl RegisterStatusText(char* name, int a, int b);
extern int __cdecl main_RunFrameLoop(int fn, int delay);
extern void __cdecl d2_RunKerkermeisterBribeDialog(char* obj);

#define SOUND_FLAG (*(unsigned char*) (0x7f4e51 + *(unsigned short*) 0x774970 * 0x21c))

/* ADDRESS: GOLDTL 0x005ad260 */
/* ADDRESS: GOLDDE 0x00591d70 */
void __cdecl d2_RunKerkermeisterMenu(char* obj)
{
	int handle;
	int wait;

	handle = 0;
	d2_ClearStatusTextSlots();
	wait = SOUND_FLAG > 0 ? 0x677ff : 0x67fff;
	if (main_RunFrameLoop((int) d2_RunKerkermeisterMenu, wait) == 0)
		return;
	do {
		if (SOUND_FLAG > 0)
			handle = RegisterStatusText("contact_BESTECHEN", *(int*) &g_14ab9e0, 0x10);
		if (SOUND_FLAG > 0 && *(int*) &sv_ClickedObjekt != 0 &&
		    *(unsigned short*) (obj + 0x27) != 0xffff && *(int*) &sv_ClickedObjekt == handle)
			d2_RunKerkermeisterBribeDialog(obj);
		wait = SOUND_FLAG > 0 ? 0x677ff : 0x67fff;
	} while (main_RunFrameLoop((int) d2_RunKerkermeisterMenu, wait) != 0);
}
