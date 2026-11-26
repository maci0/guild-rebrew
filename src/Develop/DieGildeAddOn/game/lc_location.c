extern int g_7746a0;
extern int g_14ab9d0;
extern char g_6ab158[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_RunKerkerplanDialog(int);
extern int main_LoopFlags;
extern volatile int g_6b7fc0;
extern char g_774964;
extern char g_14cf950;
extern char g_6a2e68[];
extern char g_6b5c60[];

void __cdecl fcn_00533a40(char*);
int __cdecl main_RunFrameLoop(void*, int);

/* ADDRESS: GOLD 0x5d9c70 */
/* ADDRESS: GOLDTL 0x005acf90 */
void __cdecl fcn_005acf90(int a)
{
	int x;

	fcn_005338a0();
	while (main_RunFrameLoop(fcn_005acf90, 0x67fff) != 0) {
		x = RegisterStatusText(g_6ab158, g_14ab9d0, 0x16);
		if (g_7746a0 != 0 && g_7746a0 == x) {
			d2_RunKerkerplanDialog(a);
		}
	}
}

/* ADDRESS: GOLD 0x5d7fe0 */

/* ADDRESS: GOLDTL 0x005e4c50 */
void __cdecl fcn_005e4c50(void)
{
	int flags;

	flags = (main_LoopFlags & ~0x2000) | 0x100000;
	g_6b7fc0 = 1;
	fcn_00533a40(g_6a2e68);
	(*(unsigned char*)&g_774964) = 0;
	while (main_RunFrameLoop(0, flags) != 0) {
		if (g_14cf950 == 0x39) {
			break;
		}
	}
	fcn_00533a40(g_6b5c60);
	g_6b7fc0 = 0;
	(*(unsigned char*)&g_774964) = 1;
}
