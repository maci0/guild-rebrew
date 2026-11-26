


extern int g_7746d8;
extern int g_7746a0;
extern int g_14b5aec;
extern int g_14b5bfc;
extern char g_6ad4ec[];
extern char g_6ad4d8[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_ShowBlutracheDialog(int);
int __cdecl fcn_005e6e00(void);

void __cdecl fcn_005e6950(int a)
{
	int x;
	int y;

	x = 0;
	fcn_005338a0();
	while (main_RunFrameLoop(fcn_005e6950, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			x = RegisterStatusText(g_6ad4ec, g_14b5aec, 0x16);
		}
		y = RegisterStatusText(g_6ad4d8, g_14b5bfc, 0x16);
		if (g_7746a0 != 0) {
			if (g_7746a0 == x) {
				d2_ShowBlutracheDialog(a);
			}
			else if (g_7746a0 == y) {
				fcn_005e6e00();
			}
		}
	}
}
