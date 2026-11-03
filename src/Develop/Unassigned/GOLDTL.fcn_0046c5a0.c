#include <stdio.h>
#include <string.h>

extern int g_1015ea0;
extern int g_1015ea4;
extern int g_102d020;
extern int g_102d024;
extern int g_1040490;
extern int g_1040494;
extern int g_67d378;
extern int g_67d380;
extern int g_67d390;
extern int g_67d398;
extern int g_67d3a8;
extern int g_67d3b4;
extern int g_67d964;
extern int g_67d968;
extern int g_6b23a4;
extern int g_6b25b0;
extern int g_772500;
extern char* g_772524;
extern int g_772530;
extern int g_772554;
extern int g_7725b4;
extern int g_7725f8;
extern int g_7725fc;
extern int g_14a5320;

int __cdecl fcn_00465950(char* name);
void __cdecl fcn_00472880(int font);
int __cdecl fcn_0046b520(char* text, int font);
void __cdecl fcn_0046b5f0(int x, int y, int a0, int a1, int last, int color,
    int xr, int yr);
void __cdecl fcn_0046eda0(int x, int y, int a1);
void __cdecl fcn_00469c40(int a, int b, int c);
void __cdecl fcn_0047a040(int a, int b, int c, int d);
void __cdecl fcn_0047cba0(int x, int y, int a0, int text);
void __cdecl fcn_0046c4e0(int a1);
int __cdecl fcn_00467480(int x, int y, int a, int b, int c, int d);
int __cdecl fcn_00466fe0(int a, int b);
int __cdecl fcn_0046f740(int x, int y, int img, int a1);
void __cdecl fcn_0046f9b0(int img, char* text);
int __cdecl fcn_0046fdf0(int x, int y, int img, int a1);
int __cdecl fcn_0046ff90(int a, int b);
int __cdecl fcn_00468df0(int x, int y, int name, int table, int a1);
int __cdecl _isctype(int c, int type);
int __cdecl d2_GetResourceData(int table, int index);

/* Emits the run accumulated so far with the pen at (px, g_102d024). */
#define DRAW_RUN(last, px) \
	fcn_0046b5f0(px, g_102d024, a0, a1, last, color, xr, yr)

/* Renders one element's text record: walks the text string, expands the
 * '%'/'$' markup through the switch below, word-wraps the token into the
 * glyph buffer and emits the runs through the draw helpers. */
#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x0046c5a0 */
void __cdecl fcn_0046c5a0(int a0, int a1)
{
	volatile int i;
	int nImg;
	int img;
	int xr;
	int yr;
	int nLine;
	int color;
	int tmp;
	int len;
	int extra;
	int span;
	unsigned char tail[3];
	int slot;
	int v38;
	int textLen;
	unsigned char pal[9][3];
	int maxW;
	int v60;
	int v64;
	int sv68;
	int v6c;
	int sv70;
	int sv74;
	int sv78;
	struct {
		char e[0x100];
		char d[0x200];
		char c[0x100];
		char sp[0x100];
		char b[0x80];
		char a[0x100];
	} bufs;
	char* t;
	char* s;
	char* e;
	char* p;
	char tailCh;

	nImg = 0;
	extra = 0;
	v64 = 0;
	nLine = 0;
	color = 0;
	v60 = 0;
	slot = a1 * 0x3cc + 0x1015f40;
	if (*(int*) (slot + 0x28c)) {
		fcn_00472880(*(int*) (slot + 0x28c));
	} else {
		fcn_00472880(fcn_00465950("_FONT"));
	}
	g_7725b4 = 0;
	if (!*(int*) (slot + 0x3c)) {
		return;
	}
	xr = *(int*) (slot + 0x18) + *(int*) (slot + 4);
	yr = (*(int*) (slot + 0xc) - *(int*) (slot + 0x1c)) + *(int*) (slot + 4);
	v38 = *(int*) (slot + 0x20) + *(int*) (slot + 8);
	maxW = *(int*) (slot + 0xc);
	v6c = (*(int*) (slot + 0x10) - *(int*) (slot + 0x24)) + v38;
	if (*(int*) (slot + 0x14) & 8) {
		v38 = *(int*) (slot + 8) + 0xc;
	}
	if (*(int*) (slot + 0x14) & 0x20) {
		yr = (*(int*) (slot + 0xc) + *(int*) (slot + 4)) - 0xc;
	}
	sv74 = g_7725fc;
	sv78 = g_67d964;
	sv68 = g_7725f8;
	g_102d024 = v38 - *(int*) (slot + 0x258);
	sv70 = g_67d968;
	g_1015ea4 = *(unsigned short*) (g_772524 + 8);
	g_102d020 = xr;
	g_772530 = 0;
	i = 0;
	t = *(char**) (slot + 0x3c);
	textLen = (int) strlen(t);
	while (i < textLen) {
		if (!*(char*) (t + i)) {
			break;
		}
		tmp = g_772530;
		*(int*) (tmp * 0x10c + 0x1011ae4) = 0;
		for (;;) {
			int chk;
			int d;

			t = *(char**) (slot + 0x3c);
			if ((*(char*) (t + i) != '%') && (*(char*) (t + i) != '$')) {
				break;
			}
			i += 1;
			if (1 < g_6b25b0) {
				chk = _isctype(*(char*) (t + i), 4);
			} else {
				chk = *(unsigned char*) (g_6b23a4 + *(char*) (t + i) * 2) & 4;
			}
			if (chk) {
				d = *(char*) (t + i) - '0';
				i += 1;
			} else {
				d = -1;
			}
			p = t + i;
			switch (*(char*) (p)) {
			case 'A':
				DRAW_RUN(1, g_102d020);
				d = (short) (*(char*) (p - 1) - '0');
				span = (d > 0 && d < 9) ? g_1015ea4 * d : g_1015ea4;
				if (extra) {
					span = extra;
					extra = 0;
				}
				g_102d020 = xr;
				g_102d024 += span;
				i += 1;
				nLine += 1;
				g_7725b4 = 0;
				continue;
			case 'N':
				if (*(char*) (p - 1) != '$') {
					continue;
				}
				DRAW_RUN(1, g_102d020);
				span = g_1015ea4 * 3 / 2;
				if (extra) {
					span = extra;
					extra = 0;
				}
				g_7725b4 = 0;
			next_line:
				g_102d020 = xr;
				g_102d024 += span;
				i += 1;
				nLine += 1;
				continue;
			case 'Y':
				if (*(char*) (p - 1) != '$') {
					continue;
				}
				DRAW_RUN(1, g_102d020);
				span = g_1015ea4 / 2;
				if (extra) {
					span = extra;
					extra = 0;
				}
				goto next_line;
			case 'i':
				if ((*(char*) (p + 1) == 'a') || (*(char*) (p + 1) == 'n')) {
					img = *(int*) (slot + nImg * 4 + 0x294);
					v64 = 1;
					if (img == -1) {
						img = fcn_00468df0(g_102d020 - *(int*) (slot + 4),
						    g_102d024 - *(int*) (slot + 8),
						    fcn_00465950("_IMG"), 0x6b5c60, a1);
						if (*(char*) (p + 2) == '[') {
							char* zp;
							int zn;

							s = p + 3;
							zn = 0x200;
							zp = bufs.d;
							/* block-fill prelude, see docs/codegen-walls.md section 6b */
							__asm {
								mov edi, zp
								mov ebx, zn
								xor eax, eax
								lea ecx, [edi+edi*2]
								and ecx, 3
								sub ebx, ecx
								jle short Lz1
								rep stosb
								mov ecx, ebx
								and ebx, 3
								shr ecx, 2
								rep stosd
							Lz1:
								add ecx, ebx
								rep stosb
							}
							e = strchr(s, ']');
							if (!e) {
								sprintf(bufs.sp, (char*) 0x67d540);
								continue;
							}
							strncpy(bufs.d, s, (int) (e - s));
							fcn_0046f9b0(img, bufs.d);
							if (!*(char*) (e + 1)) {
								*(char*) (p + 2) = 0;
							} else {
								strncpy(t + i + 2, e + 1, (int) strlen(e + 1) + 1);
							}
						}
						if (*(char*) (p + 1) == 'n') {
							*(int*) (g_1015ea0 + img * 0x2f4 + 0x1d0) |= 0x10;
						}
						*(int*) (slot + nImg * 4 + 0x294) = -1;
						tmp = *(int*) (g_1015ea0 + img * 0x2f4 + 0x18);
						*(int*) (slot + nImg * 4 + 0x294) = img;
						g_102d020 += tmp;
						len = *(int*) (g_1015ea0 + img * 0x2f4 + 0x1c);
						extra = len + 7;
					} else {
						extra = *(int*) (g_1015ea0 + img * 0x2f4 + 0x1c) + 7;
					}
					i += 2;
					nImg += 1;
					continue;
				}
				img = *(int*) (slot + nImg * 4 + 0x294);
				if (img == -1) {
					i += 2;
					nImg += 1;
					continue;
				}
				tmp = g_102d020;
				len = *(int*) (slot + 0x258) + g_102d024;
				if ((img == 2) || (img == g_67d3a8) || (img == g_67d3a8 + 1)) {
					len += 2;
				}
				d = *(short*) (g_772500 + img * 84 + 0x50);
				if (d + g_102d020 > yr) {
					len += g_1015ea4;
					e = (char*) xr;
				} else {
					e = (char*) tmp;
				}
				if (d > *(int*) (slot + 0xc)) {
					i += 1;
					nImg += 1;
					continue;
				}
				if (g_102d020 > xr) {
					e += 6;
				}
				img = fcn_0046f740((short) (len - *(short*) (slot + 8)),
				    (short) ((short) e - *(short*) (slot + 4)), img, a1);
				if (img == -1) {
					*(int*) (slot + nImg * 4 + 0x294) = -1;
					g_102d020 += *(int*) (g_1015ea0 + img * 0x2f4 + 0x18);
					i += 2;
					nImg += 1;
					continue;
				}
				if (*(char*) (p + 1) == 'c') {
					*(int*) (g_1015ea0 + img * 0x2f4 + 0x5c) = 0;
					*(int*) (g_1015ea0 + img * 0x2f4 + 0x58) = 1;
				} else if (*(char*) (p + 1) == 'i') {
					*(int*) (g_1015ea0 + img * 0x2f4 + 0x5c) = 0;
					*(int*) (g_1015ea0 + img * 0x2f4 + 0x58) = 0;
				} else if (*(char*) (p + 1) == 'b') {
					*(int*) (g_1015ea0 + img * 0x2f4 + 0x5c) = 1;
					*(int*) (g_1015ea0 + img * 0x2f4 + 0x58) = 0;
				} else if ((*(char*) (p + 1) == 't') || (*(char*) (p + 1) == 'a') ||
				    (*(char*) (p + 1) == 'n')) {
					if (*(char*) (p + 2) == '[') {
						char* zp;
						int zn;

						s = p + 3;
						zn = 0x80;
						zp = bufs.b;
						/* block-fill prelude, see docs/codegen-walls.md section 6b */
						__asm {
							mov edi, zp
							mov ebx, zn
							xor eax, eax
							lea ecx, [edi+edi*2]
							and ecx, 3
							sub ebx, ecx
							jle short Lz2
							rep stosb
							mov ecx, ebx
							and ebx, 3
							shr ecx, 2
							rep stosd
						Lz2:
							add ecx, ebx
							rep stosb
						}
						*(int*) (g_1015ea0 + img * 0x2f4 + 0x5c) = 1;
						*(int*) (g_1015ea0 + img * 0x2f4 + 0x84) = *(int*) (slot + 0x28c);
						*(int*) (g_1015ea0 + img * 0x2f4 + 0x1d0) = 3;
						e = strchr(s, ']');
						if (!e) {
							sprintf(bufs.sp, (char*) 0x67d540);
							continue;
						}
						strncpy(bufs.b, s, (int) (e - s));
						fcn_0046f9b0(img, bufs.b);
						if (!*(char*) (e + 1)) {
							*(char*) (p + 2) = 0;
						} else {
							strncpy(t + i + 2, e + 1, (int) strlen(e + 1) + 1);
						}
					}
				}
				*(int*) (slot + nImg * 4 + 0x294) = -1;
				g_102d020 += *(int*) (g_1015ea0 + img * 0x2f4 + 0x18);
				i += 2;
				nImg += 1;
				continue;
			case 'C':
				strncpy(t, p + 1, (int) strlen(p + 1) + 1);
				g_102d024 = *(int*) (slot + 0x38) - *(int*) (slot + 0x258);
				g_102d020 = xr;
				i = 0;
				*(int*) (slot + 0x40) = 0;
				continue;
			case 'm':
				if (*(char*) (p + 1) != 't') {
					s = (char*) nImg;
					i += 1;
					nImg = (int) s;
					if (*(int*) (slot + nImg * 4 + 0x294) != -1) {
						nImg += 1;
						continue;
					}
					if (g_102d020 > xr) {
						g_102d020 += 6;
					}
					img = fcn_00467480(g_102d020 - *(int*) (slot + 4),
					    g_102d024 - *(int*) (slot + 8), 0x10, g_1015ea4, 0x82, a1);
					*(int*) (slot + nImg * 4 + 0x294) =
					    *(int*) (g_1015ea0 + img * 0x2f4 + 0x88);
					g_102d020 += *(int*) (img * 0x160 + 0x102d150) + 6;
					nImg += 1;
					continue;
				}
				i += 2;
				if (*(int*) (slot + nImg * 4 + 0x294) == -1) {
					nImg += 1;
					continue;
				}
				img = fcn_00467480(g_102d020 - *(int*) (slot + 4),
				    g_102d024 - *(int*) (slot + 8), 8, g_1015ea4, 0x10, a1);
				*(int*) (g_1015ea0 + img * 0x2f4 + 0x78) = 1;
				tmp = *(int*) (g_1015ea0 + img * 0x2f4 + 0x88);
				*(int*) (tmp * 0x160 + 0x102d288) = *(int*) (slot + nImg * 4 + 0x294);
				*(int*) (tmp * 0x160 + 0x102d290) = nImg;
				len = *(int*) (slot + nImg * 4 + 0x298);
				*(int*) (tmp * 0x160 + 0x102d28c) = len;
				*(int*) (tmp * 0x160 + 0x102d294) = *(int*) (slot + 0x3c) + i;
				fcn_00466fe0(tmp, len);
				*(int*) (slot + nImg * 4 + 0x294) = -1;
				*(int*) (slot + nImg * 4 + 0x298) = tmp;
				textLen = (int) strlen(*(char**) (slot + 0x3c));
				*(int*) (tmp * 0x160 + 0x102d294) = *(int*) (slot + 0x3c) + i;
				fcn_00469c40(g_102d020, g_102d024,
				    *(int*) (tmp * 0x160 + 0x102d274));
				nImg += 2;
				continue;
			case 'l':
				i += 1;
				img = *(int*) (slot + nImg * 4 + 0x294);
				if (img == -1) {
					nImg += 1;
					continue;
				}
				img = fcn_0046fdf0((short) ((short) g_102d024 - *(short*) (slot + 8)),
				    (short) ((short) g_102d020 - *(short*) (slot + 4)), img, a1);
				*(int*) (g_1015ea0 + img * 0x2f4 + 0x78) = 1;
				*(int*) (g_1015ea0 + img * 0x2f4 + 0x8c) = *(int*) (slot + 0x3c) + i;
				fcn_0046ff90(img, *(int*) (slot + nImg * 4 + 0x294));
				*(int*) (slot + nImg * 4 + 0x294) = -1;
				textLen = (int) strlen(*(char**) (slot + 0x3c));
				g_102d020 = xr;
				nImg += 1;
				continue;
			case 'M':
				strncpy(t + i - 1, p + 1, (int) strlen(t) + 1 - i);
				tmp = g_772530;
				*(unsigned short*) (tmp * 0x10c + 0x10119e0) = *(unsigned short*) 0x67d530;
				*(char*) (tmp * 0x10c + 0x10119e2) = *(char*) 0x67d532;
				g_772530 = tmp + 1;
				*(int*) (tmp * 0x10c + 0x1011ae8) = 0;
				continue;
			case 't':
				if (*(int*) (slot + nImg * 4 + 0x294) == -1) {
					i += 1;
					nImg += 1;
					continue;
				}
				if (!((*(char*) (p - 1) == '%' && d == -1) ||
				    (*(char*) (p - 2) == '%' && d != -1))) {
					i += 1;
					nImg += 1;
					continue;
				}
				if (g_102d020 > xr) {
					g_102d020 += 6;
				}
				img = fcn_00467480(g_102d020 - *(int*) (slot + 4),
				    g_102d024 - *(int*) (slot + 8), 0, g_1015ea4, 1, a1);
				tmp = *(int*) (g_1015ea0 + img * 0x2f4 + 0x88);
				len = *(int*) (slot + nImg * 4 + 0x294);
				s = (char*) (tmp * 0x160 + 0x102d16c);
				if (len > 0x4800) {
					strcpy(s, (char*) len);
				} else {
					strcpy(s, (char*) *(int*) (len * 4 + 0x14a5320));
				}
				*(int*) (tmp * 0x160 + 0x102d150) =
				    fcn_0046b520(s, *(int*) (tmp * 0x160 + 0x102d278));
				len = *(int*) (tmp * 0x160 + 0x102d274);
				*(int*) (g_1015ea0 + len * 0x2f4 + 0x18) =
				    *(int*) (tmp * 0x160 + 0x102d150);
				*(int*) (slot + nImg * 4 + 0x294) = -1;
				i += 1;
				nImg += 1;
				continue;
			case 'T':
				if (d == -1) {
					d = 1;
				}
				span = fcn_0046b520((char*) 0x67d52c, *(int*) (slot + 0x28c)) * d;
				span = xr + span + span * 2;
				if (span <= g_102d020) {
					i += 1;
					continue;
				}
				g_102d020 = span;
				if (span > yr) {
					DRAW_RUN(1, span);
					g_102d020 = xr;
					g_102d024 += g_1015ea4;
				}
				tmp = g_772530;
				*(unsigned short*) (tmp * 0x10c + 0x10119e0) = *(unsigned short*) 0x67d528;
				*(char*) (tmp * 0x10c + 0x10119e2) = *(char*) 0x67d52a;
				*(int*) (tmp * 0x10c + 0x1011ae8) = span;
				g_772530 = tmp + 1;
				i += 1;
				continue;
			case '>':
				if (d == -1) {
					d = 0;
				}
				DRAW_RUN(1, g_102d020);
				span = fcn_0046b520((char*) 0x67d52c, *(int*) (slot + 0x28c)) * d;
				xr = (*(int*) (slot + 4) + *(int*) (slot + 0x18)) + span * 2;
				g_102d020 = xr;
				i += 1;
				continue;
			case '<':
				if (d == -1) {
					d = 0;
				}
				DRAW_RUN(1, g_102d020);
				span = fcn_0046b520((char*) 0x67d52c, *(int*) (slot + 0x28c)) * d;
				yr = ((*(int*) (slot + 4) - *(int*) (slot + 0x1c)) - span * 2) +
				    *(int*) (slot + 0xc);
				i += 1;
				continue;
			case '[':
				tmp = g_772530;
				span = tmp * 0x10c;
				*(unsigned short*) (span + 0x10119e0) = *(unsigned short*) 0x67d524;
				tailCh = *(char*) 0x67d526;
			colon_run:
				*(char*) (span + 0x10119e2) = tailCh;
				len = (g_67d378 - g_67d398) + g_67d3b4 * 2;
				tmp += 1;
				len = len * 21;
				*(int*) (span + 0x1011ae8) = *(short*) (g_772500 + len * 4 + 0x50);
				i += 1;
				g_772530 = tmp;
				continue;
			case ']':
				tmp = g_772530;
				span = tmp * 0x10c;
				*(unsigned short*) (span + 0x10119e0) = *(unsigned short*) 0x67d520;
				tailCh = *(char*) 0x67d522;
				goto colon_run;
			case 'Z':
				color = 0x100;
				i += 1;
				continue;
			case 'R':
				DRAW_RUN(1, g_102d020);
				color = 0x40;
				i += 1;
				continue;
			case 'B':
				color = 0x80;
				i += 1;
				continue;
			case 'L':
				color = 0;
				g_102d020 = xr;
				i += 1;
				continue;
			case 'F':
				if (*(char*) (p + 1) != 'F') {
					fcn_00472880(g_67d398 + d);
					i += 1;
					continue;
				}
				pal[0][0] = 0xdc;
				pal[1][1] = 0xdc;
				pal[2][2] = 0xdc;
				pal[3][0] = 0xff;
				pal[3][1] = 0xff;
				pal[4][0] = 0xff;
				pal[5][0] = 0xff;
				pal[5][1] = 0xff;
				pal[5][2] = 0xff;
				pal[7][1] = 0xff;
				pal[2][0] = 0x60;
				pal[2][1] = 0x60;
				pal[8][1] = 3;
				pal[8][2] = 3;
				pal[0][1] = 0;
				pal[0][2] = 0;
				pal[1][0] = 0;
				pal[1][2] = 0;
				pal[3][2] = 0;
				pal[4][1] = 0;
				pal[4][2] = 0xa8;
				pal[6][0] = 0xa8;
				pal[6][1] = 0xa8;
				pal[6][2] = 0xa8;
				pal[7][0] = 0;
				pal[7][2] = 0xc4;
				pal[8][0] = 0x96;
				if (d == 9) {
					g_7725b4 &= ~0x40;
					i += 2;
					continue;
				}
				g_7725b4 |= 0x40;
				tail[0] = pal[d][0];
				tail[1] = pal[d][1];
				tail[2] = pal[d][2];
				*(char*) (&span - 2) = tail[0];
				*(char*) (&span - 3) = tail[1];
				*(char*) (&span - 4) = tail[2];
				i += 2;
				continue;
			case '%':
				v60 = 1;
				continue;
			default:
				sprintf(bufs.sp, (char*) 0x67d504, *(char*) (p - 1));
				continue;
			}
		}
		t = *(char**) (slot + 0x3c);
		if (!*(char*) (t + i)) {
			break;
		}
		if (*(char*) (t + i) == ' ') {
			while (*(char*) (t + i + 1) == ' ') {
				i += 1;
			}
			i += 1;
		}
		s = t + i;
		e = strchr(s, ' ');
		if (!e) {
			e = t + textLen;
		}
		if (!v60) {
			p = strchr(s, '%');
			if ((p) && (p <= e) && (*(char*) (p + 1) != '%')) {
				e = p;
			}
		}
		v60 = 0;
		p = strchr(s, '$');
		if ((p) && (p < e)) {
			e = p;
		}
		len = (int) (e - s);
		if (len) {
			memset(bufs.a, 0, 0x100);
			if (len >= 0) {
				memcpy(bufs.a, s, len);
				bufs.a[len] = 0;
			}
			span = fcn_0046b520(bufs.a, *(int*) (slot + 0x28c));
			if (span + g_102d020 > yr) {
				if (!(*(int*) (slot + 0x14) & 0x2000)) {
					tmp = 0;
					g_772530 = g_772530;
					strcpy(bufs.e, bufs.a);
					strcpy(bufs.c, bufs.a);
					len = (int) strlen(bufs.a);
					if (len >= 0) {
						e = (char*) (bufs.e - len - bufs.a);
						for (;;) {
							p = &bufs.a[len];
							if ((*p != '~') && (*p != '-')) {
								len -= 1;
								e += 1;
								if (len >= 0) {
									continue;
								}
								break;
							}
							strcpy(e + (int) p, p);
							tmp = (*p == '-');
							*p = '-';
							p[1] = 0;
							if (fcn_0046b520(bufs.a, *(int*) (slot + 0x28c)) +
							    g_102d020 <= yr) {
								break;
							}
							len -= 1;
							e += 1;
							if (len < 0) {
								break;
							}
						}
					}
					if (len > 0) {
						len += tmp;
						textLen = (int) strlen(bufs.a);
						strcpy((char*) (g_772530 * 0x10c + 0x10119e0), bufs.a);
						span = fcn_0046b520(bufs.a, *(int*) (slot + 0x28c));
						*(int*) (g_772530 * 0x10c + 0x1011ae8) = span;
						i += tmp + textLen - 1;
						g_772530 += 1;
					} else {
						strcpy(bufs.a, bufs.c);
					}
					DRAW_RUN(0, g_102d020);
					g_102d024 += g_1015ea4;
					*(int*) (slot + 0x4c + (*(int*) (slot + 0x248) + nLine) * 4) = i;
					nLine += 1;
					if (len > 0) {
						strcpy(bufs.a, &bufs.c[len]);
						textLen = (int) strlen(bufs.a);
						span = fcn_0046b520(bufs.a, *(int*) (slot + 0x28c));
					}
				} else if (span + g_102d020 < g_1040494) {
					fcn_0046eda0((short) ((short) span + *(short*) (slot + 0xc)),
					    *(short*) (slot + 0x10), a1);
				} else {
					fcn_0046eda0((short) ((short) g_1040494 - *(short*) (slot + 4)),
					    *(short*) (slot + 0x10), a1);
					DRAW_RUN(0, span + g_102d020);
					g_102d024 += g_1015ea4;
					*(int*) (slot + 0x4c + (*(int*) (slot + 0x248) + nLine) * 4) = i;
					nLine += 1;
				}
			}
			tmp = (int) (short) *(int*) (slot + 0x14) & 8;
			*(int*) (slot + 0x24c) = *(int*) (slot + 0x248) + nLine;
			tmp >>= 3;
			if (*(int*) (slot + 0x14) & 0x20) {
				tmp += 2;
			}
			while (tmp < *(int*) (slot + 0x2c)) {
				e = (char*) (*(int*) (slot + 0x28) + tmp * 4);
				img = *(int*) (e);
				p = (char*) (g_1015ea0 + img * 0x2f4);
				while (!*(int*) (p + 0x78)) {
					if (span + g_102d020 <= *(int*) (p + 0x10)) {
						break;
					}
					if (g_102d020 >= *(int*) (p + 0x10) + *(int*) (p + 0x18)) {
						break;
					}
					if (g_102d024 + g_1015ea4 <= *(int*) (p + 0x14)) {
						break;
					}
					if (g_102d024 >= *(int*) (p + 0x14) + *(int*) (p + 0x1c)) {
						break;
					}
					tmp = *(int*) (p + 0x10) + *(int*) (p + 0x18);
					g_102d020 = tmp + 6;
					if (span + g_102d020 > yr) {
						DRAW_RUN(0, g_102d020);
						g_102d024 += g_1015ea4;
						*(int*) (slot + 0x4c + (*(int*) (slot + 0x248) + nLine) * 4) = i;
						nLine += 1;
						g_102d020 = xr;
					}
				}
				tmp += 1;
			}
			maxW = *(int*) (slot + 4);
			span = g_1015ea4;
			len = *(int*) (slot + 0x2c);
			if ((g_67d380 - maxW) + span + g_102d020 > maxW) {
				maxW = (g_67d380 - maxW) + span + g_102d020;
			}
			if (extra) {
				g_102d020 += g_67d380 + span;
			}
			strcpy((char*) (g_772530 * 0x10c + 0x10119e0), bufs.a);
			*(int*) (g_772530 * 0x10c + 0x1011ae8) = span;
			*(int*) (g_772530 * 0x10c + 0x1011ae4) = g_7725b4;
			*(unsigned short*) (g_772530 * 0x10c + 0x1011ae0) = *(unsigned short*) (tail);
			*(char*) (g_772530 * 0x10c + 0x1011ae2) = tail[2];
			g_772530 += 1;
			i += extra;
			if (g_772530 > 0x20) {
				g_772530 = 0;
			}
		}
	}
	DRAW_RUN(1, g_102d020);
	if (*(int*) (slot + 0x14) & 0x4000) {
		if (g_1040490 < (int) ((g_1015ea4 - 8) + g_102d024)) {
			tmp = *(int*) (slot + 0x27c);
			p = *(char**) (g_1015ea0 + tmp * 0x2f4 + 0x40);
			if (p) {
				tmp = *(int*) (p + 0x27c);
				len = ((*(int*) (p + 8) - g_1015ea4) - g_102d024) + 8 + g_1040490;
				span = *(int*) (p + 4);
			} else {
				len = ((g_1040490 - g_1015ea4) - g_102d024) + *(int*) (slot + 8) - 8;
				span = *(int*) (slot + 4);
			}
			fcn_00469c40(span, len, tmp);
		}
		fcn_0046eda0(*(short*) (slot + 0xc),
		    (short) ((g_1015ea4 - *(short*) (slot + 8)) + g_102d024), a1);
	}
	g_102d024 += g_1015ea4;
	if (*(int*) (slot + 0x14) & 0x2000) {
		fcn_0046eda0((short) maxW, *(short*) (slot + 0x10), a1);
	}
	tmp = g_102d024 - *(int*) (slot + 8);
	if (*(int*) (slot + 0x254) < tmp) {
		*(int*) (slot + 0x254) = tmp;
	}
	fcn_0047a040(sv68, sv74, sv78, sv70);
	if ((*(char*) (slot + 0x14) & 0x20) && !g_772554) {
		tmp = ((v6c - v38) - 0x10) / *(int*) (slot + 0x254) + v38;
		span = d2_GetResourceData(g_67d390, 5);
		fcn_0047cba0(yr + 1, tmp, a0, span);
	}
	if ((*(int*) (slot + 0x3c4) != *(int*) (slot + 0x2c)) && v64) {
		fcn_0046c4e0(a1);
		*(int*) (slot + 0x3c4) = *(int*) (slot + 0x2c);
	}
}
