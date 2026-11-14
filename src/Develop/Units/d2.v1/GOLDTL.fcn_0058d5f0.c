#include <string.h>
extern char* lpGebaeudePROT;
extern char* lpObjektePROT;
extern char* g_1015ea0;
extern int g_772514;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;
extern int g_100f1dc;
extern int g_14b556c;
extern int g_774654;
extern int g_7e46ac;

int __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_00525fb0(int);
int __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl he_fn_Handlung(void);
void* __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_00533dc0(int, int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_0052a0c0(int, int);
void __cdecl fcn_00594340(void);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_0046f9b0(int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00595e20(int, int);
void __cdecl fcn_005963f0(int, int, int, int);
int __cdecl fcn_005373e0(int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c4450(int);
void __cdecl sv_ClearObjectSelection(void);
void __cdecl fcn_00526120(int, int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

/* SIZE 0xf8 */
typedef struct {
	char pad0[4];
	unsigned char kind;	/* +0x04 */
	char pad5[3];
	unsigned int owner;	/* +0x08 */
	unsigned int self;	/* +0x0c */
	char pad10[0x18];
	int date0;		/* +0x28 */
	int date1;		/* +0x2c */
	int date2;		/* +0x30 */
	unsigned short date3;	/* +0x34 */
	unsigned char flag;	/* +0x36 */
	char pad37;
	unsigned int list[4];	/* +0x38 */
	char pad48[0x10];
	unsigned short good;	/* +0x58 */
	char pad5a[0x9e];
} Req_58d5f0;

/* ADDRESS: GOLDTL 0x0058d5f0 */
void __cdecl fcn_0058d5f0(unsigned char* a0)
{
	Req_58d5f0 req;
	unsigned int ids[4];
	int counts[4];
	int handles[4];
	char text[224];
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
	ents = (char*) (lpGebaeudePROT + (unsigned int) *a0 * 0x24d);
	if (*ents == 0x1f) {
		ids[0] = 0x293;
		ids[1] = 0x294;
		if ((unsigned char) ents[0x247] >= 2) {
			ids[2] = 0x295;
			n = 3;
		}
	} else {
		ids[0] = 0x225;
		ids[1] = 0x226;
		if ((unsigned char) ents[0x247] >= 2) {
			ids[2] = 0x227;
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
			if (*(unsigned short*) (h + 0xac) == *(unsigned int*) ((char*) ids + j)) {
				q = (int*) (h + 0x8c);
				for (i = 0; i < 4; i++) {
					if (*q != -1)
						(*(int*) ((char*) counts + j))++;
					q++;
				}
			}
			j += 4;
		} while (j < 0xc);
		h = he_fn_Handlung();
	}
	menu = (int) fcn_00470820(0, 0, "s_6a9750");
	ids[3] = menu;
	fcn_00471b60(menu);
	d2_SetForm(menu, 0);
	fcn_00533dc0(g_772514, 0x70f, 0x741);
	d2_SetForm(menu, 3);
	screen = (*ents != 0x1f) ? 0x4128 : 0x421e;
	io_AppendText(screen);
	fcn_0052a0c0((int) a0, 0);
	fcn_00594340();
	fcn_00471b60(menu);
	d2_SetForm(menu, 2);
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
	d2_SetOverlayAnimation(0, 0);
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
				if (*(unsigned short*) (h + 0xac) == *(unsigned int*) ((char*) ids + j)) {
					q = (int*) (h + 0x8c);
					for (i = 0; i < 4; i++) {
						if (*q != -1)
							(*(int*) ((char*) counts + j))++;
						q++;
					}
				}
				j += 4;
			} while (j < 0xc);
			h = he_fn_Handlung();
		}
		d2_SetForm(menu, 2);
		if (n) {
			for (i = 0; i < n; i++) {
				fcn_00472640(handles[i], 1);
				if (*ents != 0x1f) {
					h = ids[i] * 2 + 0x9a8;
					if (counts[i] == 1) {
						io_FormatTextBuffer(text, 0x4129, 0x228);
					} else if (counts[i] > 1) {
						io_FormatTextBuffer(text, 0x412a, counts[i], 0x228, h);
					} else {
						io_FormatTextBuffer(text, 0x679060, h);
					}
				} else if (counts[i] == 1) {
					io_FormatTextBuffer(text, 0x421f, 0x22d, ids[i] * 2 + 0x9a8);
				} else if (counts[i] >= 2) {
					io_FormatTextBuffer(text, 0x4220, counts[i], 0x22d);
				} else {
					io_FormatTextBuffer(text, 0x679060, ids[i] * 2 + 0x9a8);
				}
				fcn_0046f9b0(handles[i], text);
			}
		}
		if (g_100f1dc != -1) {
			for (sel = 0; sel < n; sel++) {
				if (handles[sel] == *(int*) 0x67d370)
					break;
			}
			if (sel < n) {
				memset(&req, 0, sizeof(req));
				req.kind = 0x8c;
				req.flag = 1;
				req.owner = *(unsigned int*) (*(unsigned short*) (a0 + 0x27) * 0x21c + 0x7f4ca4);
				req.self = *(unsigned int*) (a0 + 1);
				req.date0 = *(int*) 0x7f4c00;
				req.date1 = g_7f4c04;
				req.date2 = g_7f4c08;
				req.date3 = g_7f4c0c;
				req.good = (unsigned short) ids[sel];
				j = 0;
				p = (unsigned char*) 0x7f4ca4;
				do {
					i = j;
					if (j >= 4)
						break;
					if (p[0x184]) {
						req.list[j] = *(unsigned int*) p;
						j++;
					}
					p += 0x21c;
					i = j;
				} while ((int) p < 0x85a0a4);
				while (j <= 3) {
					req.list[j] = 0xffffffff;
					j += 2;
				}
				if (i) {
					h = fcn_004c5530(&req);
					if (h != -1) {
						while (!fcn_004c4450(h)) {
							fcn_005373e0(0, 0x20007);
						}
					}
					g_7e46ac = 0x677c7;
					sv_ClearObjectSelection();
				} else {
					fcn_00526120(g_14b556c, 4);
					sv_ClearObjectSelection();
				}
				goto next;
			}
		} else if (*(int*) 0x14ce8e0) {
			g_774654 = 1;
		}
next:
		sel = fcn_005373e0(0x58d5f0, 0x677c7);
		menu = ids[3];
	}
	sv_ClearObjectSelection();
	fcn_0052a2d0();
	fcn_00471e30(menu);
	fcn_00532ef0();
}
