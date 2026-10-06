// FUNCTION: GOLD 0x005975e0
// FUNCTION: GOLDTL 0x005a07c0

extern int g_14ad318;
extern int g_14ad2e0;
extern int g_14ab018;
extern int g_14aaf00;
extern int g_14ad2f0;
extern int g_14b5e70;
extern int g_7746a0;
extern int g_774808;
extern char g_14cf950;

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_0057ec70(int);
int __cdecl fcn_005809f0(void);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005bebe0(char*, int, int);
void __cdecl fcn_005c0020(char*);
void __cdecl fcn_005a02b0(char*);
void __cdecl fcn_005a0630(char*);
void __cdecl fcn_005a06a0(char*);
void __cdecl fcn_0059fe60(char*);

void __cdecl fcn_005a07c0(char* e, int a2)
{
	int handwerk;
	int suicide;
	int verhandeln;
	int beweis;
	int spionage;
	int meister;

	fcn_005338a0();
	while (fcn_005373e0((void*) fcn_005a07c0, 0x67fff) != 0) {
		if (fcn_0057ec70(8) == 1) {
			verhandeln = fcn_005338d0("contact_VERHANDELN", g_14ad318, 0xc);
			handwerk = fcn_005338d0("contact_HANDWERKSKUNST", g_14ad2e0, 0xc);
		} else {
			verhandeln = 0;
			handwerk = 0;
		}
		if (fcn_005809f0() == 1) {
			beweis = fcn_005338d0("contact_BEWEISBUCH", g_14ab018, 0xc);
			meister = fcn_005338d0("contact_MEISTERPRUEFUNG", g_14aaf00, 0x17);
			spionage = fcn_005338d0("contact_SPIONAGE", g_14ad2f0, 0xc);
			suicide = fcn_005338d0("contact_SELBSTMORD", g_14b5e70, 0x24);
		} else {
			beweis = 0;
			meister = 0;
			spionage = 0;
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == verhandeln) {
				fcn_005bebe0(e, a2, 0);
			} else if (g_7746a0 == handwerk) {
				fcn_005bebe0(e, a2, 1);
			} else if (g_7746a0 == beweis) {
				fcn_005c0020(e);
			} else if (g_7746a0 == spionage) {
				fcn_005a02b0(e);
			} else if (g_7746a0 == meister) {
				fcn_005a0630(e);
			} else if (g_7746a0 == suicide) {
				fcn_005a06a0(e);
			}
		} else if (g_774808 != 0 && g_14cf950 == 0x2d) {
			fcn_0059fe60(e);
		}
	}
}
