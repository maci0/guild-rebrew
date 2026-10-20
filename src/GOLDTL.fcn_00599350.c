typedef struct {
	char pad0[4];
	unsigned char type;
	char pad5[3];
	int f08;
	int f0c;
	char pad10[0x18];
	int f28;
	int f2c;
	int f30;
	unsigned short f34;
	unsigned char f36;
	char pad37[0x21];
	int f58;
	int f5c;
	int f60;
	char pad64[0x1c];
	float pos[3];
	char pad8c[4];
	float rot[3];
	char name[0x3f];
	char pad_db[0x1d];
} Msg_599350;                        /* SIZE 0xf8 */

extern char* g_1015ea0;
extern unsigned char* g_868050;
extern unsigned short g_774970;
extern int g_772514;
extern int g_100f1dc;
extern int g_6aa0a8;
extern int g_67d370;
extern int g_774654;
extern int g_14ce8e0;
extern int g_7746f8;
extern unsigned char g_773d75;
extern char* g_773da8;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_7f4ca0[];
extern char* g_14a7898[];
extern char g_6b5c60[];

int __cdecl fcn_0057ec20(int);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);
void __cdecl fcn_00519190(int, ...);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl gm_GetBuildingTypeCategory(int);
unsigned int __cdecl fcn_00504f30(int, int);
int __cdecl d2_ShowTxt(int, int, char*, int);
int __cdecl fcn_0050d200(unsigned char*, int);
void __cdecl fcn_0050bc10(int, unsigned char, char*);
int __cdecl fcn_00472900(int, int);
void __cdecl fcn_0046f940(int, const char*);
int __cdecl fcn_0046f2c0(int, int);
char* __cdecl fcn_00507ab0(int);
int __cdecl fcn_00526070(int, int, int, int);
int __cdecl fcn_00526010(void*, int, int);
void __cdecl fcn_00471af0(int, int);
int __cdecl lc_GebaeudeAusrichten(int, char*);
void __cdecl fcn_00455350(char*, float*, float*);
void __cdecl fcn_00598740(float*, int);
char* __cdecl strncpy(char*, const char*, unsigned int);
char* __cdecl strcpy(char*, const char*);
int __cdecl fcn_004c5530(char*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x00599350 */
void __cdecl fcn_00599350(void)
{
	char path[0x104];
	char buf[0x80];
	Msg_599350 msg;
	int ids[10];
	int flag;
	int count;
	int i;
	int ida;
	int idb;
	int idc;
	int hwnd;
	int prevIdx;
	int off;
	char* p;
	char* mode;
	int prev;
	int id;
	int idx;
	int txt;
	char* obj;
	unsigned char v;
	unsigned int avail;

	prevIdx = -1;
	prev = -1;
	mode = 0;
	if (!fcn_0057ec20(0x40)) {
		return;
	}
	fcn_0057e880(0xe, 0, 0, 0);
	hwnd = fcn_00470820(0, 0, (char*) 0x6aa298);
	fcn_00471b60(hwnd);
	fcn_004727a0(hwnd, 0);
	i = g_772514 * 0x3cc;
	*(int*) (i + 0x10162e8) = 0x18;
	*(int*) (i + 0x10162ec) = 0x18;
	*(int*) (i + 0x10162f0) = 0x18;
	*(int*) (i + 0x10162f4) = 0x18;
	fcn_00533f40(0x20c, 0x168, g_772514, fcn_00472830(hwnd, 3), 0x5a, &ida, &idc, &idb);
	fcn_004727a0(hwnd, 1);
	fcn_00519190(0x17eb);
	fcn_004727a0(hwnd, 2);
	count = 0;
	flag = 0;
	for (i = 1; i < 10; i++) {
		if (i == 2 || i == 5) {
			continue;
		}
		if (i == 3) {
			v = *(unsigned char*) (g_774970 * 0x21c + 0x7f4e06);
			if (v != 0x0f && v != 0x0a) {
				flag = 1;
			}
		} else {
			if (i == 7) {
				v = *(unsigned char*) (g_774970 * 0x21c + 0x7f4e04);
				if (v < 0x34 || v > 0x39) {
					flag = 1;
				}
			}
		}
		id = fcn_0046f740((count % 2) * 0x46 + 0x30, (count / 2) * 0x5a + 0x0f, i + 0x6d4, g_772514);
		ids[i] = id;
		if (flag != 0) {
			*(int*) (g_1015ea0 + id * 0x2f4 + 0x4c) = 1;
			*(int*) (g_1015ea0 + id * 0x2f4 + 0x60) = 1;
		} else {
			*(int*) (g_1015ea0 + id * 0x2f4 + 0x5c) = 1;
			strcpy((char*) (g_1015ea0 + id * 0x2f4 + 0xcc), g_14a7898[i]);
			*(int*) (g_1015ea0 + id * 0x2f4 + 0x1d0) = 3;
			*(int*) (g_1015ea0 + id * 0x2f4 + 0x1cc) = 0x54;
			*(int*) (g_1015ea0 + id * 0x2f4 + 0x1e0) = -1;
		}
		count++;
		flag = 0;
	}
	*(int*) (g_1015ea0 + ids[g_6aa0a8] * 0x2f4 + 0x38) = 1;
	do {
		if (g_100f1dc >= 0x6d4 && g_100f1dc < 0x6de) {
			g_6aa0a8 = g_100f1dc - 0x6d4;
			*(int*) (g_1015ea0 + ids[g_6aa0a8] * 0x2f4 + 0x38) = 1;
			if (prev != -1) {
				*(int*) (g_1015ea0 + ids[prev] * 0x2f4 + 0x38) = 0;
			}
		}
		if (g_6aa0a8 != prev) {
			char* rec;

			fcn_004727a0(hwnd, 3);
			fcn_0046f2c0(g_772514, 1);
			mode = 0;
			if (g_6aa0a8 == 3) {
				g_7746f8 = 1;
				mode = fcn_00507ab0(1);
			} else {
				g_7746f8 = 0;
			}
			count = 0;
			off = 0;
			idx = 0;
			rec = (char*) 0x14a6558;
			do {
				if (gm_GetBuildingTypeCategory(idx) == g_6aa0a8) {
					p = (char*) g_868050 + off;
					avail = fcn_00504f30(idx, g_774970);
					if (avail == 1) {
						if (*p != 0x0f && *p != 6) {
							id = fcn_0046f740((count % 3) * 0x46 + 0x30, (count / 3) * 0x5a + 0x0f, idx + 0x427, g_772514);
							*(int*) (g_1015ea0 + id * 0x2f4 + 0x58) = 1;
							strcpy((char*) (g_1015ea0 + id * 0x2f4 + 0xcc), *(char**) rec);
							*(int*) (g_1015ea0 + id * 0x2f4 + 0x1d0) = 3;
							*(int*) (g_1015ea0 + id * 0x2f4 + 0x1cc) = 0x54;
							txt = fcn_0050d200((unsigned char*) (g_7f4ca0 + g_774970 * 0x21c), idx);
							fcn_0050bc10(txt, g_773d75, buf);
							txt = d2_ShowTxt((count % 3) * 0x46 + 2, (count / 3) * 0x5a + 0x3f, g_6b5c60, g_772514);
							fcn_00472900(txt, 0x54);
							fcn_0046f940(txt, buf);
							*(int*) (g_1015ea0 + txt * 0x2f4 + 0x18) = 0x8c;
							*(int*) (g_1015ea0 + txt * 0x2f4 + 0x6c) = 1;
							count++;
						}
					} else {
						if (avail == 2) {
							id = fcn_0046f740((count % 3) * 0x46 + 0x30, (count / 3) * 0x5a + 0x0f, 0x4fb, g_772514);
							*(char*) (g_1015ea0 + id * 0x2f4 + 0xcc) = g_6b5c60[0];
							*(int*) (g_1015ea0 + id * 0x2f4 + 0x1d0) = 3;
							*(int*) (g_1015ea0 + id * 0x2f4 + 0x1cc) = 0x54;
							count++;
						}
					}
				}
				rec += 0x38;
				off += 0x24d;
				idx++;
			} while (rec < (char*) 0x14a7898);
			prev = g_6aa0a8;
		}
		if (g_100f1dc >= 0x427 && g_100f1dc <= 0x47f) {
			i = g_100f1dc - 0x427;
			if (prevIdx != -1) {
				*(int*) (g_1015ea0 + prevIdx * 0x2f4 + 0x38) = 0;
				*(int*) (g_1015ea0 + prevIdx * 0x2f4 + 0x3c) = 0;
			}
			prevIdx = g_67d370;
			if (mode != 0) {
				txt = fcn_0050d200((unsigned char*) (g_7f4ca0 + g_774970 * 0x21c), i);
				if (!fcn_00526070((int) mode, *(int*) (mode + 0x14), txt, g_773d75)) {
					goto skip_place;
				}
			} else {
				txt = fcn_0050d200((unsigned char*) (g_7f4ca0 + g_774970 * 0x21c), i);
				if (!fcn_00526010(g_7f4ca0 + g_774970 * 0x21c, txt, g_773d75)) {
					goto skip_place;
				}
			}
			fcn_00471af0(hwnd, 0);
			obj = (char*) lc_GebaeudeAusrichten(i, path);
			if (obj == 0) {
				fcn_00471af0(hwnd, 1);
			} else {
				msg.f28 = g_7f4c00;
				msg.type = 0x0d;
				msg.f2c = g_7f4c04;
				msg.f36 = 2;
				msg.f30 = g_7f4c08;
				msg.f34 = (unsigned short) g_7f4c0c;
				id = *(int*) (g_7f4ca0 + g_774970 * 0x21c + 4);
				msg.f08 = id;
				msg.f0c = id;
				if (g_6aa0a8 == 3) {
					msg.f58 = *(int*) (g_773da8 + 4);
				} else {
					msg.f58 = id;
				}
				msg.f5c = i;
				msg.f60 = fcn_0050d200((unsigned char*) (g_7f4ca0 + g_774970 * 0x21c), i);
				fcn_00455350(obj, (float*) (obj + 0x4c), msg.pos);
				fcn_00598740(msg.rot, (int) obj);
				strncpy(msg.name, path, 0x3f);
				fcn_004c5530((char*) &msg);
				g_774654 = 1;
			}
		}
skip_place:
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_00599350, 0x657c7) != 0);
	if (hwnd != -1) {
		fcn_00471e30(hwnd);
	}
	g_7746f8 = 0;
	fcn_0057e880(0xe, 0, 1, 0);
}
