#include <string.h>

extern char* g_7746a4;
extern unsigned short g_7725c4;
extern int g_6a2bf0;
extern int g_6a2bf4;
extern int g_6a3764;
extern int g_6a376c;
extern int g_6a3768;
extern int g_6a3770;
extern int g_100f894;
extern int g_67d8d4;
extern int g_67d370;
extern char g_1015ea0[];
extern char g_100f8c0[];
extern int g_67d8cc;
extern char* g_773dfc;
extern char* g_7746ac;
extern char* g_7746b0;
extern char* g_7746b4;
extern char* g_7746c8;
extern char* g_7746c4;
extern char* g_7746cc;
extern unsigned short* g_7746bc;
extern char* g_7e2aa0;
extern int g_7e46ac;
extern int g_7725bc;
extern int g_7746dc;
extern int g_7746e4;
extern int g_7746e0;
extern int g_7746e8;
extern int g_774798;
extern int g_6b8010;
extern int g_774970;
extern char* g_item_def_table;
extern char s_6a2308[];
extern char s_6a2ff8[];
extern char s_6a3004[];
extern char s_6a300c[];
extern char s_68b3f8[];

char* __cdecl fcn_00443bf0(float a, float b, int flags, int mask);
void __cdecl fcn_0047a2b0(int handle);
int __cdecl fcn_00506380(int a0, char* a1, unsigned short* a2, int a3);
char* __cdecl fcn_00502cd0(int a0, int a1, int a2, int a3);
unsigned short* __cdecl fcn_00502850(void);
int __cdecl fcn_0065f220(char* a, char* b);
int __cdecl fcn_00517c00(int a1, int a2, int a3, char* a4);
int __cdecl fcn_0051af00(char* buf, int a, int b);
int __cdecl fcn_0064f170(char* a, char* b, unsigned int n);
int __cdecl fcn_0064d41a(char* buf, char* fmt, ...);

/* ADDRESS: GOLDTL 0x0052fde0 */
void __cdecl fcn_0052fde0(void)
{
	char key[0x60];
	char* cur;
	char* target;
	char* name;
	char* field;
	char* text;
	unsigned short* rec;
	unsigned int v;
	int i;
	int n;
	char c;
	int done_copy;
	int limit;

	g_7746a4 = 0;
	if (g_7725c4 != 0 && g_7725c4 <= 8) {
		g_7746a4 = 0;
		return;
	}
	g_6a2bf0 = *(short*) 0x14ce8c0;
	g_6a2bf4 = *(short*) 0x14ce8c2;
	if (g_6a2bf0 <= g_6a3764 || g_6a376c <= g_6a2bf0 || g_6a2bf4 <= g_6a3768 || (g_6a3770 <= g_6a2bf4 || g_100f894 != -1) || g_67d8d4 != -1 || ((g_7746a4 = fcn_00443bf0((float) g_6a2bf0, (float) g_6a2bf4, 0x20, 1)) == 0 && (g_7746a4 = fcn_00443bf0((float) g_6a2bf0, (float) g_6a2bf4, 0x40, 1)) == 0)) {
		if (g_67d370 == -1 || !(*(unsigned char*) (g_1015ea0 + g_67d370 * 0x2f4 + 0x1d0) & 0x40)) {
			g_100f8c0[0] = 0;
		}
		if (g_67d8cc != -1) {
			fcn_0047a2b0(g_67d8cc);
			g_67d8cc = -1;
			g_774798 = -1;
		}
		g_773dfc = 0;
		g_7746ac = 0;
		g_7746b0 = 0;
		g_7746b4 = 0;
		g_7725c4 = 0;
		return;
	}
	if (!(g_7e46ac & 0x10)) {
		return;
	}
	if (g_7725bc) {
		return;
	}
	if (!g_7746a4) {
		return;
	}
	if (g_100f894 != -1) {
		return;
	}
	if (g_67d8d4 != -1) {
		return;
	}
	target = 0;
	g_7746dc = 0;
	g_7746e4 = 0;
	g_7746e0 = 0;
	g_7746e8 = 0;
	g_7725c4 = 0;
	g_7746ac = 0;
	g_7746b0 = 0;
	g_7746b4 = 0;
	g_7746bc = 0;
	cur = g_7746a4;
	c = cur[0x4b];
	if (c == 1) {
		g_7746ac = *(char**) (cur + 0x204);
		if (g_7746c8) {
			target = g_7746c8;
		} else {
			target = 0;
		}
		g_7746dc = fcn_00506380((int) g_774970, target, (unsigned short*) g_7746ac, 0);
		if (g_7746ac) {
			v = (unsigned int) *(unsigned short*) g_7746ac;
			c = g_item_def_table[v * 0x41];
			if ((c != 6 && c != 2) || !(g_7746dc & 0x4000)) {
				fcn_0064d41a(g_100f8c0, (char*) 0x679060, *(unsigned int*) (v * 8 + 0x14a79c0));
				g_7725c4 = 0x16;
			} else {
				fcn_0064d41a(g_100f8c0, s_68b3f8, *(unsigned int*) (v * 8 + 0x14a79c0), (char*) 0x14a552c);
				g_7725c4 = 0xb;
			}
		}
		g_7746e4 = g_7746dc;
		target = g_7746b0;
	} else if (c == 2) {
		g_7746b0 = *(char**) (cur + 0x204);
		g_7746dc = fcn_00506380((int) g_774970, g_7746b0, 0, 0);
		if (g_7746b0 && !(g_7746b0[0x5a] & 1)) {
			if (g_7746b0[5]) {
				fcn_0064d41a(g_100f8c0, s_6a2308, *(unsigned int*) ((unsigned int) *(unsigned short*) g_7746b0 * 0x38 + 0x14a6558), g_7746b0 + 5);
				g_7746e0 = g_7746dc;
				target = g_7746b0;
			} else {
				field = *(char**) ((unsigned int) *(unsigned short*) g_7746b0 * 0x38 + 0x14a6558);
				i = 0;
				do {
					c = *field;
					field++;
					g_100f8c0[i] = c;
					i++;
				} while (c);
				target = g_7746b0;
				g_7746e0 = g_7746dc;
			}
		} else {
			target = g_7746b0;
			g_7746e0 = g_7746dc;
		}
	} else if (c == 3) {
		g_7746b4 = *(char**) (cur + 0x204);
		g_7746dc = fcn_00506380((int) g_774970, 0, (unsigned short*) g_7746b4, 0);
		if (g_7746b4 && (fcn_00517c00(*(unsigned short*) g_7746b4, 1, 4, g_100f8c0), *(char*) ((int) g_7746b4 + 0x165) == 0x1c) && ((*(unsigned char*) (g_7746b4 + 0x1b4) & 1) && ((g_7746dc & 0x800) && g_6b8010))) {
			fcn_0051af00(g_100f8c0, 0x414c, *(unsigned short*) g_7746b4);
			g_7725c4 = 0x2e;
		}
		g_7746e8 = g_7746dc;
		target = g_7746b0;
	} else {
		g_100f8c0[0] = 0;
		target = g_7746b0;
	}
	if (g_7e2aa0 && target == g_7e2aa0 && (g_7746e0 & 1) && !(target[0x5a] & 1)) {
		g_7725c4 = 0xb;
	}
	target = g_7746c8;
	if ((g_7746c8 || (target = g_7746c4, g_7746c4)) && cur) {
		if (!fcn_0064f170(cur, s_6a300c, 0xd)) {
			field = cur + 0x10;
			i = 0;
			do {
				c = *field;
				field++;
				key[i] = c;
				i++;
			} while (c);
			if (g_7746c8) {
				v = *(unsigned int*) (target + 0x5d);
				n = 6;
			} else {
				v = *(unsigned int*) (target + 0x5d);
				n = 2;
			}
			rec = (unsigned short*) fcn_00502cd0(v, 1, 4, n);
			while (rec) {
				name = g_item_def_table + *(unsigned short*) rec * 0x41;
				if (!fcn_0065f220(key, name + 1)) {
					g_7746bc = rec;
					break;
				}
				rec = fcn_00502850();
			}
			if (rec == 0) {
				if (g_7746c8) {
					rec = (unsigned short*) fcn_00502cd0(*(unsigned int*) (target + 0x5d), 1, 0, 0xfd);
					g_7746bc = rec;
				} else {
					rec = g_7746bc;
				}
			}
			if (rec) {
				g_7746dc = fcn_00506380((int) g_774970, target, rec, 0);
				if (g_7746dc & 1) {
					g_7725c4 = 0xb;
					if (*g_7746bc != 0xfd) {
						v = *(unsigned int*) ((unsigned int) *g_7746bc * 8 + 0x14a79c0);
						text = (char*) 0x14a552c;
					} else {
						text = (char*) 0x14a5530;
						if (g_7746cc) {
							v = *(unsigned int*) ((unsigned int) *(unsigned short*) g_7746cc * 8 + 0x14a79c0);
						} else {
							v = *(unsigned int*) ((unsigned int) *(unsigned short*) target * 0x38 + 0x14a6558);
						}
					}
					fcn_0064d41a(g_100f8c0, s_68b3f8, v, text);
				} else {
					g_7746bc = 0;
				}
			}
		}
		cur = g_7746a4;
	}
	n = 8;
	done_copy = 1;
	field = cur;
	name = s_6a3004;
	do {
		if (n == 0) {
			break;
		}
		n--;
		done_copy = (*field == *name);
		field++;
		name++;
	} while (done_copy);
	if (done_copy && (target = *(char**) (cur + 0x204)) != 0) {
		if (g_7746dc & 1) {
			g_7725c4 = 0xb;
			if (target[5]) {
				fcn_0064d41a(g_100f8c0, s_6a2ff8, *(unsigned int*) ((unsigned int) *(unsigned short*) target * 0x38 + 0x14a6558), target + 5, (char*) 0x14a552c);
				cur = g_7746a4;
				goto done;
			}
			v = *(unsigned int*) ((unsigned int) *(unsigned short*) target * 0x38 + 0x14a6558);
			name = s_68b3f8;
			text = (char*) 0x14a552c;
		} else {
			text = target + 5;
			if (!target[5]) {
				field = *(char**) ((unsigned int) *(unsigned short*) target * 0x38 + 0x14a6558);
				name = g_100f8c0;
				do {
					c = *field;
					field++;
					*name = c;
					name++;
				} while (c);
				cur = g_7746a4;
				goto done;
			}
			v = *(unsigned int*) ((unsigned int) *(unsigned short*) target * 0x38 + 0x14a6558);
			name = s_6a2308;
		}
		fcn_0064d41a(g_100f8c0, name, v, text);
		cur = g_7746a4;
	} else {
		field = (char*) 0x7e46c0;
		limit = 0x20;
		do {
			if (*(char**) field == cur) {
				name = field + 0x48;
				text = g_100f8c0;
				do {
					c = *name;
					name++;
					*text = c;
					text++;
				} while (c);
				g_7725c4 = *(unsigned short*) (field + 0x44);
			}
			field += 0xc8;
			limit--;
		} while (limit);
	}
done:
	if (g_67d8cc == -1) {
		g_773dfc = cur;
		return;
	}
	fcn_0047a2b0(g_67d8cc);
	g_67d8cc = -1;
	g_773dfc = g_7746a4;
	g_774798 = 0;
	return;
}
