// FUNCTION: GOLDTL 0x4c4940
// SIZE: 95

extern int g_14cbca0;
extern char* g_14cbca4;
extern int g_772e80;
extern char g_1005780[];

void __cdecl fcn_004210a0(void);
int __cdecl fcn_004c49f0(char*);

int __cdecl fcn_004c4940(void)
{
	if (g_14cbca0 == -1) {
		return 0;
	}
	if (g_14cbca4 != 0) {
		fcn_004210a0();
		if (g_14cbca4 != 0) {
			return 0;
		}
	}
	do {
		g_772e80++;
		if (fcn_004c49f0(g_1005780) != 0) {
			return 1;
		}
		g_14cbca4 = g_1005780;
		fcn_004210a0();
	} while (g_14cbca4 == 0);
	return 0;
}
