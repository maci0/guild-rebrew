// FUNCTION: GOLD 0x586b00
// SIZE: 611
// FUNCTION: GOLDTL 0x58f0a0
// SIZE: 611

extern int g_7746d8;
extern int g_7746a0;
extern int g_774800;
extern unsigned char g_14cf950;
extern int g_14b55a0;
extern int g_14b5570;
extern int g_14b57bc;
extern int g_14b5794;
extern int g_14b57e0;
extern int g_14b56f0;
extern int g_14b5730;
extern int g_14ad100;
extern int g_14b5734;

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005338d0(char*, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00590500(int);
void __cdecl fcn_0058f020(int);
void __cdecl fcn_0058f6a0(int);
void __cdecl fcn_0058f310(int);
void __cdecl fcn_0058d5f0(int);
void __cdecl fcn_0058fb60(int);
void __cdecl fcn_0058fba0(int);
void __cdecl fcn_0058fbd0(int);
void __cdecl fcn_0058fa20(int);
void __cdecl fcn_005ba8e0(int);
void __cdecl fcn_0058fa40(int);
void __cdecl fcn_0058dbe0(int);
void __cdecl fcn_0059a0e0(void);

void __cdecl fcn_0058f0a0(int arg)
{
	int v4;
	int v5;
	int v6;
	int v7;
	int v8;
	int v1;
	int v2;
	int v3;
	int v9;

	v1 = 0;
	v2 = 0;
	v7 = 0;
	v3 = 0;
	v5 = 0;
	v4 = 0;
	v6 = 0;
	v8 = 0;
	fcn_005338a0();
	while (fcn_005373e0(fcn_0058f0a0, 0x67fff) != 0) {
		fcn_00590500(arg);
		if ((g_7746d8 & 0x200) != 0) {
			v1 = fcn_005338d0("contact_ALTERN_LASSEN", g_14b55a0, 0x2f);
			v2 = fcn_005338d0("contact_HEIMSUCHUNG", g_14b5570, 0x29);
			v3 = fcn_005338d0("contact_ZUTATEN_SUCHEN", g_14b57bc, 0x13);
			v4 = fcn_005338d0("contact_GRAEBER_PFLEGEN", g_14b5794, 0x2a);
			v5 = fcn_005338d0("contact_GEHILFEN_ERSCHAFFEN", g_14b57e0, 0x28);
			v6 = fcn_005338d0("contact_VERSICHERUNG", g_14b56f0, 0x2b);
			v7 = fcn_005338d0("contact_LIEGEPLAN", g_14b5730, 0x13);
			v8 = fcn_005338d0("contact_TRANSPORT", g_14ad100, 0x15);
		}
		v9 = fcn_005338d0("contact_GRAB_MIETEN", g_14b5734, 0x16);
		if (g_7746a0 != 0) {
			if ((g_7746d8 & 0x200) != 0) {
				fcn_0058f020(arg);
				if (g_7746a0 == v1) {
					fcn_0058f6a0(arg);
				} else if (g_7746a0 == v2) {
					fcn_0058f310(arg);
				} else if (g_7746a0 == v3) {
					fcn_0058d5f0(arg);
				} else if (g_7746a0 == v4) {
					fcn_0058fb60(arg);
				} else if (g_7746a0 == v5) {
					fcn_0058fba0(arg);
				} else if (g_7746a0 == v6) {
					fcn_0058fbd0(arg);
				} else if (g_7746a0 == v7) {
					fcn_0058fa20(arg);
				} else if (g_7746a0 == v8) {
					fcn_005ba8e0(arg);
				}
			}
			if ((g_7746d8 & 0x80) != 0 && g_7746a0 == v9) {
				fcn_0058fa40(arg);
			}
		} else if (g_774800 != 0) {
			if (g_14cf950 == 0x1e) {
				fcn_0058f6a0(arg);
			} else if (g_14cf950 == 0x2f) {
				fcn_0058fbd0(arg);
			} else if (g_14cf950 == 0x22) {
				fcn_0058dbe0(arg);
			} else if (g_14cf950 == 0x23) {
				fcn_0058f310(arg);
			} else if (g_14cf950 == 0x19) {
				fcn_0058fb60(arg);
			} else if (g_14cf950 == 0x16) {
				fcn_0058fa40(arg);
			} else if (g_14cf950 == 0x11) {
				fcn_0058fba0(arg);
			}
		}
		fcn_0059a0e0();
	}
}
