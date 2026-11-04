extern int g_772ea8;
extern int g_772eac;
extern int g_100f1dc;
#include "client_dialog_state.h"
extern int g_14ce8e0;
extern unsigned char g_773d75;
extern int g_774654;
extern double g_662908;
extern double g_6629f8;
extern double g_6640e8;
extern double g_6640f8;
extern double g_664108;
extern float g_664168;

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

/* Record buffer filled by fcn_0050de80: two counts, a per-entry value table,
 * the id table and the weight table. */
struct item_table {
	int count_a;
	int count_b;
	int values[16];
	unsigned short ids[16];
	int weights[16];
	int sum1;
	int sum2;
	int acc;
	int last;
};

/* Modal sub-dialog for picking the guard shift. The first block drives the
 * generic selection page, the second the concrete shift of one guard. */
/* ADDRESS: GOLDTL 0x004d5940 */
unsigned int __cdecl fcn_004d5940(int a0)
{
	char str[1024];
	char text[1024];
	struct item_table items;
	int total;
	int t;
	int win;
	unsigned int answer;
	int count;
	float v;
	int sel;
	int id;
	int rec;
	int k;
	int r;
	int n;
	int t4;
	int clicked;
	int* p;
	int i;

	answer = 1;
	count = 0;
	sel = 0;
	win = fcn_00470820(0, 0, (char*) 0x68be84);
	fcn_00471d80(win, 3);
	g_772ea8 = 0;
	id = (int) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0x14));
	rec = (int) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0x10c));
	k = fcn_004d5450(rec);
	d2_SetForm(win, 1);
	if (*(char*) (*(int*) 0x772e9c + 2) == 6) {
		if (*(unsigned char*) (a0 + 0x7c) & 2) {
			io_AppendText(0x1138, k + 0x1125, rec, *(unsigned short*) (*(int*) 0x772e98), id);
			d2_SetForm(win, 2);
			sel = io_AppendText(0x113a, *(unsigned short*) (*(int*) 0x772e98), id);
		} else if (*(unsigned char*) (a0 + 0x7c) & 1) {
			p = (int*) (a0 + 0x100);
			i = 3;
			do {
				if (*p != -1) {
					count += 1;
				}
				p++;
				i--;
			} while (i);
			v = gm_GetEntitySkill((char*) (*(int*) 0x772e9c), 3);
			io_AppendText(0x112e, rec, *(unsigned short*) (*(int*) 0x772e98));
			d2_SetForm(win, 2);
			io_AppendText(0x112f, count, 0xc10);
			if (v >= g_662908) {
				if (*(int*) (a0 + 0x110)) {
					io_AppendText(0x1134);
				} else {
					io_AppendText(0x1135);
				}
			}
			if (v >= g_6640f8) {
				t = fcn_00507e30((char*) (*(int*) 0x772e98), 3);
				t = (int) ((float) t * g_664168);
				if (t > 4) {
					t = 4;
				}
				io_AppendText(0x1131, (t < 0 ? 0 : t) + 0x1128);
			}
			if (*(char*) (*(int*) 0x772e98 + 9)) {
				sel = io_AppendText(0x1133, 0x1137);
			} else {
				sel = io_AppendText(0x1133, 0x1136);
			}
		} else if (*(unsigned char*) (a0 + 0x7c) & 4) {
			io_AppendText(0x113b, rec, *(unsigned short*) (*(int*) 0x772e98));
			d2_SetForm(win, 2);
			sel = io_AppendText(0x113c, *(unsigned short*) (*(int*) 0x772e98), id);
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
	if ((*(unsigned char*) (a0 + 0x7c) & 1) && !g_772ea8) {
		if (*(char*) (*(int*) 0x772e98 + 2) == 6) {
			items.count_a = 0;
			total = 0;
			p = &items.count_b;
			sel = 0x2d;
			while (sel) {
				*p = 0;
				p++;
				sel--;
			}
			p = (int*) (a0 + 0x100);
			i = 3;
			do {
				if (*p != -1) {
					count += 1;
				}
				p++;
				i--;
			} while (i);
			sel = *(int*) (a0 + 0x100);
			sel = *(int*) (fcn_00502cd0(0, 2, 7, 1, sel) + 0x24);
			d2_SetForm(win, 1);
			io_AppendText(0x6811b0);
			if (sel) {
				sel = gm_SearchTable67(*(unsigned int*) (sel + 0xb4));
				r = 0;
				p = (int*) (a0 + 0xc0);
				i = 0x10;
				do {
					if (*p != -1) {
						r += 1;
					}
					p++;
					i--;
				} while (i);
				if (sel) {
					io_AppendText(0x113d, count, 0xc10, sel, *(unsigned short*) (*(int*) 0x772e9c), r);
				}
			}
			t = fcn_00507e30((char*) (*(int*) 0x772e98), 3);
			t = (int) ((float) t * g_664168);
			if (t > 4) {
				t = 4;
			}
			if (*(int*) (a0 + 0x110)) {
				io_AppendText(0x113e, (t < 0 ? 0 : t) + 0x1128);
			} else {
				io_AppendText(0x113f);
			}
			fcn_004d5490(0x10, 0x96, 0);
			p = (int*) (a0 + 0x100);
			i = 3;
			do {
				if (*p != -1) {
					sel = gm_FindRecordById(*p);
					if (sel) {
						fcn_0050de80((char*) sel, (int*) &items);
						if (0 < items.count_b) {
							sel = 0;
							do {
								total = (int) (fcn_0050bb50(items.ids[sel], g_773d75) * (float) items.weights[sel] + (float) total);
								sel++;
							} while (sel < items.count_b);
						}
					}
				}
				p++;
				i--;
			} while (i);
			d2_SetForm(win, 2);
			io_AppendText(0x6811b0);
			t = io_AppendText(0x1141, (int) (total * g_6629f8), (int) (total * 0.5), (int) (total * g_664108));
			sel = fcn_00472250(win, 2, t);
			r = fcn_00472250(win, 2, t + 1);
			n = fcn_00472250(win, 2, t + 2);
			clicked = 0;
			p = (int*) (a0 + 0x80);
			i = 0x10;
			do {
				if (*p != -1) {
					clicked += 1;
				}
				p++;
				i--;
			} while (i);
			t4 = fcn_00472250(win, 2, t + 3);
			if (!clicked) {
				fcn_00472170(t4, 0);
			}
			t = fcn_005373e0(0x4d5940, 0x7d6c6);
			while (t) {
				if (g_14ce8e0) {
					g_774654 = 1;
					answer = 0;
				}
				if (g_100f1dc != -1) {
					clicked = *(int*) 0x67d370;
					if (clicked == t4) {
						g_774654 = 1;
						answer = 1;
					} else if (clicked == sel || clicked == r || clicked == n) {
						count = 0;
						if (clicked == sel) {
							count = 10;
						} else if (clicked == r) {
							count = 0x32;
						} else if (clicked == n) {
							count = 0x5a;
						}
						if ((gm_RandomMod(0x5a) & 0xffff) + 10 <= count) {
							rec = (int) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0x10c));
							io_FormatTextBuffer(text, 0x1142);
							fcn_004e6eb0(text, 0);
							g_774654 = 1;
							answer = 0;
							g_772ea8 = 1;
							g_772eac = fcn_004d52a0(*(int*) 0x772eb4, rec, (char*) (*(int*) 0x772e9c), (char*) (*(int*) 0x772e98), (float) count * g_6640e8);
						} else {
							io_FormatTextBuffer(str, 0x1143);
							fcn_004e6eb0(str, 0);
							g_774654 = 1;
							answer = 1;
						}
					}
				}
				t = fcn_005373e0(0x4d5940, 0x7d6c6);
			}
		}
		else {
			clicked = 0;
			p = (int*) (a0 + 0x80);
			i = 0x10;
			do {
				if (*p != -1) {
					clicked += 1;
				}
				p++;
				i--;
			} while (i);
			if (!clicked || (int) (gm_RandomMod(5) & 0xffff) > *(int*) (a0 + 0x110)) {
				count = 0;
				t = gm_RandomMod(4) & 0xffff;
				if (t == 0) {
					count = 10;
				} else if (t == 1) {
					count = 0x5a;
				} else if (t >= 2) {
					count = 0x32;
				}
				if ((gm_RandomMod(0x5a) & 0xffff) + 10 <= count) {
					rec = (int) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0x10c));
					answer = 0;
					g_772ea8 = 1;
					g_772eac = fcn_004d52a0(*(int*) 0x772eb4, rec, (char*) (*(int*) 0x772e9c), (char*) (*(int*) 0x772e98), (float) count * g_6640e8);
				} else {
					g_772eac = -1;
					answer = 1;
				}
			}
		}
	}
	if (win != -1) {
		fcn_00471e30(win);
	}
	return answer;
}
