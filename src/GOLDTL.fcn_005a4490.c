extern char* g_772500;
extern char* g_77255c;
extern int g_772514;
extern int g_774654;
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern char g_8680b4[];
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_14ab658;
extern int g_14ab65c;
extern char g_6811b0[];

struct loan_offer {
	int image;
	int text;
	char* line;
};

int __cdecl fcn_0050d5d0(int, char*, char**);
int __cdecl fcn_004693b0(int, ...);
void __cdecl fcn_00469510(int);
void __cdecl fcn_0046b2b0(int);
int __cdecl fcn_0046f100(int, int, int, int, int, int);
void __cdecl fcn_0046f280(int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_00519190();
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_00533a60(int, int, int*, int, ...);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_005a4090(char*);
void __cdecl fcn_005a4360(char*, char*);

/* Inferred name and source home; the native registry selects this callback. */
/* ADDRESS: GOLDTL 0x005a4490 */
void __cdecl fcn_005a4490(char* p)
{
	struct loan_offer rows[9];
	char* lines[9];
	int sel[2];
	int w;
	int h;
	int i;
	int n;
	int count;
	int prev;
	int first;
	int second;
	int refresh;
	int dialog;
	int index;
	int y;
	int slot;
	int arg;
	char* line;

	prev = -1;
	first = -1;
	second = -1;
	refresh = 1;
	for (i = 0; i < 9; i++) {
		rows[i].image = -1;
		rows[i].text = -1;
		rows[i].line = 0;
	}
	dialog = fcn_00470820(0, 0, "locations\\geldleihe\\geldleihe_kreditaufnehmen");
	fcn_00471b60(dialog);
	fcn_004727a0(dialog, 0);
	arg = g_772514 * 0x3cc;
	*(int*) (arg + 0x10162e8) = 0x18;
	*(int*) (arg + 0x10162ec) = 0x18;
	*(int*) (arg + 0x10162f0) = 0x18;
	*(int*) (arg + 0x10162f4) = 0x18;
	fcn_004727a0(dialog, 1);
	fcn_00519190(0x18c9, *(unsigned short*) (g_8680b4 + g_773d75 * 0x2f4) * 2 + 0x9a8);
	fcn_00473a90(0, 0);
	while (fcn_005373e0(fcn_005a4490, 0x677c7) != 0) {
		if (refresh) {
			for (i = 0; i < 9; i++) {
				if (rows[i].image != -1) {
					fcn_0046f280(rows[i].image);
					fcn_0046b2b0(rows[i].text);
					rows[i].image = -1;
					rows[i].text = -1;
					rows[i].line = 0;
				}
			}
			n = fcn_0050d5d0(g_774970, 0, lines);
			count = fcn_0050d5d0(g_774970, p, lines);
			fcn_004727a0(dialog, 4);
			fcn_00519190(g_6811b0);
			if (count >= 9) {
				fcn_00519190(0x18cb);
				refresh = 1;
			} else if (count >= 3) {
				fcn_00519190(0x18cc);
				refresh = 1;
			} else {
				if (count != 0) {
					fcn_00519190(0x18ca, *(unsigned short*) (p + 0x27), p, count, n);
				} else {
					fcn_00519190(0x18cd, *(unsigned short*) (p + 0x27), p);
				}
				refresh = 0;
			}
			fcn_004727a0(dialog, 3);
			fcn_00519190(g_6811b0);
			if (refresh) {
				fcn_00533a60(g_772514, 0, sel, 1, g_14ab65c);
				first = -1;
				second = sel[0];
			} else {
				fcn_00533a60(g_772514, 0, sel, 2, g_14ab658);
				first = sel[0];
				second = sel[1];
			}
			index = 0;
			h = *(short*) (g_772500 + 0x269da);
			w = *(short*) (g_772500 + 0x269d8);
			if (count >= 1) {
				y = 0;
				for (i = 0; i < count; i++) {
					fcn_004727a0(dialog, 2);
					rows[i].text = fcn_0046f740((*(int*) (g_77255c + 0xc) - w) >> 1, y, 0x75a, g_772514);
					rows[i].image = fcn_0046f100((*(int*) (g_77255c + 0xc) - w) >> 1, y, w, h, 0x10, g_772514);
					line = lines[index];
					rows[i].line = line;
					*(int*) (rows[i].image * 0x3cc + 0x10161cc) = 0x56;
					*(int*) (rows[i].image * 0x3cc + 0x1015f58) = 0x10;
					fcn_00519190(0x18d6, *(unsigned int*) (line + 0xb4), *(unsigned int*) (line + 0xc0), line + 0xc4);
					index++;
					y += h + 8;
				}
			}
			if (prev != -1) {
				fcn_00469510(prev);
				prev = -1;
			}
			if (count == 1) {
				prev = fcn_004693b0(1, rows[0].image);
			} else if (count == 2) {
				prev = fcn_004693b0(2, rows[0].image, rows[1].image);
			} else if (count == 3) {
				prev = fcn_004693b0(3, rows[0].image, rows[1].image, rows[2].image);
			}
			slot = prev;
		}
		refresh = 0;
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (second != -1) {
			arg = count >= 1 && *(int*) (slot * 0x8c + 0x102cbc8) != -1;
			fcn_00472640(second, arg);
		}
		if (g_100f1dc != -1 && g_100f1dc == 2) {
			if (g_67d370 != first || first == -1) {
				if (g_67d370 == second && second != -1) {
					fcn_00471af0(dialog, 0);
					fcn_005a4360(p, rows[*(int*) (slot * 0x8c + 0x102cbc8)].line);
					refresh = 1;
					fcn_00471af0(dialog, 1);
				}
			} else {
				fcn_00471af0(dialog, 0);
				fcn_005a4090(p);
				fcn_00471af0(dialog, 1);
				refresh = 1;
			}
		}
	}
	fcn_00471e30(dialog);
	if (slot != -1) {
		fcn_00469510(slot);
	}
	return fcn_00532ef0();
}
