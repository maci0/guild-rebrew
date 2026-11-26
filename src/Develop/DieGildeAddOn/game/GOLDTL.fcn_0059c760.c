


extern int g_7746d8;
extern int g_7746a0;
extern int g_14ad230;
extern int g_14ad208;
extern char g_6aa39c[];
extern char g_6aa38c[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_ShowProductionDialog(int);
void __cdecl d2_RunProductionTradeDialog(int);

void __cdecl d2_RunMineInteriorHud(int a)
{
	int x;
	int y;

	x = 0;
	y = 0;
	fcn_005338a0();
	while (main_RunFrameLoop(d2_RunMineInteriorHud, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			x = RegisterStatusText(g_6aa39c, g_14ad230, 0x16);
			y = RegisterStatusText(g_6aa38c, g_14ad208, 0xa);
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == x) {
				d2_ShowProductionDialog(a);
			}
			else if (g_7746a0 == y) {
				d2_RunProductionTradeDialog(a);
			}
		}
	}
}
