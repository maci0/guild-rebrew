// FUNCTION: GOLD 0x005a3960
// SIZE: 412
// FUNCTION: GOLDTL 0x005acc80
// SIZE: 412

extern int g_7746d8;
extern int g_14ab954;
extern int g_14ab8f4;
extern int g_14ab918;
extern int g_14ab934;
extern unsigned short g_774970;
extern int g_7746a0;
extern char g_14cf950;
extern int g_774800;

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_005ac2d0(char*);
void __cdecl fcn_005ab810(char*, int);
void __cdecl fcn_005abfd0(char*);
void __cdecl fcn_005aaf60(char*);

void __cdecl fcn_005acc80(char* e, int a2)
{
	int predigt;
	int weih;
	int beicht;
	int spende;

	beicht = 0;
	spende = 0;
	predigt = 0;
	weih = 0;
	fcn_005338a0();
	while (fcn_005373e0((void*) fcn_005acc80, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			predigt = fcn_005338d0("contact_PREDIGT", g_14ab954, 0x16);
			weih = fcn_005338d0("ob_WEIHWASSERBECKEN", g_14ab8f4, 0x16);
		}
		if (*(unsigned short*) (e + 0x27) != g_774970 && *(unsigned short*) (e + 0x27) != 0xffff) {
			if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0xf2) != 0) {
				beicht = fcn_005338d0("ob_KIRCHE_BEICHTSTUHLRAUM", g_14ab918, 0x16);
			} else {
				beicht = 0;
			}
			spende = fcn_005338d0("ob_SPENDENKAESTCHEN", g_14ab934, 0x16);
			weih = fcn_005338d0("ob_WEIHWASSERBECKEN", g_14ab8f4, 0x16);
		}
		if (g_7746a0 != 0) {
			if (g_7746d8 & 0x200) {
				if (g_7746a0 == predigt) {
					fcn_005ac2d0(e);
				} else if (g_7746a0 == weih) {
					fcn_005ab810(e, a2);
				}
			}
			if (*(unsigned short*) (e + 0x27) != g_774970) {
				if (g_7746a0 == beicht) {
					fcn_005abfd0(e);
				}
				if (g_7746a0 == spende) {
					fcn_005aaf60(e);
				}
				if (g_7746a0 == weih) {
					fcn_005ab810(e, a2);
				}
			}
		} else if (g_14cf950 == 0x30 && g_774800 != 0) {
			fcn_005abfd0(e);
		}
	}
}
