
extern char* g_6b8014;
extern int g_1040490;
extern int g_1040494;
extern int g_10432a4;
extern int g_10421a0;
extern int g_10529c8;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern int g_14ce8cc;
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_774654;
extern char* g_7746a0;
extern char* g_7746a4;
extern int g_67d370;
extern int g_100f1dc;
extern char* g_14a5320[];
extern char g_7e1d00[];
extern int g_7e46ac;
extern int g_68bfb8;
extern char g_6a375c;
extern int g_6b7fdc;
extern int g_14b5e50;
extern int g_14b5e54;
extern int g_772514;

void __cdecl fcn_00533880(void);
void __cdecl fcn_005338a0(void);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_00438b40(char*, int*);
void __cdecl fcn_00438cb0(char*, int*);
void __cdecl fcn_00445f50(int, int, float, int);
int __cdecl sprintf(char*, const char*, ...);
char* __cdecl strcpy(char*, const char*);
int __cdecl fcn_005dfa40(char*, char*, char*);
int __cdecl vfs_Tfopen(char*, char*, int);
int __cdecl fcn_00521eb0(int, char*);
void __cdecl CloseVfsStream(int);
char* __cdecl fcn_0053e7a0(char*);
int __cdecl sprintf(char*, const char*, ...);
void __cdecl fcn_0066080a(char*);
int __cdecl fcn_0042dc90(char*);
void __cdecl fcn_005338d0(char*, char*, int);
char* __cdecl fcn_00442910(int, void*, void*, char*);
void __cdecl fcn_00412f10(char*, char*, int);
char __cdecl fcn_00442c00(char*, char);
int __cdecl fcn_004e4470(char*);
void __cdecl fcn_004e44f0(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl fcn_00471db0(int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_00438da0(float, float, float, float, int, int, int, int, int);
void __cdecl fcn_00533a60(int, int, int*, int, ...);
int __cdecl fcn_005373e0(void*, int);
char* __cdecl fcn_00443bf0(float, float, int, int);
int __cdecl fcn_0064f170(char*, char*, int);
void __cdecl fcn_0053eb60(int);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_0053e9a0(void);
int __cdecl fcn_0053dc20(void);
int __cdecl fcn_004130b0(char*, char*);
void __cdecl d3_DestroyObject(char*);
void __cdecl fcn_00412cf0(char*, float*, float*, int, int);

/* Local frame layout; the 0x8984-byte frame is mostly the city name table. */
/* ADDRESS: GOLDTL 0x0053ed60 */
int __cdecl fcn_0053ed60(int unused, int network)
{
	char path[0x105];
	char names[0x40][0x210];
	char* cities[0x40];
	int values[0x40];
	char hdr[0x38];
	char langName[0x100];
	char keybuf[0x100];
	char namebuf[0x100];
	float pos[4];
	float dir[3];
	char* obj;
	char* city;
	char* image;
	char* cur;
	char* sel;
	int win1;
	int win2;
	int ids[2];
	int count;
	int i;
	int n;
	int h;
	int idx;
	int result;
	int highlight;
	int prev;

	fcn_00533880();
	fcn_005338a0();
	fcn_004432d0(0, 0);
	fcn_00438b40(g_6b8014, (int*) (g_6b8014 + 0x5c));
	fcn_00438cb0(g_6b8014, (int*) (g_6b8014 + 0x90));
	fcn_00445f50(0, 0, 1.0f, 0);
	obj = 0;
	result = 0;
	highlight = -1;
	prev = 0;
	sel = 0;
	count = fcn_005dfa40((char*) 0x6a3778, network == 0 ? (char*) 0x6a41b8 : (char*) 0x6a41b0, path);
	for (i = 0; i < count; i++) {
		h = vfs_Tfopen(names[i], (char*) 0x6750e8, g_6b7fdc);
		if (h == 0) {
			return 0;
		}
		if (fcn_00521eb0(h, hdr) == 0) {
			CloseVfsStream(h);
			return 0;
		}
		CloseVfsStream(h);
		values[i] = (signed char) hdr[0x30] - (g_6a375c & 0xff);
		cities[i] = fcn_0053e7a0(hdr + 5);
		if (cities[i] != 0) {
			sprintf(keybuf, (char*) 0x6a22a8, hdr + 5);
			fcn_0066080a(keybuf);
			idx = fcn_0042dc90(keybuf);
			if (idx != -1) {
				strcpy(langName, g_14a5320[idx]);
			} else {
				strcpy(langName, hdr + 5);
			}
			sprintf(keybuf, (char*) 0x6a41a4, hdr + 5);
			strcpy(cities[i], keybuf);
			fcn_005338d0(keybuf, langName, 0);
		}
	}
	city = (char*) cities[4];
	sel = city;
	if (city != 0) {
		pos[0] = *(float*) (city + 0x4c);
		pos[1] = *(float*) (city + 0x50);
		pos[2] = *(float*) (city + 0x54);
		pos[3] = 0.0f;
		dir[0] = 0.0f;
		dir[1] = 0.0f;
		dir[2] = 0.0f;
		obj = fcn_00442910(0, pos, dir, (char*) 0x6a40a0);
		*(char*) (obj + 0x215) = *(char*) (obj + 0x215) | 1;
		*(char*) (obj + 0x216) = (*(char*) (obj + 0x216) & 0xfd) | 1;
		fcn_00412f10(obj, (char*) 0x6a4080, 1);
	}
	fcn_00442c00(city, 0);
	g_7e46ac = 0x12d6;
	g_68bfb8 = 0x12d6;
	fcn_004e44f0(fcn_004e4470((char*) 0x6a4024));
	win1 = fcn_00470820(0, 0, (char*) 0x6a3dd4);
	fcn_00471d80(win1, 3);
	fcn_00471db0(win1, 1);
	d2_SetForm(win1, 0);
	fcn_00519190(0x1abb);
	fcn_00438da0((float) g_1040494, (float) g_1040490, 0.0f, 0.0f, g_10529c8, g_10421a0, g_10432a4, g_1040494, g_1040490);
	win2 = fcn_00470820(0, 0, (char*) 0x6a4194);
	fcn_00471d80(win2, 3);
	fcn_00471db0(win2, 1);
	d2_SetForm(win2, 2);
	fcn_00533a60(g_772514, 0, ids, 2, g_14b5e50, g_14b5e54);
	while (fcn_005373e0((void*) fcn_0053ed60, 0x10d6) != 0) {
		image = fcn_00443bf0((float) g_14ce8c0, (float) g_14ce8c2, 0x60, 1);
		g_7746a4 = image;
		if (g_14ce8cc != 0) {
			g_7746a0 = image;
		} else if (g_14ce8e0 != 0 || g_14cf950 == 1) {
			g_774654 = 1;
		}
		cur = g_7746a0;
		if (cur != 0 && fcn_0064f170(cur, (char*) 0x6a418c, 6) == 0) {
			sel = cur;
		}
		if (sel != prev) {
			pos[0] = 0.0f;
			pos[1] = 0.0f;
			pos[2] = 0.0f;
			pos[3] = 0.0f;
			dir[0] = 0.0f;
			dir[1] = 0.0f;
			dir[2] = 0.0f;
			d2_SetForm(win2, 1);
			fcn_00519190(0x6811b0);
			pos[0] = pos[0] + *(float*) (sel + 0x4c);
			pos[1] = pos[1] + *(float*) (sel + 0x50);
			pos[2] = pos[2] + *(float*) (sel + 0x54);
			fcn_00412cf0(obj, pos, dir, 0x28, 0x20);
			for (i = 0; i < count; i++) {
				if (sel != cities[i]) {
					if (cities[i] != 0) {
						fcn_00442c00(cities[i], 1);
					}
					continue;
				}
				if (cities[i] != 0) {
					strcpy(g_7e1d00, cities[i] + 6);
					sprintf(keybuf, (char*) 0x6a4170, g_7e1d00);
					fcn_0066080a(keybuf);
					idx = fcn_0042dc90(keybuf);
					if (idx != -1) {
						d2_SetForm(win2, 1);
						fcn_00519190(idx);
						fcn_00519190(0x68b300);
						fcn_00519190(idx + 1);
					}
				}
				fcn_00442c00(cities[i], 0);
				highlight = values[i];
			}
			prev = sel;
		}
		if (g_100f1dc == 2) {
			if (g_67d370 == ids[1]) {
				fcn_00471af0(win2, 0);
				fcn_00471af0(win1, 0);
				fcn_0053eb60(highlight);
				fcn_00471af0(win2, 1);
				fcn_00471af0(win1, 1);
				if (g_100f1dc != 2) {
					goto not_checked;
				}
			}
			if (g_67d370 == ids[0]) {
				goto accepted;
			}
		}
not_checked:
		if (g_14cf950 != 0x1c) {
			continue;
		}
accepted:
		fcn_00471af0(win2, 0);
		fcn_00471af0(win1, 0);
		if (network == 0) {
			if (fcn_0053e9a0() != 0 && fcn_0053dc20() != 0) {
				g_774654 = 1;
				result = 1;
				fcn_00471af0(win2, 1);
			}
			fcn_00471af0(win2, 1);
			fcn_00471af0(win1, 1);
		} else {
			g_774654 = 1;
			result = 1;
		}
	}
	if (win2 != -1) {
		fcn_00471e30(win2);
	}
	if (win1 != -1) {
		fcn_00471e30(win1);
	}
	if (obj != 0) {
		fcn_004130b0(obj, (char*) 0x6a415c);
		d3_DestroyObject(obj);
	}
	for (i = 0; i < count; i++) {
		if (cities[i] != 0) {
			d3_DestroyObject(cities[i]);
		}
	}
	return result;
}
