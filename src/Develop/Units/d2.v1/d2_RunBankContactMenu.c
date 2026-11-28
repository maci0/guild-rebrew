extern char g_14ad1b0[];
extern char d2_SelectedEntityUiFlags[];
extern char g_14a7d28[];
extern char sv_ClickedObjekt[];
void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void* p, int n);
char* __cdecl RegisterStatusText(char* name, int id, int len);
void __cdecl d2_OpenMeisterbriefDialog(char* obj);
void __cdecl d2_SelectWealthOverviewTarget(char* obj);
void __cdecl d2_ShowMoneyExchangeDialog(char* obj);
void __cdecl d2_ShowLoanDialog(char* obj);
void __cdecl d2_RunGeldleiheWechselDialog(char* obj);
void __cdecl d2_RunKreditGeberDialog(char* obj);

/* ADDRESS: GOLDTL 0x005a7200 */
/* ADDRESS: GOLDDE 0x0058bf10 */
void __cdecl d2_RunBankContactMenu(char* subject)
{
	char* s1;
	char* s2;
	char* s3;
	char* s4;
	char* obj;

	s3 = 0;
	s4 = 0;
	d2_ClearStatusTextSlots();
	if (!main_RunFrameLoop((void*) d2_RunBankContactMenu, 0x67fff)) {
		return;
	}
	do {
		s1 = RegisterStatusText("contact_GELDWECHSEL", *(int*) ((int) &g_14a7d28 + 0x39c8), 0x10);
		s2 = RegisterStatusText("contact_KREDITE", *(int*) ((int) &g_14a7d28 + 0x3918), 0x10);
		if (*(int*) &d2_SelectedEntityUiFlags & 0x200) {
			s3 = RegisterStatusText("contact_MEISTERBRIEF", *(int*) &g_14a7d28, 0x16);
			s4 = RegisterStatusText("contact_VERMOEGENSUEBERSICHT", *(int*) &g_14ad1b0, 0x16);
		}
		obj = *(char**) &sv_ClickedObjekt;
		if (obj) {
			if (obj == s3) {
				d2_OpenMeisterbriefDialog(subject);
				obj = *(char**) &sv_ClickedObjekt;
			} else if (obj == s4) {
				d2_SelectWealthOverviewTarget(subject);
				obj = *(char**) &sv_ClickedObjekt;
			}
			if (obj) {
				if (*(unsigned short*) (subject + 0x27) == *(unsigned short*) ((int) &d2_SelectedEntityUiFlags + 0x298)) {
					if (obj == s1) {
						d2_RunGeldleiheWechselDialog(subject);
					} else if (obj == s2) {
						d2_RunKreditGeberDialog(subject);
					}
				} else {
					if (obj == s1) {
						d2_ShowMoneyExchangeDialog(subject);
					} else if (obj == s2) {
						d2_ShowLoanDialog(subject);
					}
				}
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunBankContactMenu, 0x67fff));
}
