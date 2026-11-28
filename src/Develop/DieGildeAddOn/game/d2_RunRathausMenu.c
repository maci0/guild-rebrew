


extern int g_14ad250;
extern int g_14ad260;
extern int g_14a5550;
extern int gm_AllEntitiesControllable;
extern char io_LastKeyScancode;
extern int sv_ClickedObjekt;

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl d2_IsTutorialActionAllowed(int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_ShowTaxStatistics(void);
void __cdecl d2_OpenRathausGebInfo(void);
void __cdecl d2_OpenTagesordnungDialog(void);
void __cdecl d2_RunAmtCandidatesMenu(void);

/* ADDRESS: GOLDDE 0x0058dcc0 */
void __cdecl d2_RunRathausMenu(void)
{
	int kauf;
	int tages;
	int amt;

	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop((void*) d2_RunRathausMenu, 0x67fff) != 0) {
		if (d2_IsTutorialActionAllowed(0x200) == 1) {
			kauf = RegisterStatusText("contact_GEB_KAUFEN", g_14ad250, 0x10);
		} else {
			kauf = 0;
		}
		if (d2_IsTutorialActionAllowed(0x400) == 1) {
			tages = RegisterStatusText("contact_TAGESORDNUNG", g_14ad260, 0x16);
		} else {
			tages = 0;
		}
		if (d2_IsTutorialActionAllowed(0x800) == 1) {
			amt = RegisterStatusText("contact_AMT_INFO", g_14a5550, 0x16);
		} else {
			amt = 0;
		}
		if (gm_AllEntitiesControllable != 0 && io_LastKeyScancode == 0x14) {
			d2_ShowTaxStatistics();
		}
		if (sv_ClickedObjekt != 0) {
			if (sv_ClickedObjekt == kauf) {
				d2_OpenRathausGebInfo();
			} else if (sv_ClickedObjekt == tages) {
				d2_OpenTagesordnungDialog();
			} else if (sv_ClickedObjekt == amt) {
				d2_RunAmtCandidatesMenu();
			}
		}
	}
}
