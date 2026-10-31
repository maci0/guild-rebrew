

typedef struct {
	char f0;
	unsigned char kind;
	char pad2[0x16];
	int text;
	char pad1c[8];
} Law;
// SIZE 0x24

typedef struct {
	char pad0[0x228];
	int left;
	int right;
} Book;
// SIZE 0x230

extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;

Book *__cdecl fcn_00534c40(char *, char *, int, char *, char *);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
void __cdecl fcn_004f5110(char *, int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_004f4830(int, Law *);
void __cdecl fcn_005ce710(int, int);
void __cdecl fcn_005350d0(Book *);
int __cdecl fcn_005373e0(void *, int);
void __cdecl fcn_00534f30(Book *);
void __cdecl fcn_00532ef0(void);

void __cdecl fcn_005ce460(int cmd)
{
	int base;
	int first;
	int split;
	int col;
	Law law;
	int items[12];
	char buf[0x200];
	Book *w;
	int last;
	int title;
	int i;
	int n;
	int sel;

	switch (cmd) {
	case 0x111:
		w = fcn_00534c40("ob_GESETZBUCH_STRAFRECHT", "Buch", 2, "Buch\\Gesetzbuch", "Buch\\Gesetzbuch");
		first = 0x11;
		last = 0x1d;
		base = 0x1452;
		title = 0x13f8;
		split = 6;
		break;
	case 0x112:
		w = fcn_00534c40("ob_GESETZBUCH_STEUERN", "Buch", 2, "Buch\\Gesetzbuch", "Buch\\Gesetzbuch");
		first = 9;
		last = 0x11;
		base = 0x142a;
		title = 0x13f7;
		split = 4;
		break;
	case 0x113:
		w = fcn_00534c40("ob_GESETZBUCH_VERFASSUNG", "Buch", 2, "Buch\\Gesetzbuch", "Buch\\Gesetzbuch");
		first = 0;
		last = 9;
		base = 0x13fd;
		title = 0x13f6;
		split = 5;
		break;
	default:
		return;
	}
	d2_SetForm(w->left, 1);
	io_AppendText(title);
	d2_SetForm(w->left, 2);
	col = w->left;
	for (i = first, n = 0; i < last; i++, n++) {
		if (n == split) {
			d2_SetForm(w->right, 2);
			col = w->right;
		}
		fcn_004f5110(buf, i);
		items[n] = fcn_00472250(col, 2, io_AppendText("%it$1>%s$N$0>", buf));
	}
	d2_SetForm(w->left, 3);
	io_AppendText(0x1a38, 1);
	d2_SetForm(w->right, 3);
	io_AppendText(0x1a38, 2);
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			sel = -1;
			for (i = 0; i < 12; i++) {
				if (items[i] == g_67d370) {
					sel = i;
					break;
				}
			}
			if (sel != -1) {
				fcn_004f4830(sel + first, &law);
				switch (law.kind) {
				case 0:
					fcn_005ce710(base + sel * 5, law.text);
					break;
				case 1:
					fcn_005ce710(base + sel * 5, law.text + 0x13dd);
					break;
				case 2:
					fcn_005ce710(base + sel * 5, law.text + 0x13e6);
					break;
				case 3:
					fcn_005ce710(base + sel * 5, law.text + 0x13ec);
					break;
				}
			}
		}
		fcn_005350d0(w);
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_005ce460, 0x677c7) != 0);
	fcn_00534f30(w);
	fcn_00532ef0();
}
