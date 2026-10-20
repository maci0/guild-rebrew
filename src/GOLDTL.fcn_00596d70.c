extern int g_772514;
extern unsigned int g_7746d8;
extern char g_773d75;
extern char* g_1015ea0;
extern char* g_868050;

/* Private layout views inferred from native accesses; they allocate no
 * storage and are visible only to this translation unit. */

// SIZE 0x38
typedef struct {
	int id;
	int f04;
	int x;
	int y;
	int icon;
	int icon2;
	int text1;
	int text2;
	int title;
	int obj;
	int f28;
	int f2c;
	int f30;
	int f34;
} DlgRow_596d70;

// SIZE 0xc
typedef struct {
	char pad0[4];
	int x;
	int y;
} DlgWin_596d70;

/* g_1038144 is the page index table; g_1015f40 the window pool. */
extern int g_1038144[];
extern char g_1015f40[];

int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl fcn_00466ee0(int, int, int, int, int);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00472900(int, int);
void __cdecl fcn_0046b2b0(int);
void __cdecl fcn_0046f280(int);
void __cdecl fcn_0046f940(int, char*);
int __cdecl d2_ShowTxt(int, int, char*, int);
float __cdecl fcn_0050bb50(int, int);
void __cdecl fcn_0050bc10(int, int, char*);
void* __cdecl fcn_005463a0(int, int, int, int, int);
void* __cdecl fcn_005462a0(void);
int __cdecl fcn_00471f80(int);
void __cdecl d2_SetElementValue(int, ...);
void __cdecl fcn_00469c40(int, int, int);
int __cdecl sprintf(char*, const char*, ...);

/* ADDRESS: GOLDTL 0x00596d70 */
void __cdecl fcn_00596d70(int a0, int a1, DlgRow_596d70* r, int makeIcon,
                          unsigned int flags, unsigned char* p)
{
	DlgWin_596d70* w;
	char text[0x20];
	char* obj;
	float f;
	int v;
	int n;

	fcn_004727a0(a0, a1);
	w = (DlgWin_596d70*) (g_1015f40 + g_1038144[a0 * 175 + a1] * 0x3cc);
	if (r->id != 0) {
		if (r->title == -1) {
			r->title = fcn_004677e0(r->x + 6, r->y, 0x30, 0, 100, 0x6a, 0x3d, g_772514);
		}
		if (r->icon == -1) {
			if (makeIcon) {
				v = 0x8a;
				if (g_7746d8 & 0x200) {
					v = 0xca;
				}
				r->icon = fcn_00466ee0(r->x + 0xf, r->y + 6, r->id + 0xdf, v, g_772514);
				fcn_00472900(r->icon, 0x54);
			} else {
				r->icon = fcn_0046f740(r->x + 0xf, r->y + 6, r->id + 0xdf, g_772514);
				*(int*) (g_1015ea0 + r->icon * 0x2f4 + 0x5c) = 1;
			}
		}
		if (r->icon2 == -1) {
			if (flags & 1) {
				r->icon2 = fcn_0046f740(r->x + 0xf, r->y + 0x3a, 0x747, g_772514);
			} else if (flags & 2) {
				r->icon2 = fcn_0046f740(r->x + 0xf, r->y + 0x3a, 0x746, g_772514);
			}
		}
		if (flags & 2) {
			if (*p == 0x47) {
				f = fcn_0050bb50(r->id, p[0x65]);
			} else if (*(g_868050 + *p * 0x24d) == '\n') {
				f = fcn_0050bb50(r->id, g_773d75) * 1.1;
			} else {
				f = fcn_0050bb50(r->id, g_773d75) * *(float*) (p + 0x49);
			}
			fcn_0050bc10((int) f, g_773d75, text);
			if (r->text1 == -1) {
				r->text1 = d2_ShowTxt(r->x + 0x10, r->y + 0x40, text, g_772514);
			} else {
				fcn_0046f940(r->text1, text);
			}
			*(int*) (g_1015ea0 + r->text1 * 0x2f4 + 0x18) = 0x2d;
			*(int*) (g_1015ea0 + r->text1 * 0x2f4 + 0x84) = 0x54;
			*(int*) (g_1015ea0 + r->text1 * 0x2f4 + 0x70) = 1;
		}
		if (flags & 1) {
			if (*p == 0x47) {
				f = fcn_0050bb50(r->id, p[0x65]);
			} else {
				f = fcn_0050bb50(r->id, g_773d75) * 0.9;
			}
			fcn_0050bc10((int) f, g_773d75, text);
			if (r->text2 == -1) {
				r->text2 = d2_ShowTxt(r->x + 0x10, r->y + 0x49, text, g_772514);
			} else {
				fcn_0046f940(r->text2, text);
			}
			*(int*) (g_1015ea0 + r->text2 * 0x2f4 + 0x18) = 0x2d;
			*(int*) (g_1015ea0 + r->text2 * 0x2f4 + 0x84) = 0x54;
			*(int*) (g_1015ea0 + r->text2 * 0x2f4 + 0x70) = 1;
		}
		obj = (char*) fcn_005463a0(2, 0, 4, 3, *(unsigned int*) (p + 1));
		while (obj != 0) {
			if (*(unsigned short*) (obj + 0xac) == r->id) {
				break;
			}
			obj = (char*) fcn_005462a0();
		}
		if (obj == 0) {
			obj = (char*) fcn_005463a0(2, 0, 3, 3, *(unsigned int*) (p + 1));
			while (obj != 0) {
				if (*(unsigned short*) (obj + 0xac) == r->id) {
					break;
				}
				obj = (char*) fcn_005462a0();
			}
		}
		if (obj != 0 && (*(int*) (obj + 0x14) != 0 || *(int*) (obj + 0x18) != 0)) {
			if (*obj == 4) {
				*(float*) (g_1015ea0 + r->icon * 0x2f4 + 0x1f4) =
					1.0 - *(float*) (obj + 0xb4) / *(float*) (obj + 0xb8);
			} else if (*obj == 3) {
				*(float*) (g_1015ea0 + r->icon * 0x2f4 + 0x1f4) =
					1.0 - *(int*) (obj + 0xb0) / *(float*) (obj + 0xb4);
			}
		} else if (r->icon != -1) {
			*(int*) (g_1015ea0 + r->icon * 0x2f4 + 0x1f4) = 0;
		}
		if (makeIcon) {
			v = fcn_00471f80(r->icon);
			if (v > r->f30) {
				v = r->f30;
			}
			n = r->f30;
			if (!(g_7746d8 & 0x200)) {
				n -= r->f2c;
			}
			if (n < 0) {
				n = 0;
			}
			d2_SetElementValue(r->icon, 0, n, v);
			if (r->f30) {
				*(int*) (g_1015ea0 + r->icon * 0x2f4 + 0x60) = 0;
			} else {
				*(int*) (g_1015ea0 + r->icon * 0x2f4 + 0x60) = 1;
			}
			v = fcn_00471f80(r->icon);
			if (v < 0) {
				v = 0;
			}
			d2_SetElementValue(r->title, 0, r->f34, r->f30 - v, r->f2c);
		} else {
			if (r->f30) {
				*(int*) (g_1015ea0 + r->icon * 0x2f4 + 0x60) = 0;
			} else {
				*(int*) (g_1015ea0 + r->icon * 0x2f4 + 0x60) = 1;
			}
			d2_SetElementValue(r->title, 0, r->f34, r->f30, r->f2c);
		}
		*(int*) (g_1015ea0 + r->icon * 0x2f4 + 0x1d0) = 0x22;
		*(int*) (g_1015ea0 + r->icon * 0x2f4 + 0x1dc) = 4;
		*(int*) (g_1015ea0 + r->icon * 0x2f4 + 0x1e0) = 0;
		sprintf(g_1015ea0 + r->icon * 0x2f4 + 0xcc, "%s~ %li %s",
				*(unsigned int*) (0x14a79c0 + r->id * 8), r->f30, (char*) 0x14b52c0);
		if (r->icon >= 0) {
			fcn_00469c40(w->x + r->x + 0xf, w->y + r->y + 6, r->icon);
		}
		if (r->icon2 >= 0) {
			fcn_00469c40(w->x + r->x + 0xf, w->y + r->y + 0x3a, r->icon2);
		}
		if (r->text1 >= 0) {
			fcn_00469c40(w->x + r->x + 0x12, w->y + r->y + 0x3f, r->text1);
		}
		if (r->text2 >= 0) {
			fcn_00469c40(w->x + r->x + 0x12, w->y + r->y + 0x49, r->text2);
		}
		if (r->title >= 0) {
			fcn_00469c40(w->x + r->x + 6, w->y + r->y, r->title);
		}
		if (r->obj >= 0) {
			fcn_00469c40(w->x + r->x + 0xf, w->y + r->y + 6,
					*(int*) (g_1015f40 + r->obj * 0x3cc + 0x27c));
		}
		return;
	}
	if (r->icon != -1) {
		fcn_0046b2b0(r->icon);
		r->icon = -1;
	}
	if (r->icon2 != -1) {
		fcn_0046b2b0(r->icon2);
		r->icon2 = -1;
	}
	if (r->text1 != -1) {
		fcn_0046b2b0(r->text1);
		r->text1 = -1;
	}
	if (r->text2 != -1) {
		fcn_0046b2b0(r->text2);
		r->text2 = -1;
	}
	if (r->title != -1) {
		fcn_0046b2b0(r->title);
		r->title = -1;
	}
	if (r->obj != -1) {
		fcn_0046f280(r->obj);
		r->obj = -1;
	}
}
