// FUNCTION: GOLD 0x00593d80
// SIZE: 468
// FUNCTION: GOLDTL 0x0059cb40
// SIZE: 468

extern int g_7746d8;
extern int g_14ad0f0;
extern int g_14ad208;
extern int g_14ad238;
extern int g_14ad0f8;
extern int g_14ad100;
extern int g_14ad0e8;
extern int g_14abc30;
extern int g_14abc2c;
extern int g_7746a0;

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_0059a0e0(void);
void __cdecl fcn_005be140(char*, int);
void __cdecl fcn_005c5b10(char*);
void __cdecl fcn_0059ba40(char*);
void __cdecl fcn_0059b260(char*);
void __cdecl fcn_005ba8e0(char*);
void __cdecl fcn_0059c000(char*);
void __cdecl fcn_005c79a0(char*);

void __cdecl fcn_0059cb40(char* e)
{
	int gelage;
	int transport;
	int prod;
	int zs;
	int sp;
	int lager;
	int abbau;
	int suchen;

	lager = 0;
	prod = 0;
	suchen = 0;
	transport = 0;
	abbau = 0;
	gelage = 0;
	sp = 0;
	zs = 0;
	fcn_005338a0();
	while (fcn_005373e0((void*) fcn_0059cb40, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			lager = fcn_005338d0("contact_LAGER", g_14ad0f0, 0xe);
			abbau = fcn_005338d0("contact_ABBAU", g_14ad208, 0xa);
			suchen = fcn_005338d0("contact_SUCHEN_STEIN", g_14ad238, 0x16);
			prod = fcn_005338d0("contact_PRODUKTION", g_14ad0f8, 0x13);
			transport = fcn_005338d0("contact_TRANSPORT", g_14ad100, 0x15);
			gelage = fcn_005338d0("contact_GELAGE", g_14ad0e8, 0x16);
			if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x35) != 0) {
				sp = fcn_005338d0("ob_STROHPUPPE", g_14abc30, 0x17);
			}
			if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x34) != 0) {
				zs = fcn_005338d0("ob_ZIELSCHEIBE", g_14abc2c, 0x17);
			}
		}
		fcn_0059a0e0();
		if (g_7746a0 != 0) {
			if (g_7746a0 == lager) {
				fcn_005be140(e, *(int*) (e + 0x5d));
			} else if (g_7746a0 == gelage) {
				fcn_005c5b10(e);
			} else if (g_7746a0 == abbau) {
				fcn_0059ba40(e);
			} else if (g_7746a0 == suchen) {
				fcn_0059b260(e);
			} else if (g_7746a0 == transport) {
				fcn_005ba8e0(e);
			} else if (g_7746a0 == prod) {
				fcn_0059c000(e);
			} else if (g_7746a0 == zs || g_7746a0 == sp) {
				fcn_005c79a0(e);
			}
		}
	}
}
