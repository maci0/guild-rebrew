


extern int sv_ClickedObjekt;
extern int g_14ad188;
extern int g_14ad1a8;
extern char g_6aa5f0[];
extern char g_6aa5e8[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d3_UpdateBuildingInteriorState(void);
void __cdecl d2_OpenShopTradePanel(int);
void __cdecl d2_OpenLagerTradeMode2(int);

/* ADDRESS: GOLDDE 0x00583220 */
void __cdecl d2_RunKontorTradeHud(int a)
{
	int x;
	int y;

	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunKontorTradeHud, 0x67fff) != 0) {
		x = RegisterStatusText(g_6aa5f0, g_14ad188, 0x10);
		y = RegisterStatusText(g_6aa5e8, g_14ad1a8, 0x10);
		d3_UpdateBuildingInteriorState();
		if (sv_ClickedObjekt != 0) {
			if (sv_ClickedObjekt == x) {
				d2_OpenShopTradePanel(a);
			}
			else if (sv_ClickedObjekt == y) {
				d2_OpenLagerTradeMode2(a);
			}
		}
	}
}
