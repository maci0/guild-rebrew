// FUNCTION: GOLDTL 0x0059e430
// SIZE: 448

extern int g_7746d8;
extern int g_14ad268;
extern int g_14a7d28;
extern int g_14ad0f0;
extern int g_14ad100;
extern int g_14a7b50;
extern int g_7746a0;

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_0057ec70(int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005be140(char*, int);
void __cdecl fcn_005944d0(char*);
void __cdecl fcn_005ba8e0(char*);
void __cdecl fcn_005b6300(char*, char*);
void __cdecl fcn_005cf560(char*);
void __cdecl fcn_00597ec0(char*);

void __cdecl fcn_0059e430(char* e)
{
	int lager;
	int prod;
	int transport;
	int meister;
	int personal;

	lager = 0;
	prod = 0;
	transport = 0;
	meister = 0;
	personal = 0;
	fcn_005338a0();
	while (fcn_005373e0((void*) fcn_0059e430, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			if (fcn_0057ec70(0x20) == 1) {
				prod = fcn_005338d0("contact_PRODUKTION_SCHMIEDEN", g_14ad268, 0x13);
			} else {
				prod = 0;
			}
			if (fcn_0057ec70(0x80) == 1) {
				meister = fcn_005338d0("ob_MEISTERBRIEF", g_14a7d28, 0x16);
			} else {
				meister = 0;
			}
		}
		if (g_7746d8 & 0x400) {
			if (fcn_0057ec70(0x10) == 1) {
				lager = fcn_005338d0("contact_LAGER", g_14ad0f0, 0xe);
			} else {
				lager = 0;
			}
			if (fcn_0057ec70(0x100) == 1) {
				transport = fcn_005338d0("contact_TRANSPORT", g_14ad100, 0x15);
			} else {
				transport = 0;
			}
			if (fcn_0057ec70(0x40) == 1) {
				personal = fcn_005338d0("ob_PERSONALBUCH", g_14a7b50, 0xc);
			} else {
				personal = 0;
			}
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == lager) {
				fcn_005be140(e, *(int*) (e + 0x5d));
			} else if (g_7746a0 == prod) {
				fcn_005944d0(e);
			} else if (g_7746a0 == transport) {
				fcn_005ba8e0(e);
			} else if (g_7746a0 == personal) {
				fcn_005b6300(e, "ob_PERSONALBUCH");
			} else if (g_7746a0 == meister) {
				fcn_005cf560(e);
			}
		}
		fcn_00597ec0(e);
	}
	fcn_005338a0();
}
