


extern int g_7746d8;
extern int g_7746a0;
extern int g_14b57fc;
extern int g_14b55f0;
extern char g_6a99a8[];
extern char g_6a998c[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_RunFriedhofUpgradeWorkerDialog(int);
void __cdecl fcn_0058dbe0(int);

void __cdecl fcn_00590330(int a)
{
	int x;
	int y;

	x = 0;
	y = 0;
	fcn_005338a0();
	while (fcn_005373e0(fcn_00590330, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			x = RegisterStatusText(g_6a99a8, g_14b57fc, 0x28);
			y = RegisterStatusText(g_6a998c, g_14b55f0, 0x13);
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == x) {
				d2_RunFriedhofUpgradeWorkerDialog(a);
			}
			else if (g_7746a0 == y) {
				fcn_0058dbe0(a);
			}
		}
	}
}
