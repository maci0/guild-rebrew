


extern int g_7746a0;
extern int g_7746d8;
extern int g_14ab918;
extern char g_6ab07c[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_OpenBeichteDialog(int);

void __cdecl fcn_005ac250(int a)
{
	int x;

	x = 0;
	fcn_005338a0();
	while (main_RunFrameLoop(fcn_005ac250, 0x67fff) != 0) {
		if (!(g_7746d8 & 0x200)) {
			x = RegisterStatusText(g_6ab07c, g_14ab918, 0x16);
		}
		if (g_7746a0 != 0 && !(g_7746d8 & 0x200) && g_7746a0 == x) {
			d2_OpenBeichteDialog(a);
		}
	}
}
