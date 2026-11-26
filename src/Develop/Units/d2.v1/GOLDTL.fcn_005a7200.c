void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void* p, int n);
char* __cdecl RegisterStatusText(char* name, int id, int len);
void __cdecl d2_OpenMeisterbriefDialog(char* obj);
void __cdecl d2_SelectWealthOverviewTarget(char* obj);
void __cdecl d2_ShowMoneyExchangeDialog(char* obj);
void __cdecl d2_ShowLoanDialog(char* obj);
void __cdecl d2_RunGeldleiheWechselDialog(char* obj);
void __cdecl fcn_005a4e00(char* obj);

/* ADDRESS: GOLDTL 0x005a7200 */
void __cdecl fcn_005a7200(char* subject)
{
	char* s1;
	char* s2;
	char* s3;
	char* s4;
	char* obj;

	s3 = 0;
	s4 = 0;
	fcn_005338a0();
	if (!main_RunFrameLoop((void*) 0x5a7200, 0x67fff)) {
		return;
	}
	do {
		s1 = RegisterStatusText((char*) 0x6aad78, *(int*) 0x14ab6f0, 0x10);
		s2 = RegisterStatusText((char*) 0x6aad68, *(int*) 0x14ab640, 0x10);
		if (*(int*) 0x7746d8 & 0x200) {
			s3 = RegisterStatusText((char*) 0x6aad50, *(int*) 0x14a7d28, 0x16);
			s4 = RegisterStatusText((char*) 0x6aad30, *(int*) 0x14ad1b0, 0x16);
		}
		obj = *(char**) 0x7746a0;
		if (obj) {
			if (obj == s3) {
				d2_OpenMeisterbriefDialog(subject);
				obj = *(char**) 0x7746a0;
			} else if (obj == s4) {
				d2_SelectWealthOverviewTarget(subject);
				obj = *(char**) 0x7746a0;
			}
			if (obj) {
				if (*(unsigned short*) (subject + 0x27) == *(unsigned short*) 0x774970) {
					if (obj == s1) {
						d2_RunGeldleiheWechselDialog(subject);
					} else if (obj == s2) {
						fcn_005a4e00(subject);
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
	} while (main_RunFrameLoop((void*) 0x5a7200, 0x67fff));
}
