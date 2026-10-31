extern int g_772514;
extern char* g_77255c;
extern char* g_1015ea0;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern char s_6ac994[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_005c9090(int, int, int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005cde50 */
void __cdecl fcn_005cde50(void (*a0)(int), int a1, int a2)
{
	int btn[14];
	int dlg;
	int i;
	int sel;
	int id;

	btn[7] = 8;
	btn[8] = 6;
	btn[9] = 4;
	btn[10] = 5;
	btn[11] = 1;
	btn[12] = 2;
	btn[13] = 3;
	dlg = fcn_00470820(0, 0, s_6ac994);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 2);
	io_AppendText(a1 ? a1 : 0xa2);
	d2_SetForm(dlg, 1);
	btn[0] = fcn_0046f740(0x10f, 0x25, 0x599, g_772514);
	btn[1] = fcn_0046f740(0x10f, 0x93, 0x58d, g_772514);
	btn[2] = fcn_0046f740(0x69, 0xab, 0x590, g_772514);
	btn[3] = fcn_0046f740(0x1b5, 0xab, 0x58c, g_772514);
	btn[4] = fcn_0046f740(0x45, 0x125, 0x58a, g_772514);
	btn[5] = fcn_0046f740(0x10f, 0x125, 0x58f, g_772514);
	btn[6] = fcn_0046f740(0x1d9, 0x125, 0x58b, g_772514);
	for (i = 0; i < 7; i++) {
		if (i != 0 || a2 != 0) {
			id = btn[i];
			*(int*) (g_1015ea0 + id * 0x2f4 + 0x5c) = 1;
			*(int*) (g_1015ea0 + id * 0x2f4 + 0x1d0) = 3;
		}
		id = btn[i];
		*(int*) (g_1015ea0 + id * 0x2f4 + 0x84) = 0x55;
		fcn_005c9090(*(int*) (0x14a9de8 + btn[i + 7] * 4),
			     *(int*) (g_1015ea0 + id * 0x2f4 + 0x10) - *(int*) (g_77255c + 4) + 0x20,
			     *(int*) (g_1015ea0 + id * 0x2f4 + 0x14) - *(int*) (g_77255c + 8) - 0x19,
			     200, 0x55);
	}
	d2_SetOverlayAnimation(0, 0);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0)
			g_774654 = 1;
		if (g_100f1dc != -1) {
			sel = -1;
			for (i = 0; i < 7; i++) {
				if (btn[i] == g_67d370) {
					sel = i;
					break;
				}
			}
			if (a0 != 0 && sel >= 0 && sel <= 6) {
				fcn_00471af0(dlg, 0);
				(*a0)(btn[sel + 7]);
				fcn_00471af0(dlg, 1);
			}
		}
	} while (fcn_005373e0((void*) fcn_005cde50, 0x657c7) != 0);
	fcn_00471e30(dlg);
}
