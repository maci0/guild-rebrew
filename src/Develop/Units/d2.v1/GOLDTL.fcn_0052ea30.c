#include "client_types.h"
#include "Develop/Units/d2.v1/d2_gui.h"

extern int g_6a25b8;
extern int g_6a25bc;
extern int g_6a25c0;
extern int g_6a25c4[4];
extern int g_6a25d4;
extern int g_6a25d8;
extern int g_6a25e8;
extern int g_100f1dc;
extern int g_67d370;
extern int g_7e46ac;
extern int g_7746f0;
extern int g_772514;
extern unsigned short g_774970;
extern char* g_7e2aa0;
extern int* g_7e2a9c;
extern int g_7ea360;
extern char* lpObjektePROT;
extern char g_868060[];
extern Win_1015f40 g_1015f40[0x60];

extern float g_6628a8;
extern float g_662910;
extern float g_662b10;
extern double g_6640e8;
extern double g_662c38;

extern char g_6811b0[];
extern char g_6a2f24[];
extern char g_6a2f30[];
extern char g_6a2fec[];
extern char g_6a2fe4[];
extern char g_67d444[];

int __cdecl fcn_00508da0(char* a);
void __cdecl d2_SetForm(int h, int mode);
void __cdecl io_AppendText(char* fmt, ...);
void __cdecl fcn_005186c0(int id, int a, int b, char* out);
char* __cdecl fcn_005463a0(int a, int b, int c, int d, int e);
int __cdecl fcn_00500d20(void* a, void* b);
void __cdecl fcn_00500bb0(void* p, int a, int b, int c);
int __cdecl fcn_0046f740(int x, int y, int kind, int owner);
int __cdecl fcn_0046f7e0(int x, int y, int z, int owner, int flag);
void __cdecl fcn_0046b2b0(int element);
int __cdecl fcn_00529800(char* s, int* out);
float __cdecl fcn_004ff040(char* e);
int __cdecl fcn_0046f2c0(int win, int keep);
void __cdecl fcn_004bfe00(char* e);
char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);
char* __cdecl fcn_00502cd0(int a, int b, int c, ...);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_GetMsgField(int a, int b);
int __cdecl fcn_0064d41a(char* buf, char* fmt, ...);

/* ADDRESS: GOLDTL 0x0052ea30 */
void __cdecl fcn_0052ea30(void)
{
	char name[256];
	char buf[0x2c];
	int kinds[8];
	pos14_7f4c00 pos;
	int pct;
	int i;
	int k;
	int x;
	int y;
	unsigned short flags;
	char* e;
	char* s;
	char* p;
	unsigned char c;
	float ratio;
	int n;

	ratio = 0.0f;
	if (g_6a25b8 == -1) {
		return;
	}
	if (g_7e2aa0 == 0 || g_6a25c0 == -1 || g_6a25bc == -1) {
		goto no_header;
	}
	pct = fcn_00508da0(g_7e2aa0);
	d2_SetForm(g_6a25b8, 1);
	io_AppendText(g_6811b0);
	if (*g_7e2aa0 != 0x47) {
		fcn_005186c0(*(unsigned short*) (g_7e2aa0 + 0x27), 2, 1, name);
		if (g_7e2aa0[5] != 0) {
			io_AppendText(g_6a2f30, name, *g_7e2aa0 * 0xe + 0x48e, g_7e2aa0 + 5);
			goto header_done;
		}
		io_AppendText(g_6a2f24, name, *g_7e2aa0 * 0xe + 0x48e);
	} else {
		io_AppendText(g_6a2f24, (char*) 0x870, g_868060 + *(int*) (g_7e2aa0 + 0x65) * 0x2f4);
	}
header_done:
	d2_SetElementValue(g_6a25c0, 0, 100, pct);
	flags = *(unsigned short*) (g_7e2aa0 + 0x5a);
	if (flags & 4) {
		e = fcn_005463a0(2, 0, 0x1c, 3, *(int*) (g_7e2aa0 + 1));
		if (e == 0) {
			return;
		}
		n = fcn_00500d20(e + 0x44, e + 0xb8);
		ratio = (float) fcn_00500d20(e + 0x44, (char*) 0x7f4c00) / (float) n;
		*(float*) (g_1015ea0 + g_6a25bc * 0x2f4 + 0x1f4) = ratio;
		if (g_6a25c4[0] == -1) {
			d2_SetForm(g_6a25b8, 0);
			g_6a25c4[0] = fcn_0046f740(((((Win_1015f40*) g_1015f40)[g_772514].xc - 0x30) >> 1) + 0x2f, 0x4c, 0x4ff, g_772514);
		}
		return;
	}
	if (flags & 1) {
		e = fcn_005463a0(2, 0, 0xd, 3, *(int*) (g_7e2aa0 + 1));
		ratio = g_662b10;
		if (e != 0) {
			if (*(int*) (e + 0x70) >= 4) {
				ratio = (float) *(int*) (e + 0xc8) / (float) *(int*) (e + 0xc4);
			}
			if (ratio < g_6640e8) {
				ratio = (float) g_6640e8;
			}
			if (g_6a25c4[0] == -1) {
				d2_SetForm(g_6a25b8, 0);
				g_6a25c4[0] = fcn_0046f740(((((Win_1015f40*) g_1015f40)[g_772514].xc - 0x30) >> 1) + 0x2f, 0x4c, 0x4ff, g_772514);
			}
		}
		*(float*) (g_1015ea0 + g_6a25bc * 0x2f4 + 0x1f4) = ratio;
		return;
	}
	if (flags & 0x40) {
		e = fcn_005463a0(2, 0, 0x1e, 3, *(int*) (g_7e2aa0 + 1));
		if (e == 0) {
			return;
		}
		n = fcn_00500d20(e + 0x44, e + 0x52);
		ratio = (float) fcn_00500d20(e + 0x44, (char*) 0x7f4c00) / (float) n;
		*(float*) (g_1015ea0 + g_6a25bc * 0x2f4 + 0x1f4) = ratio;
		if (g_6a25c4[0] == -1) {
			d2_SetForm(g_6a25b8, 0);
			g_6a25c4[0] = fcn_0046f740(((((Win_1015f40*) g_1015f40)[g_772514].xc - 0x30) >> 1) + 0x2f, 0x4c, 0x4ff, g_772514);
		}
		return;
	}
	if ((signed char) flags >= 0) {
		if (g_6a25c4[0] != -1) {
			fcn_0046b2b0(g_6a25c4[0]);
			g_6a25c4[0] = -1;
		}
		return;
	}
	e = fcn_005463a0(2, 0, 0x1f, 3, *(int*) (g_7e2aa0 + 1));
	if (e == 0) {
		return;
	}
	n = fcn_00500d20(e + 0x44, e + 0x52);
	ratio = (float) fcn_00500d20(e + 0x44, (char*) 0x7f4c00) / (float) n;
	*(float*) (g_1015ea0 + g_6a25bc * 0x2f4 + 0x1f4) = ratio;
	if (g_6a25c4[0] == -1) {
		d2_SetForm(g_6a25b8, 0);
		g_6a25c4[0] = fcn_0046f740(((((Win_1015f40*) g_1015f40)[g_772514].xc - 0x30) >> 1) + 0x2f, 0x4c, 0x4ff, g_772514);
	}
	return;

no_header:
	if (g_7ea360 == 0) {
		goto no_target;
	}
	s = (char*) g_7ea360;
	if (g_7746f0 < 2) {
		d2_SetForm(g_6a25b8, 1);
		pct = (int) (fcn_004ff040(s) * g_662c38);
		fcn_005186c0(*(unsigned short*) s, 1, 4, name);
		io_AppendText(g_6a2fec, name, pct);
	}
	if (*(int*) (s + 0x16c) == 0) {
		goto drop_elements;
	}
	if (*(unsigned short*) (*(int*) (s + 0x16c) + 0x27) != g_774970) {
		goto drop_elements;
	}
	if (g_7746f0 >= 2) {
		goto drop_elements;
	}
	for (i = 0; i < 4; i++) {
		if (g_6a25c4[i] != -1) {
			fcn_0046b2b0(g_6a25c4[i]);
			g_6a25c4[i] = -1;
		}
	}
	d2_SetForm(g_6a25b8, 0);
	x = (((Win_1015f40*) g_1015f40)[g_772514].xc - 0x30) >> 1;
	n = fcn_00529800(s, kinds);
	if (n > 0) {
		y = 0x38;
		for (i = 0; i < n; i++) {
			if (kinds[i] >= 0xdf && kinds[i] < 0x3bb) {
				g_6a25c4[i] = fcn_0046f7e0(x + 0x32, y, kinds[i], g_772514, -2);
			} else {
				g_6a25c4[i] = fcn_0046f740(x + 0x32, y, kinds[i], g_772514);
			}
			y += 0x1a;
		}
	}
	p = *(char**) (s + 0x17c);
	if (p == 0) {
		if (g_6a25d8 != -1) {
			*(int*) (g_1015ea0 + g_6a25d8 * 0x2f4 + 0x1f4) = 0;
		}
		return;
	}
	if (g_6a25d8 == -1) {
		return;
	}
	c = (unsigned char) *p;
	switch (c) {
	case 0x8f:
		n = fcn_00500d20(p + 0x44, p + 0xb8);
		if (n != 0) {
			ratio = (float) fcn_00500d20(p + 0x44, (char*) 0x7f4c00) / (float) n;
		}
		break;
	case 0x16:
		n = fcn_00500d20(p + 0x44, p + 0xb8);
		if (n != 0) {
			ratio = (float) fcn_00500d20(p + 0x44, (char*) 0x7f4c00) / (float) n;
		}
		break;
	case 0x40:
		if (*(int*) (p + 0x70) < 2) {
			ratio = g_662910;
		} else if (*(int*) (p + 0x70) == 2) {
			n = fcn_00500d20(p + 0x44, p + 0x52);
			if (n != 0) {
				ratio = (float) fcn_00500d20(p + 0x44, (char*) 0x7f4c00) / (float) n;
			}
		}
		break;
	case 0x61:
		pos = *(pos14_7f4c00*) (p + 0xc4);
		fcn_00500bb0(&pos, 8, 0, 0);
		n = fcn_00500d20(p + 0xc4, &pos);
		if (n != 0) {
			ratio = (float) fcn_00500d20(p + 0xc4, (char*) 0x7f4c00) / (float) n;
		}
		break;
	case 0x43:
		pos = *(pos14_7f4c00*) (p + 0x44);
		fcn_00500bb0(&pos, 0x18, 0, 0);
		n = fcn_00500d20(p + 0x44, &pos);
		if (n != 0) {
			ratio = (float) fcn_00500d20(p + 0x44, (char*) 0x7f4c00) / (float) n;
		}
		break;
	case 0x62:
		if (*(int*) (p + 0x70) < 4) {
			ratio = g_662910;
		} else if (*(int*) (p + 0x70) == 4) {
			pos = *(pos14_7f4c00*) (p + 0x44);
			fcn_00500bb0(&pos, 0x60, 0, 0);
			n = fcn_00500d20(p + 0x44, &pos);
			if (n != 0) {
				ratio = (float) fcn_00500d20(p + 0x44, (char*) 0x7f4c00) / (float) n;
			}
		}
		break;
	case 0x65:
		if (*(int*) (p + 0x70) < 2) {
			ratio = g_662910;
		} else {
			pos = *(pos14_7f4c00*) (p + 0x44);
			fcn_00500bb0(&pos, 0x18, 0, 0);
			n = fcn_00500d20(p + 0x44, &pos);
			if (n != 0) {
				ratio = (float) fcn_00500d20(p + 0x44, (char*) 0x7f4c00) / (float) n;
			}
		}
		break;
	case 0x48:
		if (*(int*) (p + 0x70) < 1) {
			ratio = g_662910;
		} else if (*(int*) (p + 0x70) == 1) {
			n = fcn_00500d20(p + 0x44, p + 0xcc);
			if (n != 0) {
				ratio = (float) fcn_00500d20(p + 0x44, (char*) 0x7f4c00) / (float) n;
			}
		}
		break;
	case 0x6c:
		n = fcn_00500d20(p + 0x44, p + 0xb4);
		if (n != 0) {
			ratio = (float) fcn_00500d20(p + 0x44, (char*) 0x7f4c00) / (float) n;
		}
		break;
	}
	*(float*) (g_1015ea0 + g_6a25d8 * 0x2f4 + 0x1f4) = ratio;
	return;

drop_elements:
	for (i = 0; i < 4; i++) {
		if (g_6a25c4[i] != -1) {
			fcn_0046b2b0(g_6a25c4[i]);
			g_6a25c4[i] = -1;
		}
	}
	return;

no_target:
	if (g_6a25d4 == -1 || g_7e2a9c == 0) {
		return;
	}
	for (i = 0; i < 4; i++) {
		if (g_6a25c4[i] != -1) {
			fcn_0046b2b0(g_6a25c4[i]);
			g_6a25c4[i] = -1;
		}
	}
	if (lpObjektePROT[*(unsigned short*) g_7e2a9c * 0x41] != 0x1d) {
		return;
	}
	if (g_6a25e8 != -1 && g_100f1dc != -1
	    && g_67d370 == g_6a25e8 && (g_7e46ac & 0x2000)) {
		fcn_004bfe00((char*) g_7e2a9c);
	}
	if (g_6a25c0 != -1) {
		d2_SetElementValue(g_6a25c0, 0, 100, *((char*) g_7e2a9c + 0x12));
	}
	d2_SetForm(g_6a25b8, 2);
	for (i = 0; i < 4; i++) {
		if (g_6a25c4[i] != -1) {
			fcn_0046b2b0(g_6a25c4[i]);
			g_6a25c4[i] = -1;
		}
	}
	fcn_0046f2c0(g_772514, 1);
	e = *(char**) ((char*) g_7e2a9c + 0x24);
	if (e != 0) {
		s = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xb4));
		if (s != 0) {
			io_AppendText(g_6a2fe4, (unsigned char) *s * 0xe + 0x48e);
		}
	}
	e = fcn_00502cd0(*(int*) ((char*) g_7e2a9c + 0x14), 1, 0, 0x1dd);
	if (e == 0) {
		return;
	}
	s = fcn_00502cd0(*(int*) (e + 0x14), 1, 5);
	if (s == 0) {
		return;
	}
	k = 0;
	for (i = 3; i < 0x83; i += 0x20) {
		g_6a25c4[k] = fcn_0046f7e0(i, 0x28, *(unsigned short*) s + 0xdf, g_772514, -2);
		fcn_0064d41a(buf, g_67d444, gm_GetMsgField((int) e, (int) s));
		n = d2_ShowTxt(i - 2, 0x1c, buf, g_772514);
		*(int*) (g_1015ea0 + n * 0x2f4 + 0x5c) = 1;
		*(int*) (g_1015ea0 + n * 0x2f4 + 0x6c) = 1;
		*(int*) (g_1015ea0 + n * 0x2f4 + 0x18) = 0x20;
		s = gm_NextEntityQueryMatch();
		k++;
		if (s == 0) {
			return;
		}
	}
	return;
}
unsigned char _dpad_7e2760[828];
unsigned char _dpad_7e2aa0[2848];
