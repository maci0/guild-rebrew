// FUNCTION: GOLD 0x00577cc0
// FUNCTION: GOLDTL 0x00580290

extern int* g_665f08;
extern unsigned char** g_7749e4;
extern int g_100f1dc;
extern int g_67d370;
extern char g_14cf950;

int __cdecl fcn_00423460(int);
void __cdecl fcn_004237f0(int, int);

int __cdecl fcn_00580290(void)
{
	int o;
	unsigned char* p;

	o = g_665f08[7];
	if (o == 0) {
		return -4;
	}
	if (*(int*) (o + 0x74) == 0) {
		return -4;
	}
	p = *g_7749e4;
	if (p != 0 && *p == 0x87) {
		if (g_100f1dc != -1) {
			if (g_67d370 == g_665f08[8]) {
				if (g_665f08[5] != 0) {
					if (fcn_00423460(g_665f08[5]) != 0) {
						fcn_004237f0(g_665f08[5], 0);
					}
					g_665f08[5] = 0;
				}
				return 1;
			}
		}
		else if (g_14cf950 == 0x1c) {
			if (g_665f08[5] != 0) {
				if (fcn_00423460(g_665f08[5]) != 0) {
					fcn_004237f0(g_665f08[5], 0);
				}
				g_665f08[5] = 0;
			}
			return 1;
		}
	}
	return 0;
}
