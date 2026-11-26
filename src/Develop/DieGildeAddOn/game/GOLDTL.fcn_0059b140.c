


extern int g_7746d8;
extern int g_7746a0;
extern int g_14a5548;
extern int g_14ad118;
extern char g_6aa370[];
extern char g_6aa35c[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl fcn_005b7880(int, char*);
void __cdecl fcn_005c72f0(int);

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
				fcn_005b7880(a, g_6aa370);
			}
			else if (g_7746a0 == y) {
				fcn_005c72f0(a);
			}
		}
	}
}
