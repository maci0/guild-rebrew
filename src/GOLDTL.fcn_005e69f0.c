// FUNCTION: GOLD 0x005d9d80
// FUNCTION: GOLDTL 0x005e69f0

extern int g_7746d8;
extern int g_7746a0;
extern int g_14b5b94;
extern int g_14ad100;
extern int g_14ad0f8;
extern int g_14ad0f0;
extern int g_14b5ab4;
extern int g_14a7b50;
extern int g_14a7d28;

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_0058d5f0(int);
void __cdecl fcn_005ba8e0(int);
void __cdecl fcn_005944d0(int);
void __cdecl fcn_005be140(int, int);
void __cdecl fcn_005cf560(int);
void __cdecl fcn_005e6650(int);
void __cdecl fcn_005b6300(int, char*);
void __cdecl fcn_0059a0e0(void);

void __cdecl fcn_005e69f0(int a)
{
	int zig;
	int trans;
	int prod;
	int lager;
	int meister;
	int betteln;
	int personal;

	zig = 0;
	trans = 0;
	prod = 0;
	lager = 0;
	personal = 0;
	meister = 0;
	betteln = 0;
	fcn_005338a0();
	while (fcn_005373e0(fcn_005e69f0, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			zig = fcn_005338d0("contact_ZUTATEN_SUCHEN_ZIGEUNER", g_14b5b94, 0x16);
			trans = fcn_005338d0("contact_TRANSPORT", g_14ad100, 0x15);
			prod = fcn_005338d0("contact_PRODUKTION_ZIGEUNER", g_14ad0f8, 0x13);
			lager = fcn_005338d0("contact_LAGER", g_14ad0f0, 0xe);
			betteln = fcn_005338d0("contact_BETTELN", g_14b5ab4, 0x2c);
		}
		if (g_7746d8 & 0x400) {
			personal = fcn_005338d0("contact_PERSONALBUCH", g_14a7b50, 0xc);
			meister = fcn_005338d0("contact_MEISTERBRIEF", g_14a7d28, 0xc);
		}
		if (g_7746a0 != 0) {
			if (g_7746d8 & 0x200) {
				if (g_7746a0 == zig) {
					fcn_0058d5f0(a);
				} else if (g_7746a0 == trans) {
					fcn_005ba8e0(a);
				} else if (g_7746a0 == prod) {
					fcn_005944d0(a);
				} else if (g_7746a0 == lager) {
					fcn_005be140(a, 0);
				} else if (g_7746a0 == meister) {
					fcn_005cf560(a);
				} else if (g_7746a0 == betteln) {
					fcn_005e6650(a);
				}
			}
			if (g_7746a0 == personal) {
				fcn_005b6300(a, "ob_PERSONALBUCH");
			}
		}
		fcn_0059a0e0();
	}
}
