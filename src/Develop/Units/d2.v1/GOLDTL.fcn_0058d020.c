extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_772514;
extern int g_774654;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
int __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_0058c4f0(char*, int, int, int*, int*);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_0058cda0(char*, int);
void __cdecl fcn_00471af0(int, int);

/* ADDRESS: GOLDTL 0x0058d020 */
void __cdecl fcn_0058d020(char* a0)
{
	int sel;
	int ids[4];
	int dlg;
	int task;
	int i;

	sel = 0;
	dlg = fcn_00470820(0, 0, "Locations\\Friedhof\\RentAGrave");
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(dlg, 1);
	fcn_00519190(0x410a, 0x4108);
	fcn_0058c4f0(a0, dlg, 2, ids, &sel);
	d2_SetForm(dlg, 3);
	task = fcn_00472250(dlg, 3, fcn_00519190(0x6a4078, 0x4117));
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == task) {
				fcn_00471af0(dlg, 0);
				if (fcn_0058cda0(a0, sel) == 1) {
					g_774654 = 1;
				}
				fcn_00471af0(dlg, 1);
			} else {
				for (i = 0; i < 4; i++) {
					if (g_67d370 == ids[i] && i != sel) {
						sel = i;
						fcn_0058c4f0(a0, dlg, 2, ids, &sel);
						break;
					}
				}
			}
		}
	} while (fcn_005373e0(0x58d020, 0x677c7) != 0);
	fcn_00471e30(dlg);
}
