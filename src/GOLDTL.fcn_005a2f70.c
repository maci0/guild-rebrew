// FUNCTION: GOLDTL 0x005a2f70
// SIZE: 331

extern int g_7746d8;
extern int g_14ad290;
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

void __cdecl fcn_005a2f70(char* e)
{
	int prod;
	int lager;
	int transport;
	int meister;
	int personal;

	lager = 0;
	prod = 0;
	transport = 0;
	meister = 0;
	personal = 0;
	fcn_005338a0();
	while (fcn_005373e0((void*) fcn_005a2f70, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			prod = fcn_005338d0("contact_PRODUKTION_BRAUEN", g_14ad290, 0x2d);
		}
		if (g_7746d8 & 0x400) {
			meister = fcn_005338d0("ob_MEISTERBRIEF", g_14a7d28, 0x16);
			personal = fcn_005338d0("ob_PERSONALBUCH", g_14a7b50, 0xc);
			transport = fcn_005338d0("contact_TRANSPORT", g_14ad100, 0x15);
			lager = fcn_005338d0("contact_LAGER", g_14ad0f0, 0xe);
		}
		fcn_00597ec0(e);
		if (g_7746a0 != 0) {
			if (g_7746a0 == personal) {
				fcn_005b6300(e, "ob_PERSONALBUCH");
			} else if (g_7746a0 == lager) {
				fcn_005be140(e, *(int*) (e + 0x5d));
			} else if (g_7746a0 == meister) {
				fcn_005cf560(e);
			} else if (g_7746a0 == prod) {
				fcn_005944d0(e);
			} else if (g_7746a0 == transport) {
				fcn_005ba8e0(e);
			}
		}
	}
}
