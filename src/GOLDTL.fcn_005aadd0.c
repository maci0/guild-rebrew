// FUNCTION: GOLD 0x5a1ab0
// SIZE: 253
// FUNCTION: GOLDTL 0x005aadd0
// SIZE: 253

extern unsigned short g_774970;
extern char g_7f4ca0[];
extern int g_14abb84;
extern char* g_14a5320[];
extern int g_7746a0;

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_005aad40(void);
int __cdecl fcn_005338d0(char*, int, int);
int __cdecl fcn_004eb320(char*);
void __cdecl fcn_005a9dd0(char*);
void __cdecl fcn_005aac20(void);

void __cdecl fcn_005aadd0(char* e)
{
	int a;
	int b;
	int id;
	char lvl;

	b = 0;
	id = 0;
	lvl = g_7f4ca0[g_774970 * 540 + 0x169];
	if (lvl == 0x1e) {
		id = 0x167c;
	} else if (lvl == 0x1f || lvl == 0x21) {
		id = 0x166a;
	} else if (lvl == 0x20) {
		id = 0x1674;
	}
	fcn_005338a0();
	while (fcn_005373e0((void*) fcn_005aad40, 0x67fff) != 0) {
		a = fcn_005338d0("ob_ZUNFTKASSE", g_14abb84, 0x16);
		if (fcn_004eb320(g_7f4ca0 + g_774970 * 540) != 0 && id != 0) {
			b = fcn_005338d0("contact_ZUNFTLEVEL3", ((int*)g_14a5320)[id], 0x16);
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == a) {
				fcn_005a9dd0(e);
			} else if (g_7746a0 == b) {
				fcn_005aac20();
			}
		}
	}
}
