/* Refreshes the current selection/building view state. */

extern int g_6772c4;
extern int g_100f1e8;
extern int g_100f1ec;
extern int g_100f890;
extern int g_100f894;
extern int g_100f800;
extern int g_67d388;
extern int g_67d370;
extern int g_14ce8d8;
extern int g_14ce8d0;
extern int g_100f1dc;
extern int g_6b5c8c;
extern int g_100f884;
extern int g_772578;
extern int g_100f84c;
extern int g_100f1d0;
extern int g_100f1e4;
extern int g_67d8d0;
extern int g_67d8d4;
extern int g_1015ea4;

int __cdecl fcn_0046aee0(int x, int y);
void __cdecl fcn_004748b0(void);
void __cdecl fcn_00473b10(void);
void __cdecl fcn_004234e0(int handle, char* text, int a, int b, int c, int d, int e);
void __cdecl fcn_00472380(int object, int selected);
void __cdecl fcn_0046e790(int index);

/* ADDRESS: GOLDTL 0x00474e80 */
void __cdecl fcn_00474e80(void)
{
	int v4;
	int v7;
	int v6;
	int v8;
	int v2;
	int found;
	unsigned int* v1;
	int* v5;
	int* v10;
	char* text;

	if (g_6772c4 != 0) {
		g_100f1e8 = *(short*) 0x14cf900;
		g_100f1ec = *(short*) 0x14cf902;
	}
	g_100f890 = fcn_0046aee0(g_100f1e8, g_100f1ec);
	fcn_004748b0();
	if (g_67d388 != -1) {
		g_100f894 = g_67d388;
		g_100f800 = -1;
		v4 = 0;
		v7 = *(int*) (g_67d388 * 0x3cc + 0x1015f6c);
		if (1 <= v7) {
			v5 = (int*) (g_67d388 * 0x3cc + 0x1015f68);
			do {
				if (*v5 == g_67d370) {
					g_100f800 = v4;
					break;
				}
				v4 += 1;
				v5 = v5 + 1;
			} while (v4 < v7);
		}
	} else {
		g_100f894 = -1;
	}
	fcn_00473b10();
	if (g_14ce8d8 != 0) {
		v7 = g_67d370;
		if (g_100f890 != -1) {
			v4 = 0x1015ea0 + g_67d370 * 0x2f4;
			if ((*(int*) (v4 + 0x58) != 0 || *(int*) (v4 + 0x5c) != 0) &&
			    *(int*) (v4 + 0x20) != 0x45) {
				g_100f1dc = g_100f890;
				g_6b5c8c = 1;
				v1 = *(unsigned int**) (v4 + 0x50);
				if (v1 != 0) {
					if (v1[0x67] != 0 && v1[0x66] == 0) {
						g_100f884 = *v1;
					}
				} else {
					g_100f884 = -1;
				}
				if (*(int*) (v4 + 0x58) != 0) {
					text = (char*) 0x67d908;
					*(int*) (v4 + 0x38) = *(int*) (v4 + 0x38) ^ 1;
					*(int*) (0x1015ea0 + g_67d370 * 0x2f4 + 0x3c) =
						*(int*) (0x1015ea0 + 0x38 + g_67d370 * 0x2f4);
				} else if (g_100f890 != 1) {
					text = (char*) 0x67d908;
				} else {
					text = (char*) 0x67d8f0;
				}
				fcn_004234e0(g_772578, text, 1, 0x3f, 0x7f, 0, 0);
				found = 0;
				v4 = 0;
				do {
					if (found != 0) {
						break;
					}
					v6 = 0;
					if (1 <= *(int*) (v4 + 0x102cbc4)) {
						v10 = (int*) (v4 + 0x102cbcc);
						do {
							if (*v10 == v7) {
								v8 = 0;
								if (1 <= *(int*) (v4 + 0x102cbc4)) {
									v5 = (int*) (v4 + 0x102cbcc);
									do {
										v2 = *v5;
										if (v2 != v7) {
											fcn_00472380(v2, 0);
										} else {
											fcn_00472380(v2, 1);
											*(int*) (v4 + 0x102cbc8) = v8;
										}
										v8 += 1;
										v5 = v5 + 1;
										v7 = g_67d370;
									} while (v8 < *(int*) (v4 + 0x102cbc4));
								}
								found = 1;
							}
							v6 += 1;
							v10 = v10 + 1;
						} while (v6 < *(int*) (v4 + 0x102cbc4));
					}
					v4 += 0x8c;
				} while (v4 < 0x460);
				if (g_100f1dc != g_100f84c) {
					g_100f84c = g_100f1dc;
				}
				g_100f1d0 = g_100f800;
			}
		}
		if (v7 != -1) {
			g_100f1e4 = 0x1015ea0 + v7 * 0x2f4;
		}
	} else {
		g_100f1dc = -1;
		g_100f1e4 = 0;
		g_100f1d0 = -1;
	}
	g_67d8d0 = -1;
	g_67d8d4 = -1;
	v7 = 0;
	v5 = (int*) 0x100f204;
	for (;;) {
		if (g_100f1e8 >= v5[-1] &&
		    g_100f1e8 <= v5[-1] + v5[1] &&
		    g_100f1ec >= *v5 &&
		    g_100f1ec <= *v5 + v5[2] &&
		    v5[4] != 0) {
			g_67d8d4 = v7;
			if (g_14ce8d8 != 0) {
				g_67d8d0 = v7;
			}
			break;
		}
		v5 += 6;
		v7 += 1;
		if ((int) v5 >= 0x100f504) {
			break;
		}
	}
	if (g_100f894 != -1) {
		v4 = 0x1015f40 + g_100f894 * 0x3cc;
		if (g_14ce8d0 != 0 &&
		    (*(unsigned char*) (v4 + 0x14) & 0x20) != 0 &&
		    *(int*) (v4 + 0xc) + *(int*) (v4 + 4) - 0xc < g_100f1e8 &&
		    g_100f1ec > *(int*) (v4 + 8) + 0xa &&
		    g_100f1ec < *(int*) (v4 + 0x10) + *(int*) (v4 + 8) - 0xa) {
			v7 = ((g_100f1ec - *(int*) (v4 + 8) - 0xc) * *(int*) (v4 + 0x254)) /
			     (*(int*) (v4 + 0x10) - 0x18) + 4;
			*(int*) (v4 + 0x258) = v7;
			*(int*) (v4 + 0x248) = v7 / g_1015ea4;
			*(int*) (v4 + 0x44) = *(int*) (v4 + 0x48 + (v7 / g_1015ea4) * 4);
			if (v7 != *(int*) (v4 + 0x25c)) {
				fcn_0046e790(g_100f894);
			}
		}
	}
}
