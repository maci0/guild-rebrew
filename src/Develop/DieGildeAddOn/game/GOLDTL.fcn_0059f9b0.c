


extern int g_7746a0;
extern int g_14ab0b8;
extern int g_14aadd8;
extern int g_14ab098;
extern char g_6aa78c[];
extern char g_6aa77c[];
extern char g_6aa764[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_ShowFestInvitation(int, int);
void __cdecl d2_RunTalenteDialog(int, int, int);
void __cdecl fcn_005c0a90(int);
void __cdecl fcn_00532ef0(void);

void __cdecl fcn_0059f9b0(int a1, int a2)
{
	int x;
	int y;
	int z;

	fcn_005338a0();
	while (fcn_005373e0(fcn_0059f9b0, 0x67fff) != 0) {
		x = RegisterStatusText(g_6aa78c, g_14ab0b8, 0x16);
		y = RegisterStatusText(g_6aa77c, g_14aadd8, 0xc);
		z = RegisterStatusText(g_6aa764, g_14ab098, 0xc);
		if (g_7746a0 != 0) {
			if (g_7746a0 == x) {
				d2_ShowFestInvitation(a1, a2);
			}
			else if (g_7746a0 == y) {
				d2_RunTalenteDialog(a1, a2, 3);
			}
			else if (g_7746a0 == z) {
				fcn_005c0a90(a1);
				fcn_00532ef0();
			}
		}
	}
}
