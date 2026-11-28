


extern int g_14ad318;
extern int g_14ad2e0;
extern int g_14ab018;
extern int g_14aaf00;
extern int g_14ad2f0;
extern int g_14b5e70;
extern int sv_ClickedObjekt;
extern int g_774808;
extern char io_LastKeyScancode;

#ifdef REBREW_GOLD
#define fcn_005c0020 fcn_005b46e0
#endif

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl d2_IsTutorialActionAllowed(int);
int __cdecl d2_IsTutorialInactive(void);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_RunTalenteDialog(char*, int, int);
void __cdecl fcn_005c0020(char*);
void __cdecl d2_RunMeisterpruefungDialog(char*);
void __cdecl d2_OpenSpionageTargetPicker(char*);
void __cdecl d2_ShowWeinkellerDialog(char*);
void __cdecl d2_ShowGeliebteDialog(char*);

/* ADDRESS: GOLDDE 0x00585640 */
void __cdecl d2_RunCharacterActionsHud(char* e, int mode)
{
	int handwerk;
	int suicide;
	int verhandeln;
	int beweis;
	int spionage;
	int meister;

	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop((void*) d2_RunCharacterActionsHud, 0x67fff) != 0) {
		if (d2_IsTutorialActionAllowed(8) == 1) {
			verhandeln = RegisterStatusText("contact_VERHANDELN", g_14ad318, 0xc);
			handwerk = RegisterStatusText("contact_HANDWERKSKUNST", g_14ad2e0, 0xc);
		} else {
			verhandeln = 0;
			handwerk = 0;
		}
		if (d2_IsTutorialInactive() == 1) {
			beweis = RegisterStatusText("contact_BEWEISBUCH", g_14ab018, 0xc);
			meister = RegisterStatusText("contact_MEISTERPRUEFUNG", g_14aaf00, 0x17);
			spionage = RegisterStatusText("contact_SPIONAGE", g_14ad2f0, 0xc);
			suicide = RegisterStatusText("contact_SELBSTMORD", g_14b5e70, 0x24);
		} else {
			beweis = 0;
			meister = 0;
			spionage = 0;
		}
		if (sv_ClickedObjekt != 0) {
			if (sv_ClickedObjekt == verhandeln) {
				d2_RunTalenteDialog(e, mode, 0);
			} else if (sv_ClickedObjekt == handwerk) {
				d2_RunTalenteDialog(e, mode, 1);
			} else if (sv_ClickedObjekt == beweis) {
				fcn_005c0020(e);
			} else if (sv_ClickedObjekt == spionage) {
				d2_RunMeisterpruefungDialog(e);
			} else if (sv_ClickedObjekt == meister) {
				d2_OpenSpionageTargetPicker(e);
			} else if (sv_ClickedObjekt == suicide) {
				d2_ShowWeinkellerDialog(e);
			}
		} else if (g_774808 != 0 && io_LastKeyScancode == 0x2d) {
			d2_ShowGeliebteDialog(e);
		}
	}
}
