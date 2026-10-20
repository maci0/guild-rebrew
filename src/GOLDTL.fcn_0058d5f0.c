extern char* g_868050;
extern char* g_99ec10;
extern char* g_1015ea0;
extern int g_772514;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;

int __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_00525fb0(int);
int __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl fcn_005462a0(void);
void* __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00533dc0(int, int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_0052a0c0(int, int);
void __cdecl fcn_00594340(void);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_0046f9b0(int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00595e20(int, int);
void __cdecl fcn_005963f0(int, int, int, int);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_0051af00(void*, int, ...);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_005305a0(void);
void __cdecl fcn_00526120(int, int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

typedef struct {
	int kind;
	int f4;
	int f8;
	char pad0c[0x18];
	int v23;
	int v24;
	int v25;
	unsigned short v26;
	char v27;
	char pad33[0x21];
	char v28;
	char pad55;
	unsigned short v29;
	char pad58[4];
	int v30;
	unsigned int handles[6];
	char pad78[0x80];
} Req_58d5f0;

/* ADDRESS: GOLDTL 0x0058d5f0 */
void __cdecl fcn_0058d5f0(unsigned char* a0)
{
	Req_58d5f0 req;
	unsigned int ids[4];
	int counts[4];
	int handles[4];
	char text[224];
	unsigned int list[8];
	unsigned char* p;
	unsigned char* vp;
	char* ents;
	int* q;
	int h;
	int i;
	int j;
	int n;
	int menu;
	int sel;
	int count;
	int screen;

	ids[2] = 0x227;
	handles[3] = fcn_00502cd0(*(unsigned int*) (a0 + 0x5d), 2, 6, 0, 0x2a);
	n = 2;
	ents = (char*) (g_868050 + (unsigned int) *a0 * 0x24d);
	if (*ents != 0x1f) {
		ids[0] = 0x225;
		ids[1] = 0x226;
		if ((unsigned char) ents[0x247] >= 2) {
			ids[2] = 0x227;
			n = 3;
		}
	} else {
		ids[0] = 0x293;
		ids[1] = 0x294;
		if ((unsigned char) ents[0x247] >= 2) {
			ids[2] = 0x295;
			n = 3;
		}
	}
	if (fcn_00525fb0((int) a0))
		return;
	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	h = fcn_005463a0(2, 0, 0x8c, 3, *(unsigned int*) (a0 + 1));
	while (h) {
		j = 0;
		do {
			if (*(unsigned short*) (h + 0xac) == ids[j / 4]) {
				q = (int*) (h + 0x8c);
				for (i = 0; i < 4; i++) {
					if (*q != -1)
						counts[j / 4]++;
					q++;
				}
			}
			j += 4;
		} while (j < 0xc);
		h = fcn_005462a0();
	}
	menu = (int) fcn_00470820(0, 0, "s_6a9750");
	ids[3] = menu;
	fcn_00471b60(menu);
	fcn_004727a0(menu, 0);
	fcn_00533dc0(g_772514, 0x70f, 0x741);
	fcn_004727a0(menu, 3);
	screen = (*ents != 0x1f) ? 0x4128 : 0x421e;
	fcn_00519190(screen);
	fcn_0052a0c0((int) a0, 0);
	fcn_00594340();
	fcn_00471b60(menu);
	fcn_004727a0(menu, 2);
	if (n) {
		i = *(int*) (0x1015f4c + g_772514 * 0x3cc) / 2 - 0x80;
		j = 0x19;
		for (count = 0; count < n; count++) {
			h = fcn_0046f740(i, j, (int) ids[count] + 0xdf, g_772514);
			vp = (unsigned char*) (g_1015ea0 + h * 0x2f4);
			*(int*) (vp + 0x5c) = 1;
			*(int*) (vp + 0x1d0) = 3;
			*(int*) (vp + 0x1dc) = 100;
			*(int*) (vp + 0x1e0) = 0x10;
			*(int*) (vp + 0x84) = 0x54;
			fcn_0046f9b0(h, *(int*) (0x14a79c0 + (int) ids[count] * 8));
			handles[count] = h;
			fcn_00472640(h, 1);
			j += 0x50;
		}
		menu = ids[3];
	}
	fcn_00473a90(0, 0);
	fcn_00595e20((int) a0, handles[3]);
	fcn_005963f0(menu, 1, 0, (int) a0);
	sel = fcn_005373e0(0x58d5f0, 0x677c7);
	while (sel) {
		fcn_00595e20((int) a0, handles[3]);
		fcn_005963f0(menu, 1, 0, (int) a0);
		counts[0] = 0;
		counts[1] = 0;
		counts[2] = 0;
		h = fcn_005463a0(2, 0, 0x8c, 3, *(unsigned int*) (a0 + 1));
		while (h) {
			j = 0;
			do {
				if (*(unsigned short*) (h + 0xac) == ids[j / 4]) {
					q = (int*) (h + 0x8c);
					for (i = 0; i < 4; i++) {
						if (*q != -1)
							counts[j / 4]++;
						q++;
					}
				}
				j += 4;
			} while (j < 0xc);
			h = fcn_005462a0();
		}
		fcn_004727a0(menu, 2);
		if (n) {
			for (i = 0; i < n; i++) {
				fcn_00472640(handles[i], 1);
				if (*ents != 0x1f) {
					h = ids[i] * 2 + 0x9a8;
					if (counts[i] == 1) {
						fcn_0051af00(text, 0x4129, 0x228);
					} else if (counts[i] > 1) {
						fcn_0051af00(text, 0x412a, counts[i], 0x228, h);
					} else {
						fcn_0051af00(text, 0x679060, h);
					}
				} else if (counts[i] == 1) {
					fcn_0051af00(text, 0x421f, 0x22d, ids[i] * 2 + 0x9a8);
				} else if (counts[i] >= 2) {
					fcn_0051af00(text, 0x4220, counts[i], 0x22d);
				} else {
					fcn_0051af00(text, 0x679060, ids[i] * 2 + 0x9a8);
				}
				fcn_0046f9b0(handles[i], text);
			}
		}
		if (*(int*) 0x100f1dc != -1) {
			for (sel = 0; sel < n; sel++) {
				if (handles[sel] == *(int*) 0x67d370)
					break;
			}
			if (sel < n) {
				req.kind = 0x8c;
				req.v27 = 1;
				req.f4 = *(unsigned int*) (*(unsigned short*) (a0 + 0x27) * 0x21c + 0x7f4ca4);
				req.f8 = *(unsigned int*) (a0 + 1);
				req.v23 = (int) 0x7f4c00;
				req.v24 = g_7f4c04;
				req.v25 = g_7f4c08;
				req.v29 = g_7f4c0c;
				req.v26 = (unsigned short) ids[sel];
				j = 0;
				p = (unsigned char*) 0x7f4ca4;
				do {
					i = j;
					if (j >= 4)
						break;
					if (p[0x184]) {
						list[j] = *(unsigned int*) p;
						j++;
					}
					p += 0x21c;
					i = j;
				} while ((int) p < 0x85a0a4);
				while (j <= 3) {
					list[j] = 0xffffffff;
					j += 2;
				}
				req.v30 = 0;
				if (i) {
					h = fcn_004c5530(&req);
					if (h != -1) {
						while (!fcn_004c4450(h)) {
							fcn_005373e0(0, 0x20007);
						}
					}
					*(int*) 0x7e46ac = 0x677c7;
					fcn_005305a0();
				} else {
					fcn_00526120(*(int*) 0x14b556c, 4);
					fcn_005305a0();
				}
				goto next;
			}
		} else if (*(int*) 0x14ce8e0) {
			*(int*) 0x774654 = 1;
		}
next:
		sel = fcn_005373e0(0x58d5f0, 0x677c7);
		menu = ids[3];
	}
	fcn_005305a0();
	fcn_0052a2d0();
	fcn_00471e30(menu);
	fcn_00532ef0();
}
