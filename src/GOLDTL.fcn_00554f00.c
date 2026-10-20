extern char g_7f4ca0[];
extern char g_868080[];
extern char g_7f4c00[];
extern char g_6a5e78[];
extern char g_6a5e60[];
extern char g_6a5e40[];
extern char g_6a5e24[];
extern char g_6a5e10[];
extern char g_6a5e00[];
extern char g_6a438c[];
extern char g_6a5de0[];
extern char g_6a5dcc[];
extern char g_6a5da8[];
extern char g_6a5d84[];
extern char g_6a5d60[];
extern char g_6a5d3c[];
extern char g_6a5d20[];
extern char g_6a5d04[];
extern char g_6a5ce8[];
extern char g_6a5ccc[];
extern char g_67d908[];
extern unsigned short g_774970;
extern char g_774964;
extern char g_7749e8;
extern int g_7749e4;
extern unsigned char g_773d75;
extern int g_100f884;
extern int g_100f1dc;

int __cdecl fcn_00500cb0(char*, char*);
char* __cdecl fcn_00508e40(int);
void __cdecl fcn_00545670(char*, int, int, char*, int);
void __cdecl fcn_00545780(char*);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(int, int, int, char*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c30a0(int, int, char*, int, int);
void __cdecl fcn_00519190(int, ...);

/* ADDRESS: GOLDTL 0x00554f00 */
void __cdecl fcn_00554f00(char* a0)
{
	char* rec;
	char* h;
	char* p;
	char* s;
	char* name;
	unsigned short w;
	int st;
	unsigned char c;

	rec = g_7f4ca0 + *(unsigned short*) (a0 + 8) * 0x21c;
	if (g_774970 != *(unsigned short*) (a0 + 8)) {
		return;
	}
	if (g_774964 == 0) {
		return;
	}
	name = a0 + 0x52;
	if (fcn_00500cb0(name, g_7f4c00) == 1) {
		return;
	}
	p = fcn_00508e40(*(int*) (a0 + 0xb0));
	st = *(int*) (a0 + 0x70);
	if (st == -2 || st == -1 || *(unsigned short*) rec == 0xffff || p == 0) {
		if (*(int*) (a0 + 0x74) != 0) {
			fcn_00545780(a0);
		}
		fcn_00546190(a0);
		return;
	}
	if (st == 0) {
		h = *(char**) (a0 + 0x74);
		if (h == 0) {
			if (p == rec) {
				fcn_00545670(a0, 0, 0, g_6a5e78, 0x5fd);
			} else {
				fcn_00545670(a0, 0, 0, g_6a5e60, 0x5fe);
			}
		}
		h = *(char**) (a0 + 0x74);
		if (h == 0) {
			fcn_00546190(a0);
			return;
		}
		fcn_00471b60(*(int*) (h + 8));
		fcn_004727a0(*(int*) (h + 8), 1);
		if (p != rec) {
			goto other_record;
		}
		if (*(int*) (a0 + 0xb4) == 0) {
			fcn_004c4510(p, *(int*) (p + 4));
			fcn_004c4570(1, 1, 0xd, a0 + 0xac);
			fcn_004c5360();
			*(int*) (a0 + 0xb4) = 1;
		}
		c = *(unsigned char*) (a0 + 0xac);
		if (c == 9) {
			fcn_00519190(0x42a3, name);
		} else if (c == 8) {
			fcn_00519190(0x42a1, name);
		} else if (c == 7) {
			fcn_00519190(0x429f, name);
		} else if (c == 2) {
			fcn_00519190(0x1618, g_868080 + g_773d75 * 0x2f4, name, *(unsigned short*) p, ((*(char*) (p + 9) != 0) ? 0xa : 0) + 0x116);
		} else {
			fcn_00519190(0x1617, g_868080 + g_773d75 * 0x2f4, name, *(unsigned short*) p, (int) c + ((*(char*) (p + 9) != 0) ? 0x11e : 0x114));
		}
		c = *(unsigned char*) (a0 + 0xac);
		if (c == 2) {
			fcn_004c30a0(-7, 0, g_6a5e40, 0, 0x64);
			fcn_004c30a0(-8, 0, g_6a5e24, 0, 0xfa);
			fcn_004c30a0(-8, 0, (*(char*) (p + 9) != 0) ? g_6a5e00 : g_6a5e10, (int) c, 0x64);
			fcn_004c30a0(-7, 0, g_67d908, -1, 0);
			goto tail;
		}
		if (c <= 3) {
			s = g_6a5e40;
		} else if (c < 6) {
			s = g_6a5de0;
		} else {
			s = g_6a438c;
		}
		fcn_004c30a0(-7, 0, s, 0, 0x64);
		if (c < 7) {
			fcn_004c30a0(-8, 0, g_6a5dcc, 0, 0xfa);
			fcn_004c30a0(-8, 0, (*(char*) (p + 9) != 0) ? g_6a5e00 : g_6a5e10, (int) c, 0x64);
		} else if (c == 7) {
			fcn_004c30a0(-7, 0, g_6a5da8, -1, 0x64);
		} else if (c == 8) {
			fcn_004c30a0(-7, 0, g_6a5ce8, -1, 0x64);
		} else if (c == 9) {
			fcn_004c30a0(-7, 0, g_6a5ccc, -1, 0x64);
		}
		fcn_004c30a0(-7, 0, g_67d908, -1, 0);
		goto tail;
	}
	if (st == 1) {
		h = *(char**) (a0 + 0x74);
		if (h == 0) {
			*(int*) (a0 + 0x70) = 0;
			return;
		}
		if (g_100f884 != *(int*) (h + 8) && g_7749e8 == 0) {
			return;
		}
		if (g_100f1dc == 2) {
			fcn_00545780(a0);
			fcn_00546190(a0);
			return;
		}
		if (g_7749e8 == 0) {
			return;
		}
		if (g_7749e4 != (int) h) {
			return;
		}
		g_7749e8 = 0;
		fcn_00545780(a0);
		fcn_00546190(a0);
		return;
	}
	return;

other_record:
	c = *(unsigned char*) (a0 + 0xac);
	w = *(unsigned short*) p;
	if (c == 9) {
		fcn_00519190(0x42a4, (int) w, ((*(char*) (p + 9) != 0) ? 0xa : 0) + 0x11d, (int) w);
	} else if (c == 8) {
		fcn_00519190(0x42a2, (int) w, ((*(char*) (p + 9) != 0) ? 0xa : 0) + 0x11c, (int) w);
	} else if (c == 7) {
		fcn_00519190(0x42a0, (int) w, ((*(char*) (p + 9) != 0) ? 0xa : 0) + 0x11b, (int) w);
	} else if (c == 2) {
		fcn_00519190(0x161b, (int) w);
	} else {
		fcn_00519190(0x161a, (int) w, (int) w, ((*(char*) (p + 9) != 0) ? 0xa : 0) + 0x114, (int) w);
	}
	c = *(unsigned char*) (a0 + 0xac);
	if (c == 2) {
		fcn_004c30a0(-8, 0, g_6a5d3c, 0, 0x64);
	} else if (c < 7) {
		fcn_004c30a0(-8, 0, g_6a5d20, 0, 0x64);
		fcn_004c30a0(-8, 0, (*(char*) (p + 9) != 0) ? g_6a5e00 : g_6a5e10, (int) c, 0x64);
	} else if (c == 7) {
		fcn_004c30a0(-7, 0, g_6a5d04, -1, 0x64);
	} else if (c == 8) {
		fcn_004c30a0(-7, 0, g_6a5ce8, -1, 0x64);
	} else if (c == 9) {
		fcn_004c30a0(-7, 0, g_6a5ccc, -1, 0x64);
	}

tail:
	fcn_004727a0(*(int*) (*(char**) (a0 + 0x74) + 8), 2);
	fcn_00519190(0x161c);
	*(int*) (a0 + 0x70) = 1;
}
