/*
 * Rebuild the trade-goods tooltip list for object a0: item name, weight,
 * quality bar and the "contains" product rows, then place the window.
 */

extern char* g_item_def_table; /* 0x0099ec10 */
extern int g_1040494;          /* 0x01040494 */
extern int g_772514;           /* 0x00772514 */
extern unsigned char g_773d75; /* 0x00773d75 */
extern int g_7746c4;           /* 0x007746c4 */
extern int g_7746c8;           /* 0x007746c8 */
extern int g_7e2aa0;           /* 0x007e2aa0 */

extern char s_6811b0[]; /* "$C" */
extern char s_6a9a28[]; /* "%s$N" */
extern char s_6a9a30[]; /* "%i %s$N" */
extern char s_6a9a38[]; /* "ToolTip\\ToolTip_Objekte_Handelsgut" */
extern char s_6a9a5c[]; /* "ToolTip\\ToolTip_Objekte_Waffen" */

int* __cdecl fcn_004ce590(int);
void __cdecl fcn_00469c40(int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0046f7e0(int, int, int, int, int);
int __cdecl io_AppendText(int, ...);
float __cdecl eval_ObjektPreis2Credits(int, int);
float __cdecl fcn_0050bb50(int, int, int);
int __cdecl fcn_0050c710(int, int, int);
int __cdecl fcn_0050dc90(int);
float __cdecl fcn_00510260(int, int, int*);

/* ADDRESS: GOLDTL 0x00590b80 */
int __cdecl fcn_00590b80(int a0)
{
	int arr[32];
	char* def;
	int* rec;
	int* ent;
	int win;
	int slot;
	int count;
	int i;
	int n;
	int item;
	char* p;
	unsigned short v;
	int val;
	float quality;

	rec = fcn_004ce590(a0);
	def = g_item_def_table + a0 * 0x41;
	if (rec != 0 && *rec != 0) {
		win = fcn_00470820(0, 0, s_6a9a5c);
	} else {
		win = fcn_00470820(0, 0, s_6a9a38);
	}
	fcn_00471b60(win);
	n = *(int*) (0x01038144 + win * 700);
	val = *(int*) (0x01015f4c + n * 0x3cc);
	if (*(int*) (0x01015f44 + n * 0x3cc) + val > g_1040494 - 0x10) {
		fcn_00469c40(g_1040494 - 0x10 - val,
				*(int*) (0x01015f48 + n * 0x3cc),
				*(int*) (0x010161bc + n * 0x3cc));
	}
	d2_SetForm(0, 2);
	fcn_0046f740(0, 0, a0 + 0xdf, g_772514);
	io_AppendText(a0 * 2 + 0x9a9);
	d2_SetForm(0, 1);
	io_AppendText(a0 * 2 + 0x9a8);
	d2_SetForm(0, 3);
	if (def[0x40] != 0) {
		io_AppendText(0x21, def[0x40]);
	} else {
		io_AppendText(0x1f, (int) fcn_0050bb50(a0, g_773d75,
				(int) eval_ObjektPreis2Credits(a0, 100)));
	}
	ent = (int*) g_7746c4;
	if (ent == 0) {
		ent = (int*) g_7746c8;
		if (ent == 0) {
			ent = (int*) g_7e2aa0;
		}
	}
	d2_SetForm(win, 4);
	if (ent == 0) {
		io_AppendText(0x20, *(int*) (def + 0x22));
	} else {
		fcn_0050c710((int) ent, 1, 1);
		p = (char*) fcn_0050dc90((int) ent);
		slot = 0;
		count = 0x7f4ca0;
		for (i = 0x300; i != 0; i--) {
			if (*(int*) (count + 0x16c) == (int) ent && count != (int) p) {
				arr[slot] = *(int*) (count + 4);
				slot++;
			}
			count += 0x21c;
		}
		quality = fcn_00510260((int) ent, slot, arr);
		p = (char*) fcn_0050dc90((int) ent);
		if (p == 0) {
			p = (char*) (0x7f4ca0 + *(unsigned short*) ((char*) ent + 0x27) * 0x21c);
		}
		io_AppendText(0x22, (int) ((double) *(unsigned int*) (def + 0x22)
				/ ((double) *(unsigned char*) (p + 0x81)
					* 0.000992063492063492 + quality)));
	}
	d2_SetForm(0, 4);
	io_AppendText(0x25);
	item = 0x28;
	p = def + 0x26;
	for (i = 4; i != 0; i--) {
		v = *(unsigned short*) p;
		val = *(unsigned short*) (p + 8);
		if (val != 0) {
			fcn_0046f7e0(0, item, val + 0xdf, g_772514, -2);
			io_AppendText((int) s_6a9a30, v, val * 2 + 0x9a8);
			item += 0x16;
		}
		p += 2;
	}
	d2_SetForm(0, 3);
	io_AppendText(0x26);
	slot = 0;
	for (i = 0; i < 0x309; i += 0x15) {
		p = (char*) (0x699059 + i);
		val = slot * 0x16 + 0x28;
		for (n = 10; n != 0; n--) {
			if (*(unsigned short*) p == a0 && a0 != 0x1cd) {
				fcn_0046f7e0(6, val,
						*(unsigned char*) (0x699058 + i) + 0x427,
						g_772514, -2);
				io_AppendText((int) s_6a9a28,
						*(unsigned char*) (0x699058 + i) * 0xe + 0x48e);
				slot++;
				val += 0x16;
			}
			p += 2;
		}
	}
	if (def[0] != 0x17 && def[0] != 0x25) {
		n = slot;
		goto done;
	}
	i = 0;
	if (a0 == 0x225 || a0 == 0x226 || a0 == 0x227) {
		arr[0] = 0x48;
		arr[1] = 0x49;
		arr[2] = 0x4a;
		i = 3;
	} else if (a0 == 0x293 || a0 == 0x294 || a0 == 0x295) {
		arr[0] = 0x4e;
		arr[1] = 0x4f;
		arr[2] = 0x50;
		i = 3;
	} else if (a0 == 0x1c1 || a0 == 0x1c2 || a0 == 0x1c3) {
		arr[0] = 0x18;
		arr[1] = 0x19;
		i = 2;
	} else if (a0 != 0x1c7) {
		if (a0 == 0x1c4 || a0 == 0x1c5 || a0 == 0x1c6
				|| a0 == 0x2af || a0 == 0x2b0) {
			arr[0] = 0x1e;
			i = 1;
		} else if ((0x1d0 <= a0 && a0 <= 0x1d2)
				|| (0x1bd <= a0 && a0 <= 0x1c0)) {
			arr[0] = 0x20;
			i = 1;
		} else if ((0x1b7 <= a0 && a0 <= 0x1b9)
				|| (0x1ca <= a0 && a0 <= 0x1cc)) {
			arr[0] = 0x1e;
			i = 1;
		} else if ((0x1cd <= a0 && a0 <= 0x1cf) || a0 == 0x1ba
				|| (0x1bb <= a0 && a0 <= 0x1bc)) {
			arr[0] = 0x1f;
			i = 1;
		}
	}
	n = slot;
	if (i > 0) {
		n = slot + i;
		val = slot * 0x16 + 0x28;
		for (count = 0; count < i; count++) {
			item = arr[count];
			fcn_0046f7e0(6, val, item + 0x427, g_772514, -2);
			io_AppendText((int) s_6a9a28, item * 0xe + 0x48e);
			val += 0x16;
		}
	}
	if ((a0 == 0x1c7
			|| (a0 != 0x1c1 && a0 != 0x1c2 && a0 != 0x1c3
				&& a0 != 0x1c4 && a0 != 0x1c5 && a0 != 0x1c6
				&& a0 != 0x2af && a0 != 0x2b0))
			&& (def[0] == 0x17 || def[0] == 0x25)) {
		fcn_0046f7e0(6, n * 0x16 + 0x28, 0x444, g_772514, -2);
		io_AppendText((int) s_6a9a28, 0x624);
		n++;
	}
done:
	if (n == 0) {
		io_AppendText((int) s_6811b0);
	}
	return win;
}
