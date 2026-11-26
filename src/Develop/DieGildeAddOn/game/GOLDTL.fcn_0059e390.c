


extern int g_7746a0;
extern int g_14ad188;
extern int g_14ad1a8;
extern char g_6aa5f0[];
extern char g_6aa5e8[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d3_UpdateBuildingInteriorState(void);
void __cdecl d2_OpenShopTradePanel(int);
void __cdecl d2_OpenLagerTradeMode2(int);

void __cdecl d2_RunKontorTradeHud(int a)
{
	int x;
	int y;

	fcn_005338a0();
	while (main_RunFrameLoop(d2_RunKontorTradeHud, 0x67fff) != 0) {
		x = RegisterStatusText(g_6aa5f0, g_14ad188, 0x10);
		y = RegisterStatusText(g_6aa5e8, g_14ad1a8, 0x10);
		d3_UpdateBuildingInteriorState();
		if (g_7746a0 != 0) {
			if (g_7746a0 == x) {
				d2_OpenShopTradePanel(a);
			}
			else if (g_7746a0 == y) {
				d2_OpenLagerTradeMode2(a);
			}
		}
	}
}
