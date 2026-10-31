extern int g_772514;
extern char* g_1015ea0;
extern int g_100f1dc;
extern int g_774654;
extern int g_14ce8e0;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, char*);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00472380(int, char*);
int __cdecl fcn_00471f80(int);
void __cdecl fcn_00476b60(void);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_005373e0(int, int);

/* ADDRESS: GOLDTL 0x0053d020 */
unsigned int __cdecl fcn_0053d020(int a0)
{
	int items[8];
	int sel;
	unsigned int changed;
	int win;
	int n;
	int i;
	int slot;
	int id;
	int w3;
	int w4;
	int v;
	int v2;
	int found;
	unsigned int r3;
	unsigned int r4;
	char* src;
	char* dst;
	char ch;

	sel = -1;
	changed = 0;
	win = fcn_00470820(0, 0, (char*) 0x6a3fc8);
	fcn_00471b60(win);
	d2_SetForm(win, 1);
	io_AppendText(0x1acf, (char*) 0x7e1d00);
	d2_SetForm(win, 2);
	n = (*(int*) (g_772514 * 0x3cc + 0x1015f4c) - 0x20) / 0x30;
	i = 0;
	do {
		slot = fcn_0046f740((i % n) * 0x30, (i / n) * 0x30, i + 0x59a, g_772514);
		items[i] = slot;
		v = slot * 0x2f4;
		i++;
		*(unsigned int*) (v + 0x58 + (int) g_1015ea0) = 1;
		*(unsigned int*) (v + 0x38 + (int) g_1015ea0) = 0;
		*(unsigned int*) (v + 0x3c + (int) g_1015ea0) = 0;
		*(unsigned int*) (v + 0x60 + (int) g_1015ea0) = 1;
	} while (i <= 7);
	i = 0;
	do {
		if (*(int*) 0x7e23e4 == i + 0x59a) {
			v = items[i] * 0x2f4;
			*(unsigned int*) (v + 0x4c + (int) g_1015ea0) = 1;
			*(unsigned int*) (v + 0x68 + (int) g_1015ea0) = 1;
			*(unsigned int*) (v + 0x60 + (int) g_1015ea0) = 0;
			*(unsigned int*) (v + 0x3c + (int) g_1015ea0) = 0;
		}
		i++;
	} while (i < 8);
	i = 0;
	do {
		if (*(int*) (g_1015ea0 + 0x4c + items[i] * 0x2f4) == 0) {
			sel = items[i];
			*(unsigned int*) (sel * 0x2f4 + 0x38 + (int) g_1015ea0) = 1;
			*(unsigned int*) (sel * 0x2f4 + 0x3c + (int) g_1015ea0) = 1;
			break;
		}
		i++;
	} while (i < 8);
	d2_SetForm(win, 3);
	r3 = fcn_00472250(win, 3, io_AppendText(0x489, (char*) 0x6a3fc0));
	d2_SetForm(win, 4);
	r4 = fcn_00472250(win, 4, io_AppendText(0x486, (char*) 0x6a3fc0));
	w3 = fcn_00472250(win, 0, 3);
	w4 = fcn_00472250(win, 0, 5);
	*(unsigned int*) (*(int*) (g_1015ea0 + 0x88 + w3 * 0x2f4) * 0x160 + 0x102d158) = 0xc;
	*(unsigned int*) (*(int*) (g_1015ea0 + 0x88 + w4 * 0x2f4) * 0x160 + 0x102d158) = 0xc;
	if (*(char*) 0x7e23ea) {
		fcn_00472380(w3, (char*) 0x7e23ea);
		fcn_00472380(w4, (char*) 0x7e240a);
		i = 0;
		do {
			if (*(int*) (g_1015ea0 + 8 + items[i] * 0x2f4) == *(int*) 0x7e23e4) {
				sel = items[i];
				*(unsigned int*) (sel * 0x2f4 + 0x38 + (int) g_1015ea0) = 1;
				*(unsigned int*) (sel * 0x2f4 + 0x3c + (int) g_1015ea0) = 1;
				break;
			}
			i++;
		} while (i < 8);
	}
	fcn_00476b60();
	id = fcn_005373e0(0x53d020, a0);
	while (id) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc == 2) {
			*(char*) 0x7e23e0 = 0;
			*(char*) 0x7e23e1 = 0;
			*(char*) 0x7e23e2 = 0x12;
			*(int*) 0x7e23e4 = *(int*) (g_1015ea0 + 8 + sel * 0x2f4);
			*(char*) 0x7e23e8 = (char) (fcn_00471f80(r3) + 'w');
			*(char*) 0x7e23e9 = (char) (fcn_00471f80(r4) + 'z');
			src = (char*) fcn_00471f80(w3);
			dst = (char*) 0x7e23ea;
			do {
				ch = *src;
				src++;
				*dst = ch;
				dst++;
			} while (ch);
			src = (char*) fcn_00471f80(w4);
			dst = (char*) 0x7e240a;
			do {
				ch = *src;
				src++;
				*dst = ch;
				dst++;
			} while (ch);
			g_774654 = 1;
			changed = 1;
		} else if (g_100f1dc >= 0x59a && g_100f1dc < 0x5a2) {
			i = 0;
			do {
				v2 = (int) g_1015ea0 + items[i] * 0x2f4;
				found = 0;
				if (v2 == *(int*) 0x100f1e4) {
					sel = items[i];
					found = 1;
				} else {
					*(unsigned int*) (v2 + 0x38) = 0;
					*(unsigned int*) (v2 + 0x3c) = 0;
					*(unsigned int*) (v2 + 0x60) = 1;
				}
				i++;
			} while (i < 8);
			if (!found) {
				*(unsigned int*) (sel * 0x2f4 + 0x38 + (int) g_1015ea0) = 1;
				*(unsigned int*) (sel * 0x2f4 + 0x3c + (int) g_1015ea0) = 1;
			}
		}
		id = fcn_005373e0(0x53d020, a0);
	}
	fcn_00471e30(win);
	return changed;
}
