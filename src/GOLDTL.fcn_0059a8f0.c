// FUNCTION: GOLD 0x00591bb0
// SIZE: 288
// FUNCTION: GOLDTL 0x0059a8f0
// SIZE: 288

extern unsigned short g_774970;
extern char g_7f4ca0[];
extern char* g_7746cc;

char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);
void __cdecl fcn_0041d9e0(char*);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_00526920(char*, int, char*);

void __cdecl fcn_0059a8f0(void)
{
	char* p;
	char* e;
	char* d;

	for (p = fcn_005463a0(1, 0, 0x3d); p != 0; p = fcn_005462a0()) {
		if (*(int*) (p + 0xac) == *(int*) (g_7f4ca0 + g_774970 * 540 + 4)) {
			for (e = gm_StartFilteredEntitySearch(1, 5, 4); e != 0; e = gm_AddObjekt()) {
				if (*(int*) (e + 0x65) == *(int*) (g_7f4ca0 + g_774970 * 540 + 4)) {
					d = fcn_00502cd0(*(int*) (e + 0x5d), 1, 0, 0x65);
					if (d != 0 && g_7746cc != d) {
						fcn_00526920(e, *(int*) (d + 2), "");
					}
					return;
				}
			}
			fcn_0041d9e0("lc_PlayerInJail(): Could not find ob_DIEBESGILDE_GEFAENGNIS...");
			return;
		}
	}
	e = gm_StartFilteredEntitySearch(1, 5, 6);
	if (e == 0) {
		fcn_0041d9e0("lc_PlayerInJail(): Could not find a jail...");
		return;
	}
	d = fcn_00502cd0(*(int*) (e + 0x5d), 1, 0, 0xba);
	if (d != 0 && g_7746cc != d) {
		fcn_00526920(e, *(int*) (d + 2), "");
	}
}
