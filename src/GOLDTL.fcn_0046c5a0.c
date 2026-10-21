#include <stdio.h>
#include <string.h>

extern int g_1015ea0;
extern int g_1015ea4;
extern int g_102d020;
extern int g_102d024;
extern int g_1040490;
extern int g_1040494;
extern int g_67d380;
extern int g_67d390;
extern int g_67d964;
extern int g_67d968;
extern int g_6b23a4;
extern int g_6b25b0;
extern int g_772524;
extern int g_772530;
extern int g_772554;
extern int g_7725b4;
extern int g_7725f8;
extern int g_7725fc;

int __cdecl fcn_00465950(char* name);
void __cdecl fcn_00472880(int font);
void __cdecl fcn_0046b5f0(int pos, int baseline, int a0, int a1, int last, int v35, int v38, int v37);
int __cdecl fcn_0046b520(char* text, unsigned int font);
void __cdecl fcn_0046eda0(int x, int y, int a1);
int __cdecl fcn_00466190(int table, int index);
void __cdecl fcn_0047a040(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
void __cdecl fcn_0047cba0(int x, int y, int a0, int text);
void __cdecl fcn_00469c40(unsigned int a, int b, int c);
void __cdecl fcn_0046c4e0(int a1);

/* Renders one element's text record: walks the text string, expands the
 * '%'/'$' markup through the tag dispatch table, word-wraps the token into the
 * glyph buffer and emits the runs through the draw helpers. */
#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x0046c5a0 */
void __cdecl fcn_0046c5a0(int a0, int a1)
{
	char line[384];
	char text[256];
	char wrap[768];
	char saved[256];
	char* p;
	char* q;
	char* d;
	char* s;
	char ch;
	int v6;
	int v10;
	int v28;
	int v5;
	int v7;
	unsigned int v11;
	unsigned int v12;
	int v13;
	unsigned int v18;
	unsigned int v19;
	unsigned int v20;
	int v21;
	unsigned int v22;
	int v23;
	int v24;
	int v25;
	int v26;
	int v27;
	unsigned short v29;
	char v30;
	int v31;
	unsigned int v32;
	unsigned int v33;
	unsigned int v34;
	unsigned int v35;
	int v36;
	int v37;
	int v38;
	int v39;
	unsigned int v40;
	int v41;
	int tag;

	v40 = 0;
	v32 = 0;
	v23 = 0;
	v36 = 0;
	v35 = 0;
	v24 = 0;
	v6 = a1 * 0x3cc;
	v10 = v6 + 0x1015f40;
	v28 = v10;
	if (*(int*) (v6 + 0x10161cc) != 0) {
		fcn_00472880(*(int*) (v6 + 0x10161cc));
	} else {
		fcn_00472880(fcn_00465950("_FONT"));
	}
	g_7725b4 = 0;
	if (*(int*) (v6 + 0x1015f7c) == 0) {
		return;
	}
	v25 = *(int*) (v6 + 0x1015f4c);
	v5 = *(int*) (v6 + 0x1015f58) + *(int*) (v6 + 0x1015f44);
	v37 = v25 - *(int*) (v6 + 0x1015f5c);
	v27 = *(int*) (v6 + 0x1015f60) + *(int*) (v6 + 0x1015f48);
	v21 = (*(int*) (v6 + 0x1015f50) - *(int*) (v6 + 0x1015f64)) + v27;
	if (*(unsigned int*) (v6 + 0x1015f54) & 8) {
		v27 = *(int*) (v6 + 0x1015f48) + 0xc;
	}
	if (*(unsigned int*) (v6 + 0x1015f54) & 0x20) {
		v37 = v25 + -0xc;
	}
	v37 += *(int*) (v6 + 0x1015f44);
	v19 = g_7725fc;
	v18 = g_67d964;
	g_102d024 = v27 - *(int*) (v6 + 0x1016198);
	v22 = g_7725f8;
	g_1015ea4 = *(unsigned short*) (g_772524 + 8);
	v20 = g_67d968;
	v13 = 0;
	v12 = 0xffffffff;
	g_772530 = 0;
	v41 = 0;
	s = *(char**) (v6 + 0x1015f7c);
	do {
		if (!v12) {
			break;
		}
		v12 -= 1;
		p = s + 1;
		ch = *s;
		s = p;
	} while (ch);
	v26 = (int) (~v12 - 1);
	g_102d020 = v5;
	v38 = v5;
	if (1 <= v26) {
		while (*(char*) (v41 + *(int*) (v10 + 0x3c)) != 0) {
			*(unsigned int*) (v13 * 0x10c + 0x1011ae4) = 0;
			for (;;) {
				v6 = *(int*) (v10 + 0x3c);
				if ((*(char*) (v6 + v41) != '%') && (*(char*) (v6 + v41) != '$')) {
					break;
				}
				v41 += 1;
				if (2 <= g_6b25b0) {
					v12 = (unsigned int) _isctype(*(char*) (v6 + v41), 4);
				} else {
					v12 = *(unsigned char*) (g_6b23a4 + *(char*) (v6 + v41) * 2) & 4;
				}
				if (v12) {
					v41 += 1;
				}
				tag = (int) *(char*) (*(int*) (v10 + 0x3c) + v41);
				if ((unsigned int) (tag - 0x25) <= 0x4f) {
					((void (__cdecl*) (void)) (*(unsigned char*) (tag + 0x46dcdf) * 4 + 0x46dcb0)) ();
					return;
				}
				sprintf(line, "Unknown textparameter: %%%c", *(char*) (*(int*) (v10 + 0x3c) + -1 + v41));
				v5 = g_102d020;
			}
			v6 = *(int*) (v10 + 0x3c);
			if (*(char*) (v6 + v41) != 0) {
				if (*(char*) (v6 + v41) == ' ') {
					do {
						s = (char*) (v6 + 1 + v41);
						v41 += 1;
					} while (*s == ' ');
				}
				s = (char*) (v6 + v41);
				v12 = (unsigned int) strchr(s, 0x20);
				if (!v12) {
					v12 = *(int*) (v10 + 0x3c) + v26;
				}
				if (!v24) {
					v7 = (int) strchr(s, 0x25);
					if (((v7 != 0) && (v7 <= (int) v12)) && (*(char*) (v7 + 1) != '%')) {
						v12 = (unsigned int) v7;
					}
				}
				v24 = 0;
				v7 = (int) strchr(s, 0x24);
				if ((v7 != 0) && (v7 < (int) v12)) {
					v12 = (unsigned int) v7;
				}
				v12 -= (int) s;
				v33 = v12;
				if (v12) {
					v6 = 0x40;
					q = text;
					while (v6) {
						q[0] = '\0';
						q[1] = '\0';
						q[2] = '\0';
						q[3] = '\0';
						v6 -= 1;
						q = q + 4;
					}
					if (0 <= (int) v12) {
						v7 = (int) (v12 >> 2);
						q = text;
						while (v7) {
							d = q + 4;
							p = s + 4;
							*(unsigned int*) q = *(unsigned int*) s;
							v7 -= 1;
							s = p;
							q = d;
						}
						v7 = (int) (v12 & 3);
						while (v7) {
							d = q + 1;
							p = s + 1;
							*q = *s;
							v7 -= 1;
							s = p;
							q = d;
						}
						text[v12 + 1] = '\0';
						v10 = v28;
					}
					v5 = fcn_0046b520(text, *(unsigned int*) (v10 + 0x28c));
					v6 = a1;
					v31 = v5;
					if (v5 + g_102d020 > v37) {
						if (!(*(unsigned int*) (v10 + 0x14) & 0x2000)) {
							v12 = 0xffffffff;
							v6 = 0;
							v34 = 0;
							s = text;
							do {
								if (!v12) {
									break;
								}
								v12 -= 1;
								p = s + 1;
								ch = *s;
								s = p;
							} while (ch);
							v5 = (int) (~v12 - 1);
							do {
								s = &text[v6];
								wrap[v6] = *s;
								v6 += 1;
							} while (*s);
							v6 = 0;
							do {
								s = &text[v6];
								saved[v6] = *s;
								v6 += 1;
							} while (*s);
							v6 = g_102d020;
							v39 = v5;
							if (0 <= v5) {
								v13 = (int) (0xfffffa80 - v5);
								do {
									s = &text[v39];
									if ((text[v39] == '~') || (text[v39] == '-')) {
										q = s;
										do {
											ch = *q;
											q[v13] = ch;
											q = q + 1;
										} while (ch);
										v34 = (unsigned int) (*s == '-');
										*s = '-';
										v11 = *(unsigned int*) (v10 + 0x28c);
										text[v39 + 1] = '\0';
										v6 = g_102d020;
										if (fcn_0046b520(text, v11) + g_102d020 <= v37) {
											break;
										}
									}
									v39 -= 1;
									v13 += 1;
								} while (0 <= v39);
							}
							if (1 <= v39) {
								v39 += (int) v34;
								v12 = 0xffffffff;
								s = text;
								do {
									if (!v12) {
										break;
									}
									v12 -= 1;
									p = s + 1;
									ch = *s;
									s = p;
								} while (ch);
								v12 = ~v12;
								v7 = (int) (v12 >> 2);
								s = text;
								q = (char*) (g_772530 * 0x10c + 0x10119e0);
								while (v7) {
									d = q + 4;
									p = s + 4;
									*(unsigned int*) q = *(unsigned int*) s;
									v7 -= 1;
									s = p;
									q = d;
								}
								v7 = (int) (v12 & 3);
								while (v7) {
									d = q + 1;
									p = s + 1;
									*q = *s;
									v7 -= 1;
									s = p;
									q = d;
								}
								v33 = v12 - 1;
								v11 = (unsigned int) fcn_0046b520(text, *(unsigned int*) (v28 + 0x28c));
								v5 = g_772530 + 1;
								*(unsigned int*) (g_772530 * 0x10c + 0x1011ae8) = v11;
								v41 = v41 + -1 + (int) v34 + (int) (v12 - 1);
								v6 = g_102d020;
								v10 = v28;
								g_772530 = v5;
							} else {
								v5 = 0;
								do {
									s = &saved[v5];
									text[v5] = *s;
									v5 += 1;
								} while (*s);
							}
							v5 = v38;
							fcn_0046b5f0(v6, g_102d024, a0, a1, 0, v35, v38, v37);
							g_102d024 += g_1015ea4;
							v6 = *(int*) (v10 + 0x248) + v36;
							v36 += 1;
							g_102d020 = v5;
							*(int*) (v10 + 0x4c + v6 * 4) = v41;
							if (1 <= v39) {
								s = &saved[v39];
								v6 = -(int) s;
								do {
									ch = *s;
									s[(int) &text[v6]] = ch;
									s = &s[1];
								} while (ch);
								v12 = 0xffffffff;
								s = text;
								do {
									if (!v12) {
										break;
									}
									v12 -= 1;
									p = s + 1;
									ch = *s;
									s = p;
								} while (ch);
								v33 = ~v12 - 1;
								v31 = fcn_0046b520(text, *(unsigned int*) (v10 + 0x28c));
							}
							goto label_46d915;
						}
						if (v5 + g_102d020 < g_1040494) {
							v31 = (short) v5;
							v31 = *(short*) (v10 + 0xc) + (short) v31;
							fcn_0046eda0((int) (short) v31, (int) *(short*) (v10 + 0x10), a1);
							goto label_46d915;
						}
						fcn_0046eda0((int) (short) ((short) g_1040494 - *(short*) (v10 + 4)), (int) *(short*) (v10 + 0x10), a1);
						v5 = v38;
						fcn_0046b5f0(g_102d020, g_102d024, a0, v6, 0, v35, v38, v37);
						g_102d020 = v5;
						g_102d024 += g_1015ea4;
						v6 = v36 + 1;
						*(int*) (v10 + 0x4c + (*(int*) (v10 + 0x248) + v36) * 4) = v41;
						v36 = v6;
					}
label_46d915:
					v5 = g_102d020;
					v6 = v36;
					v12 = ((int) (char) *(unsigned int*) (v10 + 0x14) & 8U) >> 3;
					*(int*) (v10 + 0x24c) = *(int*) (v10 + 0x248) + v6;
					if (*(unsigned int*) (v10 + 0x14) & 0x20) {
						v12 += 2;
					}
					v34 = v12;
					if ((int) v12 < *(int*) (v10 + 0x2c)) {
						do {
							v13 = g_1015ea0 + *(int*) (*(int*) (v10 + 0x28) + (int) v12 * 4) * 0x2f4;
							v11 = *(unsigned int*) (v13 + 0x78);
							v36 = v13;
							while ((((!v11 && (*(int*) (v13 + 0x10) < v31 + v5)) && (v39 = *(int*) (v13 + 0x10) + *(int*) (v13 + 0x18), v5 < v39)) && ((*(int*) (v13 + 0x14) < (int) (g_102d024 + g_1015ea4) &&
							    (g_102d024 < *(int*) (v13 + 0x1c) + *(int*) (v13 + 0x14)))))) {
								g_102d020 = v39 + 6;
								v5 = g_102d020;
								if (v37 < v31 + g_102d020) {
									fcn_0046b5f0(g_102d020, g_102d024, a0, a1, 0, v35, v38, v37);
									g_102d024 += g_1015ea4;
									*(int*) (v10 + 0x4c + (*(int*) (v10 + 0x248) + v6) * 4) = v41;
									v6 += 1;
									v13 = v36;
									v5 = v38;
								}
								v11 = *(unsigned int*) (v13 + 0x78);
								g_102d020 = v5;
							}
							v12 = v34 + 1;
							v34 = v12;
						} while ((int) v12 < *(int*) (v10 + 0x2c));
						v36 = v6;
					}
					v10 = (g_67d380 - *(int*) (v10 + 4)) + v31 + v5;
					if (v25 < v10) {
						v25 = v10;
					}
					if (v33) {
						v5 += g_67d380 + v31;
						g_102d020 = v5;
					}
					v10 = g_772530 * 0x10c;
					v12 = v33 + 1 >> 2;
					s = text;
					q = (char*) (v10 + 0x10119e0);
					while (v12) {
						d = q + 4;
						p = s + 4;
						*(unsigned int*) q = *(unsigned int*) s;
						v12 -= 1;
						s = p;
						q = d;
					}
					v12 = v33 + 1 & 3;
					while (v12) {
						d = q + 1;
						p = s + 1;
						*q = *s;
						v12 -= 1;
						s = p;
						q = d;
					}
					*(int*) (v10 + 0x1011ae8) = v31;
					*(unsigned int*) (v10 + 0x1011ae4) = g_7725b4;
					*(unsigned short*) (v10 + 0x1011ae0) = v29;
					*(char*) (v10 + 0x1011ae2) = v30;
					g_772530 += 1;
					v41 += (int) v33;
					v10 = v28;
					if (0x21 <= g_772530) {
						g_772530 = 0;
					}
				} else {
					v5 = g_102d020;
				}
			}
			if (v26 <= v41) {
				break;
			}
			v13 = g_772530;
		}
	}
	v6 = a1;
	fcn_0046b5f0(v5, g_102d024, a0, a1, 1, v35, v38, v37);
	if (*(unsigned int*) (v10 + 0x14) & 0x4000) {
		if (g_1040490 < (int) ((g_1015ea4 - 8) + g_102d024)) {
			v5 = *(int*) (v10 + 0x27c);
			v6 = *(int*) (g_1015ea0 + 0x40 + v5 * 0x2f4);
			if (v6) {
				v5 = *(int*) (v6 + 0x27c);
				v13 = ((*(int*) (v6 + 8) - g_1015ea4) - g_102d024) + 8 + g_1040490;
				v11 = *(unsigned int*) (v6 + 4);
			} else {
				v13 = ((g_1040490 - g_1015ea4) - g_102d024) + -8 + *(int*) (v10 + 8);
				v11 = *(unsigned int*) (v10 + 4);
			}
			fcn_00469c40(v11, v13, v5);
			v6 = a1;
		}
		fcn_0046eda0((int) *(short*) (v10 + 0xc), (int) (short) (((short) g_1015ea4 - *(short*) (v10 + 8)) + (short) g_102d024), v6);
	}
	g_102d024 += g_1015ea4;
	if (*(unsigned int*) (v10 + 0x14) & 0x2000) {
		fcn_0046eda0((int) (short) v25, (int) *(short*) (v10 + 0x10), v6);
	}
	v5 = g_102d024 - *(int*) (v10 + 8);
	if (*(int*) (v10 + 0x254) < v5) {
		*(int*) (v10 + 0x254) = v5;
	}
	fcn_0047a040(v22, v19, v18, v20);
	if ((*(unsigned char*) (v10 + 0x14) & 0x20) && (v5 = ((v21 - v27) + -0x10) / *(int*) (v10 + 0x254) + v27, !g_772554)) {
		v11 = (unsigned int) fcn_00466190(g_67d390, 5);
		fcn_0047cba0(v37 + 1, v5, a0, (int) v11);
	}
	if ((*(int*) (v10 + 0x3c4) != *(int*) (v10 + 0x2c)) && (v23)) {
		fcn_0046c4e0(v6);
		*(unsigned int*) (v10 + 0x3c4) = *(unsigned int*) (v10 + 0x2c);
	}
	return;
}
