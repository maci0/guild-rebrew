


extern int g_7746d8;
extern int g_7746a0;
extern int g_774800;
extern char g_14cf950;
extern int g_14b55a0;
extern int g_14b5570;
extern int g_14b57bc;
extern int g_14b5794;
extern int g_14b57e0;
extern int g_14b56f0;
extern int g_14b5730;
extern int g_14ad100;
extern int g_14b5734;

void __cdecl fcn_005338a0(void);
int __cdecl RegisterStatusText(char*, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d3_TriggerFriedhofChatScript(int);
void __cdecl fcn_0058f020(int);
void __cdecl fcn_0058f6a0(int);
void __cdecl d2_ShowHauntingDialog(int);
void __cdecl fcn_0058d5f0(int);
void __cdecl d2_StartGrabpflege(int);
void __cdecl fcn_0058fba0(int);
void __cdecl fcn_0058fbd0(int);
void __cdecl fcn_0058fa20(int);
void __cdecl d2_OpenTransportPanel(int);
void __cdecl fcn_0058fa40(int);
void __cdecl fcn_0058dbe0(int);
void __cdecl d3_UpdateBuildingInteriorState(void);

void __cdecl d2_RunFriedhofActions(int arg)
{
	int graveCareAction;
	int createHelperAction;
	int insuranceAction;
	int burialPlanAction;
	int transportAction;
	int ageAction;
	int hauntAction;
	int ingredientAction;
	int rentGraveAction;

	ageAction = 0;
	hauntAction = 0;
	burialPlanAction = 0;
	ingredientAction = 0;
	createHelperAction = 0;
	graveCareAction = 0;
	insuranceAction = 0;
	transportAction = 0;
	fcn_005338a0();
	while (main_RunFrameLoop(d2_RunFriedhofActions, 0x67fff) != 0) {
		d3_TriggerFriedhofChatScript(arg);
		if ((g_7746d8 & 0x200) != 0) {
			ageAction = RegisterStatusText("contact_ALTERN_LASSEN", g_14b55a0, 0x2f);
			hauntAction = RegisterStatusText("contact_HEIMSUCHUNG", g_14b5570, 0x29);
			ingredientAction = RegisterStatusText("contact_ZUTATEN_SUCHEN", g_14b57bc, 0x13);
			graveCareAction = RegisterStatusText("contact_GRAEBER_PFLEGEN", g_14b5794, 0x2a);
			createHelperAction = RegisterStatusText("contact_GEHILFEN_ERSCHAFFEN", g_14b57e0, 0x28);
			insuranceAction = RegisterStatusText("contact_VERSICHERUNG", g_14b56f0, 0x2b);
			burialPlanAction = RegisterStatusText("contact_LIEGEPLAN", g_14b5730, 0x13);
			transportAction = RegisterStatusText("contact_TRANSPORT", g_14ad100, 0x15);
		}
		rentGraveAction = RegisterStatusText("contact_GRAB_MIETEN", g_14b5734, 0x16);
		if (g_7746a0 != 0) {
			if ((g_7746d8 & 0x200) != 0) {
				fcn_0058f020(arg);
				if (g_7746a0 == ageAction) {
					fcn_0058f6a0(arg);
				} else if (g_7746a0 == hauntAction) {
					d2_ShowHauntingDialog(arg);
				} else if (g_7746a0 == ingredientAction) {
					fcn_0058d5f0(arg);
				} else if (g_7746a0 == graveCareAction) {
					d2_StartGrabpflege(arg);
				} else if (g_7746a0 == createHelperAction) {
					fcn_0058fba0(arg);
				} else if (g_7746a0 == insuranceAction) {
					fcn_0058fbd0(arg);
				} else if (g_7746a0 == burialPlanAction) {
					fcn_0058fa20(arg);
				} else if (g_7746a0 == transportAction) {
					d2_OpenTransportPanel(arg);
				}
			}
			if ((g_7746d8 & 0x80) != 0 && g_7746a0 == rentGraveAction) {
				fcn_0058fa40(arg);
			}
		} else if (g_774800 != 0) {
			if ((*(unsigned char*)&g_14cf950) == 0x1e) {
				fcn_0058f6a0(arg);
			} else if ((*(unsigned char*)&g_14cf950) == 0x2f) {
				fcn_0058fbd0(arg);
			} else if ((*(unsigned char*)&g_14cf950) == 0x22) {
				fcn_0058dbe0(arg);
			} else if ((*(unsigned char*)&g_14cf950) == 0x23) {
				d2_ShowHauntingDialog(arg);
			} else if ((*(unsigned char*)&g_14cf950) == 0x19) {
				d2_StartGrabpflege(arg);
			} else if ((*(unsigned char*)&g_14cf950) == 0x16) {
				fcn_0058fa40(arg);
			} else if ((*(unsigned char*)&g_14cf950) == 0x11) {
				fcn_0058fba0(arg);
			}
		}
		d3_UpdateBuildingInteriorState();
	}
}
