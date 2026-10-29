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
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_005c9090(int, int, int, int, int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_004ea460(void);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_005cadc0(int, char*, char*, int, void*);
int __cdecl fcn_005ccca0(char*, char*, int, void*);

/* ADDRESS: GOLDTL 0x005cd440 */
int __cdecl fcn_005cd440(char* a0, int a1, int a2, void* a3)
{
	int btn[9];
	int order[9];
	int dlg;
	int i;
	int id;
	int result;
	int scale;
	int e;

	order[0] = 0;
	order[1] = 8;
	order[2] = 6;
	order[3] = 4;
	order[4] = 5;
	order[5] = 1;
	order[6] = 2;
	order[7] = 3;
	order[8] = 7;
	dlg = fcn_00470820(0, 0, s_6ac994);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 2);
	if (a1) {
		fcn_00519190(a1);
	} else {
		fcn_00519190(0xa1);
	}
	d2_SetForm(dlg, 3);
	id = fcn_00472250(dlg, 3, fcn_00519190(0x1687));
	d2_SetForm(dlg, 1);
	btn[0] = fcn_0046f740(0x45, 0x3c, 0x589, g_772514);
	btn[1] = fcn_0046f740(0x10f, 0x25, 0x599, g_772514);
	btn[2] = fcn_0046f740(0x10f, 0x93, 0x58d, g_772514);
	btn[3] = fcn_0046f740(0x69, 0xab, 0x590, g_772514);
	btn[4] = fcn_0046f740(0x1b5, 0xab, 0x58c, g_772514);
	btn[5] = fcn_0046f740(0x45, 0x125, 0x58a, g_772514);
	btn[6] = fcn_0046f740(0x10f, 0x125, 0x58f, g_772514);
	btn[7] = fcn_0046f740(0x1d9, 0x125, 0x58b, g_772514);
	btn[8] = fcn_0046f740(0x1d9, 0x3c, 0x58e, g_772514);
	for (i = 0; i < 9; i++) {
		if (i != 1 || *(int*) (a0 + 0x18) == 0) {
			e = btn[i];
			*(int*) (g_1015ea0 + e * 0x2f4 + 0x5c) = 1;
			*(int*) (g_1015ea0 + e * 0x2f4 + 0x1d0) = 3;
		}
		e = btn[i];
		*(int*) (g_1015ea0 + e * 0x2f4 + 0x84) = 0x55;
		fcn_005c9090(*(int*) (0x14a9de8 + order[i] * 4),
			     *(int*) (g_1015ea0 + e * 0x2f4 + 0x10)
				 - *(int*) (g_77255c + 4) + 0x20,
			     *(int*) (g_1015ea0 + e * 0x2f4 + 0x14)
				 - *(int*) (g_77255c + 8) - 0x19,
			     200, 0x55);
	}
	result = 0;
	fcn_00473a90(0, 0);
	g_100f1dc = -1;
	scale = btn[8] * 0x2f4;
	do {
		result = 0;
		if (!fcn_004ea460()) {
			*(int*) (g_1015ea0 + scale + 0x5c) = 0;
			*(int*) (g_1015ea0 + scale + 0x1d0) = 0;
		} else {
			*(int*) (g_1015ea0 + scale + 0x5c) = 1;
			*(int*) (g_1015ea0 + scale + 0x1d0) = 3;
		}
		if (g_14ce8e0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			for (i = 0; i < 9; i++) {
				if (btn[i] == g_67d370) {
					break;
				}
			}
			if (i > -1 && i < 9) {
				fcn_00471af0(dlg, 0);
				result = fcn_005cadc0(order[i], a0, (char*) a1, 0, a3);
				fcn_00471af0(dlg, 1);
			} else if (g_67d370 == id) {
				fcn_00471af0(dlg, 0);
				result = fcn_005ccca0(a0, (char*) a1, -1, a3);
				fcn_00471af0(dlg, 1);
			}
			if (result && a3 == 0 && (*(unsigned char*) (a0 + 0x14) & 4) == 0) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005cd440, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return result;
}
