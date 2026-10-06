// FUNCTION: GOLD 0x005a3810
// FUNCTION: GOLDTL 0x005acb30

extern int g_7746d8;
extern int g_14ad1d8;
extern int g_14ad0f0;
extern int g_14ad100;
extern int g_14a7d28;
extern int g_14a7b50;
extern int g_7746a0;

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_00597ec0(char*);
void __cdecl fcn_005944d0(char*);
void __cdecl fcn_005ba8e0(char*);
void __cdecl fcn_005b6300(char*, char*);
void __cdecl fcn_005be140(char*, int);
void __cdecl fcn_005cf560(char*);

void __cdecl fcn_005acb30(char* e)
{
	int meister;
	int lager;
	int prod;
	int personal;
	int transport;

	meister = 0;
	lager = 0;
	prod = 0;
	personal = 0;
	transport = 0;
	fcn_005338a0();
	while (fcn_005373e0((void*) fcn_005acb30, 0x67fff) != 0) {
		fcn_00597ec0(e);
		if (g_7746d8 & 0x200) {
			prod = fcn_005338d0("contact_PRODUKTION_SCHREIBEN", g_14ad1d8, 0x13);
			lager = fcn_005338d0("contact_LAGER", g_14ad0f0, 0xe);
			transport = fcn_005338d0("contact_TRANSPORT", g_14ad100, 0x15);
			personal = fcn_005338d0("ob_PERSONALBUCH", g_14a7b50, 0xc);
			meister = fcn_005338d0("ob_MEISTERBRIEF", g_14a7d28, 0xc);
		}
		if (g_7746a0 != 0 && (g_7746d8 & 0x200)) {
			if (g_7746a0 == personal) {
				fcn_005b6300(e, "ob_PERSONALBUCH");
			} else if (g_7746a0 == lager) {
				fcn_005be140(e, *(int*) (e + 0x5d));
			} else if (g_7746a0 == prod) {
				fcn_005944d0(e);
			} else if (g_7746a0 == transport) {
				fcn_005ba8e0(e);
			} else if (g_7746a0 == meister) {
				fcn_005cf560(e);
			}
		}
	}
}
