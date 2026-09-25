// FUNCTION: GOLDTL 0x005a91b0
// SIZE: 264

extern int g_14ad250;
extern int g_14ad260;
extern int g_14a5550;
extern int g_774800;
extern char g_14cf950;
extern int g_7746a0;

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_0057ec70(int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_004fc490(void);
void __cdecl fcn_005a8e20(void);
void __cdecl fcn_005ce0f0(void);
void __cdecl fcn_005cde30(void);

void __cdecl fcn_005a91b0(void)
{
	int kauf;
	int tages;
	int amt;

	fcn_005338a0();
	while (fcn_005373e0((void*) fcn_005a91b0, 0x67fff) != 0) {
		if (fcn_0057ec70(0x200) == 1) {
			kauf = fcn_005338d0("contact_GEB_KAUFEN", g_14ad250, 0x10);
		} else {
			kauf = 0;
		}
		if (fcn_0057ec70(0x400) == 1) {
			tages = fcn_005338d0("contact_TAGESORDNUNG", g_14ad260, 0x16);
		} else {
			tages = 0;
		}
		if (fcn_0057ec70(0x800) == 1) {
			amt = fcn_005338d0("contact_AMT_INFO", g_14a5550, 0x16);
		} else {
			amt = 0;
		}
		if (g_774800 != 0 && g_14cf950 == 0x14) {
			fcn_004fc490();
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == kauf) {
				fcn_005a8e20();
			} else if (g_7746a0 == tages) {
				fcn_005ce0f0();
			} else if (g_7746a0 == amt) {
				fcn_005cde30();
			}
		}
	}
}
