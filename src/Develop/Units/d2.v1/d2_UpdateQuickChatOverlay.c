typedef struct Handler {
	void(__cdecl* fn)(void);
	int arg;
} Handler;
/* SIZE 8 */

extern Handler main_FrameHandlerStack[];
extern int g_774650;
extern volatile unsigned int gm_GameTicks;
int d2_QuickChatLastTick = 0xffffffff;
extern int g_6a2c20;
extern char str_dollar_C[];
extern char g_7e3a60[];

void __cdecl d2_RunChatConsole(void);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterForm(int, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);

/* ADDRESS: GOLDTL 0x00536b10 */
void __cdecl d2_UpdateQuickChatOverlay(void)
{
	if (main_FrameHandlerStack[g_774650].fn != d2_RunChatConsole &&
	    d2_QuickChatLastTick > gm_GameTicks - 0x23a &&
	    d2_QuickChatLastTick != -1) {
		if (g_6a2c20 == -1) {
			g_6a2c20 = d2_LoadForm(0, 0, "misc\\quickchat");
			d2_CenterForm(g_6a2c20, 3);
			if (g_6a2c20 == -1) {
				return;
			}
		}
		d2_SetForm(g_6a2c20, 0);
		io_AppendText((int) str_dollar_C);
		io_AppendText((int) g_7e3a60);
		return;
	}
	if (g_6a2c20 == -1) {
		return;
	}
	d2_DestroyForm(g_6a2c20);
	g_6a2c20 = -1;
}
