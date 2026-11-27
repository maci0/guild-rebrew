


extern int g_7746d8;
extern int g_7746a0;
extern int g_14a5548;
extern int g_14ad118;
extern char g_6aa370[];
extern char g_6aa35c[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_RunSoeldnerbuchDialog(int, char*);
void __cdecl d2_RunEquipmentDialog(int);

void __cdecl d2_RunWacheInteriorHud(int a)
{
	int x;
	int y;

	x = 0;
	y = 0;
	fcn_005338a0();
	while (main_RunFrameLoop(d2_RunWacheInteriorHud, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			x = RegisterStatusText(g_6aa370, g_14a5548, 0xc);
			y = RegisterStatusText(g_6aa35c, g_14ad118, 0xd);
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == x) {
				d2_RunSoeldnerbuchDialog(a, g_6aa370);
			}
			else if (g_7746a0 == y) {
				d2_RunEquipmentDialog(a);
			}
		}
	}
}
