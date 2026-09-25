// FUNCTION: GOLD 0x0058a120
// SIZE: 184
// FUNCTION: GOLDTL 0x00592630
// SIZE: 184

extern char g_7f4ca0[];
extern char* g_868050;
extern int g_773d78;

void __cdecl fcn_005925e0(int, int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);

void __cdecl fcn_00592630(void)
{
	int i;
	int n;
	unsigned char* e;

	for (i = 0; i < 768; i++) {
		if (g_7f4ca0[i * 540 + 2] == 6) {
			break;
		}
	}
	n = 1;
	fcn_005925e0(0, g_773d78);
	e = gm_StartFilteredEntitySearch(1, 5, 0xf);
	if (e != 0) {
		n = 2;
		fcn_005925e0(1, (int) e);
	}
	if (*(int*) (g_7f4ca0 + i * 540 + 0x170) != 0) {
		fcn_005925e0(n, *(int*) (g_7f4ca0 + i * 540 + 0x170));
	}
	n = 3;
	for (e = gm_StartFilteredEntitySearch(1, 4, i); e != 0; e = gm_AddObjekt()) {
		if (g_868050[*e * 589] != 2) {
			fcn_005925e0(n++, (int) e);
		}
	}
}
