// FUNCTION: GOLD 0x005656b0
// SIZE: 232
// FUNCTION: GOLDTL 0x0056da20
// SIZE: 232

// SIZE 0x188
typedef struct {
	int a[24];
	int b[24];
	int pad[2];
	int c[24];
	int d[24];
} Tabs;

extern Tabs g_7e43a8;
extern int g_7f4c04;

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned short __cdecl fcn_0042e410(int n);
void __cdecl fcn_0050ff70(char* o, int delta);
void __cdecl fcn_00546190(char* p);

void __cdecl fcn_0056da20(char* p)
{
	int i;
	char* e;
	int d;

	switch (*(int*) (p + 0x70)) {
	case 0:
		for (i = (g_7f4c04 & 0xffff) + 1; i < (g_7f4c04 & 0xffff) + 4; i++) {
			g_7e43a8.a[i] = 1000;
			g_7e43a8.b[i] = 3;
		}
		*(short*) (p + 0x56) = (short) (g_7f4c04 + 2);
		*(int*) (p + 0x58) = 0;
		*(int*) (p + 0x70) += 1;
		return;
	case 1:
		if ((p[0x78] & 2) != 0 && p[0xec] != 0) {
			for (i = 0; i < 16; i++) {
				if (((int*) (p + 0xac))[i] != -1) {
					e = gm_StartFilteredEntitySearch(1, 1, ((int*) (p + 0xac))[i]);
					if (e != 0) {
						d = fcn_0042e410(5) + 5;
						fcn_0050ff70(e, -d);
					}
				}
			}
			p[0xec] = 0;
		}
		fcn_00546190(p);
		return;
	case -1:
	case -2:
		fcn_00546190(p);
		return;
	}
}
