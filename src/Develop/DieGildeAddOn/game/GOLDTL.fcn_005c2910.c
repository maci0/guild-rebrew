extern int g_774654;
extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_67d370;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_00546190(void*);
void* __cdecl he_fn_Handlung(void);
void* __cdecl fcn_005463a0(int, ...);
void* __cdecl gm_SearchTable67(int);

/* ADDRESS: GOLDTL 0x005c2910 */
void __cdecl fcn_005c2910(char* e)
{
	int win;
	char* u;
	int id;
	int saved;
	int r;

	id = *(int*) (e + 1);
	u = (char*) fcn_005463a0(1, 0, 0x1b);
	while (u != 0 && *(int*) (u + 0xac) != *(int*) (e + 1)) {
		u = (char*) he_fn_Handlung();
	}
	win = fcn_00470820(0, 0, "Panel\\Gebaeude_Verkaufen_pergament");
	fcn_00471b60(win);
	d2_SetForm(win, 2);
	saved = fcn_00472250(win, 2, io_AppendText(0x17cc, e, *(int*) (u + 0xb0)));
	d2_SetOverlayAnimation(0, 0);
	fcn_005373e0((void*) 0, 0x677c7);
	do {
		r = (int) gm_SearchTable67(id);
		if ((e[0x5b] & 4) || r == 0) {
			g_774654 = 1;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc == 2) {
			if (g_67d370 == saved) {
				fcn_004c5420(*(int*) (e + 1), 0x5a, 2, 0, 2);
				fcn_00546190(u);
				g_774654 = 1;
			}
		} else if (g_100f1dc == 1) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005c2910, 0x677c7) != 0);
	fcn_00471e30(win);
}
