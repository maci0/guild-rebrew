// FUNCTION: GOLD 0x00593be0
// SIZE: 416
// FUNCTION: GOLDTL 0x0059c9a0
// SIZE: 416

extern int g_7746d8;
extern int g_14ad0f0;
extern int g_14ad288;
extern int g_14ad0e8;
extern int g_14ad100;
extern int g_14abc2c;
extern int g_14abc30;
extern int g_7746a0;
extern int g_100f1dc;
extern int g_67d370;
extern int g_6a25f0;

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_0059a0e0(void);
void __cdecl fcn_005c5990(char*, int);
void __cdecl fcn_005ba8e0(char*);
void __cdecl fcn_005be140(char*, int);
void __cdecl fcn_0059c000(char*);
void __cdecl fcn_005c5b10(char*);
void __cdecl fcn_005c79a0(char*);
void __cdecl fcn_005c5310(char*);

void __cdecl fcn_0059c9a0(char* e)
{
	int zs;
	int sp;
	int x;
	int lager;
	int holz;
	int gelage;
	int transport;

	lager = 0;
	transport = 0;
	holz = 0;
	gelage = 0;
	sp = 0;
	zs = 0;
	fcn_005338a0();
	x = *(int*) (e + 0x71);
	while (fcn_005373e0((void*) fcn_0059c9a0, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			lager = fcn_005338d0("contact_LAGER", g_14ad0f0, 0xe);
			holz = fcn_005338d0("contact_PRODUKTION_HOLZ", g_14ad288, 0x13);
			gelage = fcn_005338d0("contact_GELAGE", g_14ad0e8, 0x16);
			transport = fcn_005338d0("contact_TRANSPORT", g_14ad100, 0x15);
			zs = fcn_005338d0("ob_ZIELSCHEIBE", g_14abc2c, 0xc);
			sp = fcn_005338d0("ob_STROHPUPPE", g_14abc30, 0xc);
		}
		fcn_0059a0e0();
		fcn_005c5990(e, x);
		if (g_7746a0 != 0) {
			if (g_7746a0 == transport) {
				fcn_005ba8e0(e);
			} else if (g_7746a0 == lager) {
				fcn_005be140(e, *(int*) (e + 0x5d));
			} else if (g_7746a0 == holz) {
				fcn_0059c000(e);
			} else if (g_7746a0 == gelage) {
				fcn_005c5b10(e);
			} else if (g_7746a0 == zs) {
				fcn_005c79a0(e);
			} else if (g_7746a0 == sp) {
				fcn_005c79a0(e);
			}
		}
		if (g_100f1dc != -1 && g_67d370 == g_6a25f0) {
			fcn_005c5310(e);
		}
	}
}
