extern int g_772ea8;
extern int g_772eac;
extern int g_100f1dc;
extern int g_774654;
extern int g_14ce8e0;
extern unsigned char g_773d75;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl fcn_004d5450(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
float __cdecl gm_GetEntitySkill(char*, int);
int __cdecl fcn_00507e30(char*, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_00502cd0(int, int, ...);
int __cdecl gm_SearchTable67(int);
int __cdecl gm_FindRecordById(int);
int __cdecl fcn_0050de80(char*, int*);
float __cdecl fcn_0050bb50(int, int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_004d5490(int, int, int);
void __cdecl fcn_004d5740(char*, int, int);
int __cdecl fcn_004e6eb0(char*, unsigned int);
int __cdecl fcn_004d52a0(int, int, char*, char*, float);
void __cdecl fcn_00472170(int, int);
int __cdecl gm_RandomMod(int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00471e30(int);

/* Modal sub-dialog for picking the guard shift. The first block drives the
 * generic selection page, the second the concrete shift of one guard. */
/* ADDRESS: GOLDTL 0x004d5940 */
unsigned int __cdecl fcn_004d5940(int a0)
{
	char str[1024];
	char text[1024];
	int items[17];
	unsigned short ids[56];
	unsigned int answer;
	int count;
	int win;
	int id;
	int sel;
	int row;
	int rec;
	int pct;
	int i;
	int k;
	int t;
	int v;
	int n;
	int choice;
	int r;
	char* list;
	char* names;
	int* p;
	int* q;
	unsigned char flags;

	answer = 1;
	count = 0;
	sel = 0;
	win = fcn_00470820(0, 0, (char*) 0x68be84);
	fcn_00471d80(win, 3);
	names = *(char**) 0x772e98;
	list = *(char**) 0x772e9c;
	g_772ea8 = 0;
	id = (int) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0x14));
	rec = (int) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0x10c));
	k = fcn_004d5450(rec);
	d2_SetForm(win, 1);
	if (list[1] == 6) {
		flags = *(unsigned char*) (a0 + 0x7c);
		if (flags & 2) {
			io_AppendText(0x1138, k + 0x1125, rec, *names, id);
			d2_SetForm(win, 2);
			sel = io_AppendText(0x113a, *names, id);
		} else if (flags & 1) {
			count = 0;
			p = (int*) (a0 + 0x100);
			i = 3;
			do {
				if (*p != -1) {
					count += 1;
				}
				p++;
				i--;
			} while (i);
			v = (int) gm_GetEntitySkill(list, 3);
			io_AppendText(0x112e, rec, *names);
			d2_SetForm(win, 2);
			io_AppendText(0x112f, count, 0xc10);
			if (0.5 <= (float) v) {
				io_AppendText(*(int*) (a0 + 0x110) ? 0x1134 : 0x1135);
			}
			if (*(float*) 0x6640f8 <= (float) v) {
				fcn_00507e30(names, 3);
				t = (int) gm_GetEntitySkill(list, 3);
				if (5 <= t) {
					t = 4;
				}
				io_AppendText(0x1131, t + 0x1128);
			}
			if (*(char*) (names + 9)) {
				sel = io_AppendText(0x1133, 0x1137);
			} else {
				sel = io_AppendText(0x1133, 0x1136);
			}
		} else if (flags & 4) {
			io_AppendText(0x113b, rec, *names);
			d2_SetForm(win, 2);
			sel = io_AppendText(0x113c, *names, id);
		}
		d2_SetForm(win, 1);
		io_AppendText(0x1132);
		fcn_004d5740((char*) (a0 + 0xc0), 0, 0xb4);
		fcn_00472250(win, 2, sel);
		fcn_00472250(win, 2, sel + 1);
		t = fcn_005373e0(0x4d5940, 0x7d6c6);
		while (t) {
			if (g_14ce8e0) {
				g_774654 = 1;
				g_772ea8 = 1;
				answer = 0;
			}
			if (g_100f1dc != 2) {
				if (g_100f1dc == 1) {
					g_772ea8 = 1;
					answer = 0;
					g_774654 = 1;
				}
			} else {
				answer = 1;
				g_774654 = 1;
			}
			t = fcn_005373e0(0x4d5940, 0x7d6c6);
		}
	}
	flags = *(unsigned char*) (a0 + 0x7c) & 1;
	if (flags && list[1] == 6 && !g_772ea8) {
		k = 0;
		sel = 0x2d;
		p = items;
		while (sel) {
			*p = 0;
			p++;
			sel--;
		}
		p = (int*) (a0 + 0x100);
		sel = 3;
		q = p;
		do {
			if (*q != -1) {
				count += 1;
			}
			q++;
			sel--;
		} while (sel);
		sel = *p;
		sel = *(int*) (fcn_00502cd0(0, 2, 7, 1, sel) + 0x24);
		d2_SetForm(win, 1);
		io_AppendText(0x6811b0);
		if (sel) {
			sel = gm_SearchTable67(*(unsigned int*) (sel + 0xb4));
			r = 0;
			q = (int*) (a0 + 0xc0);
			i = 0x10;
			do {
				if (*q != -1) {
					r += 1;
				}
				q++;
				i--;
			} while (i);
			if (sel) {
				io_AppendText(0x113d, count, 0xc10, sel, *list, r);
			}
		}
		fcn_00507e30(names, 3);
		t = (int) gm_GetEntitySkill(list, 3);
		if (5 <= t) {
			t = 4;
		}
		if (*(int*) (a0 + 0x110)) {
			io_AppendText(0x113e, t + 0x1128);
		} else {
			io_AppendText(0x113f);
		}
		fcn_004d5490(0x10, 0x96, 0);
		i = 3;
		do {
			if (*p != -1) {
				sel = gm_FindRecordById(*p);
				if (sel) {
					fcn_0050de80((char*) sel, items);
					sel = 0;
					if (1 <= items[0]) {
						do {
							fcn_0050bb50(ids[sel], g_773d75);
							sel++;
						} while (sel < items[0]);
					}
				}
			}
			p++;
			i--;
		} while (i);
		d2_SetForm(win, 2);
		io_AppendText(0x6811b0);
		v = (int) gm_GetEntitySkill(list, 3);
		t = io_AppendText(0x1141, (int) gm_GetEntitySkill(list, 3));
		sel = fcn_00472250(win, 2, t);
		row = fcn_00472250(win, 2, t + 1);
		r = fcn_00472250(win, 2, t + 2);
		n = 0;
		q = (int*) (a0 + 0x80);
		i = 0x10;
		do {
			if (*q != -1) {
				n += 1;
			}
			q++;
			i--;
		} while (i);
		t = fcn_00472250(win, 2, t + 3);
		if (!n) {
			fcn_00472170(t, 0);
		}
		k = fcn_005373e0(0x4d5940, 0x7d6c6);
		while (k) {
			if (g_14ce8e0) {
				g_774654 = 1;
				answer = 0;
			}
			if (g_100f1dc != -1) {
				if (*(int*) 0x67d370 != t) {
					if (*(int*) 0x67d370 != sel && *(int*) 0x67d370 != row && *(int*) 0x67d370 != r) {
						goto label_4d601e;
					}
					v = 0;
					count = 0;
					if (*(int*) 0x67d370 != sel) {
						if (*(int*) 0x67d370 == row) {
							v = 0x32;
							goto label_4d5f52;
						}
						if (*(int*) 0x67d370 == r) {
							v = 0x5a;
							count = v;
						}
					} else {
						v = 10;
label_4d5f52:
						count = v;
					}
					if ((gm_RandomMod(0x5a) & 0xffff) + 10 <= v) {
						rec = (int) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0x10c));
						io_FormatTextBuffer(text, 0x1142);
						fcn_004e6eb0(text, 0);
						g_774654 = 1;
						answer = 0;
						g_772ea8 = 1;
						g_772eac = fcn_004d52a0(*(int*) 0x772eb4, rec, list, names, (float) count * *(float*) 0x6640e8);
						goto label_4d601e;
					}
					io_FormatTextBuffer(str, 0x1143);
					fcn_004e6eb0(str, 0);
				}
				g_774654 = 1;
				answer = 1;
			}
label_4d601e:
			k = fcn_005373e0(0x4d5940, 0x7d6c6);
		}
		goto label_4d6146;
	}
	if (!flags || list[1] == 6 || g_772ea8) {
		goto label_4d6146;
	}
	q = (int*) (a0 + 0x80);
	i = 0x10;
	sel = 0;
	do {
		if (*q != -1) {
			sel += 1;
		}
		q++;
		i--;
	} while (i);
	if (sel && (int) (gm_RandomMod(5) & 0xffff) <= *(int*) (a0 + 0x110)) {
		goto label_4d6146;
	}
	t = 0;
	count = 0;
	v = gm_RandomMod(4) & 0xffff;
	if (v) {
		if (v == 1) {
			t = 0x5a;
			goto label_4d60c3;
		}
		if (v >= 2) {
			t = 0x32;
			count = t;
		}
	} else {
		t = 10;
label_4d60c3:
		count = t;
	}
	if ((gm_RandomMod(0x5a) & 0xffff) + 10 <= t) {
		rec = (int) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0x10c));
		answer = 0;
		g_772ea8 = 1;
		g_772eac = fcn_004d52a0(*(int*) 0x772eb4, rec, list, names, (float) count * *(float*) 0x6640e8);
	} else {
		g_772eac = -1;
		answer = 1;
	}
label_4d6146:
	if (win != -1) {
		fcn_00471e30(win);
	}
	return answer;
}
