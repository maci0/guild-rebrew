#include "client_dialog_helpers.h"

extern unsigned char g_772558;
extern int g_772514;
extern int g_1015f4c;
extern int g_1015f50;
extern unsigned char *g_1015ea0;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern float g_6628bc;
extern float g_662924;
extern float g_66293c;
extern float g_662a98;

typedef struct {
	int f[10];
} Arg;

typedef struct {
	float f[10];
} Gfx;

typedef struct {
	char out[12];
	int src[4];
	char buf[0x10];
} Loc;

void __cdecl fcn_00472e50(void);
void __cdecl fcn_00472c30(int, int, int, int, int, int, int);
int __cdecl fcn_0046fac0(int, int, char *, int);
int __cdecl fcn_0046b520(char *, int);
void __cdecl fcn_00500d60(int *, char *);
int __cdecl fcn_005d36f0(Arg, int, int);
void __cdecl io_FormatTextBuffer(char *, char *, ...);

/* ADDRESS: GOLDTL 0x005d3d90 */
void __cdecl fcn_005d3d90(unsigned short flags, Gfx g, int win)
{
	unsigned char saved;
	int m;
	int h;
	Loc loc;
	int w;
	int step;
	int i;
	int n;
	int id;
	int x1;
	int x2;
	int d;
	float y;

	m = 0;
	saved = g_772558;
	fcn_00472e50();
	fcn_0046f2c0(win, 1);
	g_772558 = 1;
	w = *(int *) ((char *) &g_1015f4c + win * 0x3cc);
	h = *(int *) ((char *) &g_1015f50 + win * 0x3cc);
	step = (w - 0x69) / 16;
	if (flags & 1)
		m = fcn_005d36f0(*(Arg *) &g, w - 1, h);
	g_772558 = 1;
	if (flags & 2)
		fcn_005d3880(*(Arg *) &g, w - 1, h);
	if (flags & 4)
		fcn_005d3c20(*(Cur *) &g, w - 1, h);
	if (flags & 8)
		fcn_005d3980(*(Cur *) &g, w - 1, h);
	if (flags & 0x10)
		fcn_005d3ad0(*(Cur *) &g, w - 1, h);
	g_772558 = 0;
	fcn_00472c30(0x2d, 8, 0x2d, h - 0x13, 0x10, 0x10, 0x10);
	fcn_00472c30(0x2d, h - 0x13, w - 0x3b, h - 0x13, 0x10, 0x10, 0x10);
	y = (float) h - g_66293c;
	for (i = 0; i < 4; i++) {
		n = (int) ((float) i * g_6628bc * y + g_662924);
		fcn_00472c30(0x28, n, 0x2d, n, 0x10, 0x10, 0x10);
	}
	for (i = 0, n = 0x64; n > 0; i++, n -= 0x19) {
		io_FormatTextBuffer(loc.buf, (char *) 0x6acbec, n);
		id = fcn_0046fac0(3, (int) ((float) i * g_6628bc * y + g_662a98), loc.buf, g_772514);
		*(int *) (g_1015ea0 + id * 0x2f4 + 0x18) = 0x23;
		*(int *) (g_1015ea0 + id * 0x2f4 + 0x70) = 1;
	}
	if (m != 0) {
		x1 = w - 0x3c;
		fcn_00472c30(x1, 8, x1, h - 0x13, 0x10, 0x10, 0x10);
		x2 = w - 0x37;
		fcn_00472c30(x2, 8, x1, 8, 0x10, 0x10, 0x10);
		fcn_00472c30(x2, (h - 0x1e) / 2 + 8, x1, (h - 0x1e) / 2 + 8, 0x10, 0x10, 0x10);
		io_FormatTextBuffer(loc.buf, (char *) 0x67d444, m);
		d = fcn_0046b520(loc.buf, 0x55) + 2;
		id = fcn_0046fac0(x1, 5, loc.buf, g_772514);
		*(int *) (g_1015ea0 + id * 0x2f4 + 0x18) = d;
		*(int *) (g_1015ea0 + id * 0x2f4 + 0x70) = 1;
		io_FormatTextBuffer(loc.buf, (char *) 0x67d444, m / 2);
		id = fcn_0046fac0(x1, (h - 0x1e) / 2 + 5, loc.buf, g_772514);
		*(int *) (g_1015ea0 + id * 0x2f4 + 0x18) = d;
		*(int *) (g_1015ea0 + id * 0x2f4 + 0x70) = 1;
	}
	loc.src[0] = g_7f4c00;
	loc.src[1] = g_7f4c04;
	loc.src[2] = g_7f4c08;
	*(short *) ((char *) loc.src + 0xc) = g_7f4c0c;
	fcn_00500d60(loc.src, loc.out);
	if (loc.out[1] == 1) {
		io_FormatTextBuffer(loc.buf, (char *) 0x67d444, *(short *) (loc.out + 2));
		d = fcn_0046b520(loc.buf, 0x55);
		id = fcn_0046fac0(step * 16 + 0x2d, h - 0xd, loc.buf, g_772514);
		*(int *) (g_1015ea0 + id * 0x2f4 + 0x18) = d;
	}
	loc.src[0]--;
	fcn_00500d60(loc.src, loc.out);
	n = step * 15 + 0x2d;
	for (i = 0xf; i != 0; i--) {
		fcn_00472c30(n, h - 0x13, n, h - 0x10, 0x10, 0x10, 0x10);
		if (loc.out[1] == 1) {
			io_FormatTextBuffer(loc.buf, (char *) 0x67d444, *(short *) (loc.out + 2));
			d = fcn_0046b520(loc.buf, 0x55);
			id = fcn_0046fac0(n, h - 0xd, loc.buf, g_772514);
			*(int *) (g_1015ea0 + id * 0x2f4 + 0x18) = d;
			fcn_00472c30(n, h - 0x13, n, h - 0xd, 0x10, 0x10, 0x10);
		}
		loc.src[0]--;
		fcn_00500d60(loc.src, loc.out);
		n -= step;
	}
	if (loc.out[1] == 1) {
		io_FormatTextBuffer(loc.buf, (char *) 0x67d444, *(short *) (loc.out + 2));
		d = fcn_0046b520(loc.buf, 0x55);
		id = fcn_0046fac0(0x2d, h - 0xd, loc.buf, g_772514);
		*(int *) (g_1015ea0 + id * 0x2f4 + 0x18) = d;
	}
	g_772558 = saved;
}
