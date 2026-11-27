


extern int g_14ad250;
extern int g_14ad260;
extern int g_14a5550;
extern int g_774800;
extern char g_14cf950;
extern int g_7746a0;

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl d2_IsTutorialActionAllowed(int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_ShowTaxStatistics(void);
void __cdecl d2_OpenRathausGebInfo(void);
void __cdecl d2_OpenTagesordnungDialog(void);
void __cdecl d2_RunAmtCandidatesMenu(void);

void __cdecl d2_RunRathausMenu(void)
{
	int kauf;
	int tages;
	int amt;

	fcn_005338a0();
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
		if (g_774800 != 0 && g_14cf950 == 0x14) {
			d2_ShowTaxStatistics();
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == kauf) {
				d2_OpenRathausGebInfo();
			} else if (g_7746a0 == tages) {
				d2_OpenTagesordnungDialog();
			} else if (g_7746a0 == amt) {
				d2_RunAmtCandidatesMenu();
			}
		}
	}
}
