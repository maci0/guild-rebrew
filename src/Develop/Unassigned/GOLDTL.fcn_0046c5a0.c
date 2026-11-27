#include <stdio.h>
#include <string.h>
#define g_1015ea0 d2_gui_legacy_pointer_declaration
#define d2_GetResourceData d2_gui_legacy_resource_declaration
#define g_772500 d2_gui_legacy_772500_declaration
#include "Develop/Units/d2.v1/d2_gui.h"
#undef g_1015ea0
#undef d2_GetResourceData
#undef g_772500
extern int g_1015ea0; extern int d2_FontHeight; extern int g_102d020; extern int g_102d024; extern int d2_ScreenHeight; extern int g_1040494; extern int d2_CurrentFont;
extern int g_67d380;
extern int g_67d390;
extern int d2_DefaultFont;
extern int g_67d3a8;
extern int g_67d3b4;
extern int d2_ClipRight;
extern int d2_ClipBottom;
extern int g_6b23a4;
extern int g_6b25b0;
extern int g_772500;
extern char* g_772524;
extern int g_772530;
extern int g_772554;
extern int g_7725b4;
extern int d2_ClipLeft;
extern int g_7725fc;
extern int txt_TextEntries;

int __cdecl d2_FindResourceByName(char* name);
void __cdecl d2_SelectFont(int font);
int __cdecl d2_MeasureTextWidth(char* text, int font);
void __cdecl d2_RenderMarkupLine(int x, int y, int a0, int a1, int last, int color,
    int xr, int yr);
void __cdecl d2_ResizeWindow(int x, int y, int a1);
void __cdecl d2_PositionControl(int a, int b, int c);
void __cdecl d2_SetClipRect(int a, int b, int c, int d);
void __cdecl d2_DrawSpriteFromSet(int x, int y, int a0, int text);
void __cdecl d2_NormalizeWindowButtonWidths(int a1);
int __cdecl d2_AddWindowInputIcon(int x, int y, int a, int b, int c, int d);
int __cdecl d2_SetFieldTextId(int a, int b);
int __cdecl d2_AddElementToWindow(int x, int y, int img, int a1);
void __cdecl d2_SetControlText(int img, char* text);
int __cdecl d2_AddWindowText(int x, int y, int img, int a1);
int __cdecl d2_SetEditControlText(int a, int b);
int __cdecl d2_AddWindowTextButton(int x, int y, int name, int table, int a1);
int __cdecl _isctype(int c, int type);
int __cdecl d2_GetResourceData(int table, int index);

/* Emits the run accumulated so far with the pen at (px, g_102d024). */
#define DRAW_RUN(last, px) \
	d2_RenderMarkupLine(px, g_102d024, a0, a1, last, color, xr, yr)

/* Renders one element's text record: walks the text string, expands the
 * '%'/'$' markup through the switch below, word-wraps the token into the
 * glyph buffer and emits the runs through the draw helpers. */
#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x0046c5a0 */
void __cdecl d2_RenderMarkupText(int a0, int a1)
{
	int i;
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
		d2_SelectFont(*(int*) (slot + 0x28c));
	} else {
		d2_SelectFont(d2_FindResourceByName("_FONT"));
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
	sv78 = d2_ClipRight;
	sv68 = d2_ClipLeft;
	g_102d024 = v38 - *(int*) (slot + 0x258);
	sv70 = d2_ClipBottom;
	d2_FontHeight = *(unsigned short*) (g_772524 + 8);
	g_102d020 = xr;
	g_772530 = 0;
	i = 0;
	t = *(char**) (slot + 0x3c);
	textLen = (int) strlen(t);
	while (textLen > i) {
		if (!*(char*) (t + i)) {
			break;
		}
		tmp = g_772530;
		*(int*) (tmp * 0x10c + 0x1011ae4) = 0;
		for (;;) {
			int chk;
			int d;
			char ch;

			t = *(char**) (slot + 0x3c);
			ch = *(char*) (t + i);
			if (ch != '%' && ch != '$') {
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
				span = (d > 0 && d < 9) ? d2_FontHeight * d : d2_FontHeight;
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
				span = d2_FontHeight * 3 / 2;
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
				span = d2_FontHeight / 2;
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
						img = d2_AddWindowTextButton(g_102d020 - *(int*) (slot + 4),
						    g_102d024 - *(int*) (slot + 8),
						    d2_FindResourceByName("_IMG"), 0x6b5c60, a1);
						if (*(char*) (p + 2) == '[') {
							char* zp;
							int zn;

							s = p + 3;
							zn = 0x200;
							zp = bufs.d;
							/* block-fill prelude, see archived docs/codegen-walls.md section 6b */
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
							d2_SetControlText(img, bufs.d);
							if (!*(char*) (e + 1)) {
								*(char*) (p + 2) = 0;
							} else {
								strncpy(t + i + 2, e + 1, (int) strlen(e + 1) + 1);
							}
						}
						if (*(char*) (p + 1) == 'n') {
							((D2_CONTROL_TL*)g_1015ea0)[img].flags_1d0 |= 0x10;
						}
						*(int*) (slot + nImg * 4 + 0x294) = -1;
						tmp = ((D2_CONTROL_TL*)g_1015ea0)[img].width;
						*(int*) (slot + nImg * 4 + 0x294) = img;
						g_102d020 += tmp;
						len = ((D2_CONTROL_TL*)g_1015ea0)[img].height;
						extra = len + 7;
					} else {
						extra = ((D2_CONTROL_TL*)g_1015ea0)[img].height + 7;
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
					len += d2_FontHeight;
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
				img = d2_AddElementToWindow((short) (len - *(short*) (slot + 8)),
				    (short) ((short) e - *(short*) (slot + 4)), img, a1);
				if (img == -1) {
					*(int*) (slot + nImg * 4 + 0x294) = -1;
					g_102d020 += ((D2_CONTROL_TL*)g_1015ea0)[img].width;
					i += 2;
					nImg += 1;
					continue;
				}
				if (*(char*) (p + 1) == 'c') {
					((D2_CONTROL_TL*)g_1015ea0)[img].value_05c = 0;
					((D2_CONTROL_TL*)g_1015ea0)[img].value_058 = 1;
				} else if (*(char*) (p + 1) == 'i') {
					((D2_CONTROL_TL*)g_1015ea0)[img].value_05c = 0;
					((D2_CONTROL_TL*)g_1015ea0)[img].value_058 = 0;
				} else if (*(char*) (p + 1) == 'b') {
					((D2_CONTROL_TL*)g_1015ea0)[img].value_05c = 1;
					((D2_CONTROL_TL*)g_1015ea0)[img].value_058 = 0;
				} else if ((*(char*) (p + 1) == 't') || (*(char*) (p + 1) == 'a') ||
				    (*(char*) (p + 1) == 'n')) {
					if (*(char*) (p + 2) == '[') {
						char* zp;
						int zn;

						s = p + 3;
						zn = 0x80;
						zp = bufs.b;
						/* block-fill prelude, see archived docs/codegen-walls.md section 6b */
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
						((D2_CONTROL_TL*)g_1015ea0)[img].value_05c = 1;
						((D2_CONTROL_TL*)g_1015ea0)[img].font = *(int*) (slot + 0x28c);
						((D2_CONTROL_TL*)g_1015ea0)[img].flags_1d0 = 3;
						e = strchr(s, ']');
						if (!e) {
							sprintf(bufs.sp, (char*) 0x67d540);
							continue;
						}
						strncpy(bufs.b, s, (int) (e - s));
						d2_SetControlText(img, bufs.b);
						if (!*(char*) (e + 1)) {
							*(char*) (p + 2) = 0;
						} else {
							strncpy(t + i + 2, e + 1, (int) strlen(e + 1) + 1);
						}
					}
				}
				*(int*) (slot + nImg * 4 + 0x294) = -1;
				g_102d020 += ((D2_CONTROL_TL*)g_1015ea0)[img].width;
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
					img = d2_AddWindowInputIcon(g_102d020 - *(int*) (slot + 4),
					    g_102d024 - *(int*) (slot + 8), 0x10, d2_FontHeight, 0x82, a1);
					*(int*) (slot + nImg * 4 + 0x294) =
					    ((D2_CONTROL_TL*)g_1015ea0)[img].value_088;
					g_102d020 += *(int*) (img * 0x160 + 0x102d150) + 6;
					nImg += 1;
					continue;
				}
				i += 2;
				if (*(int*) (slot + nImg * 4 + 0x294) == -1) {
					nImg += 1;
					continue;
				}
				img = d2_AddWindowInputIcon(g_102d020 - *(int*) (slot + 4),
				    g_102d024 - *(int*) (slot + 8), 8, d2_FontHeight, 0x10, a1);
				((D2_CONTROL_TL*)g_1015ea0)[img].value_078 = 1;
				tmp = ((D2_CONTROL_TL*)g_1015ea0)[img].value_088;
				*(int*) (tmp * 0x160 + 0x102d288) = *(int*) (slot + nImg * 4 + 0x294);
				*(int*) (tmp * 0x160 + 0x102d290) = nImg;
				len = *(int*) (slot + nImg * 4 + 0x298);
				*(int*) (tmp * 0x160 + 0x102d28c) = len;
				*(int*) (tmp * 0x160 + 0x102d294) = *(int*) (slot + 0x3c) + i;
				d2_SetFieldTextId(tmp, len);
				*(int*) (slot + nImg * 4 + 0x294) = -1;
				*(int*) (slot + nImg * 4 + 0x298) = tmp;
				textLen = (int) strlen(*(char**) (slot + 0x3c));
				*(int*) (tmp * 0x160 + 0x102d294) = *(int*) (slot + 0x3c) + i;
				d2_PositionControl(g_102d020, g_102d024,
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
				img = d2_AddWindowText((short) ((short) g_102d024 - *(short*) (slot + 8)),
				    (short) ((short) g_102d020 - *(short*) (slot + 4)), img, a1);
				((D2_CONTROL_TL*)g_1015ea0)[img].value_078 = 1;
				((D2_CONTROL_TL*)g_1015ea0)[img].payload.fields.value_08c = *(int*) (slot + 0x3c) + i;
				d2_SetEditControlText(img, *(int*) (slot + nImg * 4 + 0x294));
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
				img = d2_AddWindowInputIcon(g_102d020 - *(int*) (slot + 4),
				    g_102d024 - *(int*) (slot + 8), 0, d2_FontHeight, 1, a1);
				tmp = ((D2_CONTROL_TL*)g_1015ea0)[img].value_088;
				len = *(int*) (slot + nImg * 4 + 0x294);
				s = (char*) (tmp * 0x160 + 0x102d16c);
				if (len > 0x4800) {
					strcpy(s, (char*) len);
				} else {
					strcpy(s, (char*) *(int*) (len * 4 + 0x14a5320));
				}
				*(int*) (tmp * 0x160 + 0x102d150) =
				    d2_MeasureTextWidth(s, *(int*) (tmp * 0x160 + 0x102d278));
				len = *(int*) (tmp * 0x160 + 0x102d274);
				((D2_CONTROL_TL*)g_1015ea0)[len].width =
				    *(int*) (tmp * 0x160 + 0x102d150);
				*(int*) (slot + nImg * 4 + 0x294) = -1;
				i += 1;
				nImg += 1;
				continue;
			case 'T':
				if (d == -1) {
					d = 1;
				}
				span = d2_MeasureTextWidth((char*) 0x67d52c, *(int*) (slot + 0x28c)) * d;
				span = xr + span + span * 2;
				if (span <= g_102d020) {
					i += 1;
					continue;
				}
				g_102d020 = span;
				if (span > yr) {
					DRAW_RUN(1, span);
					g_102d020 = xr;
					g_102d024 += d2_FontHeight;
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
				span = d2_MeasureTextWidth((char*) 0x67d52c, *(int*) (slot + 0x28c)) * d;
				xr = (*(int*) (slot + 4) + *(int*) (slot + 0x18)) + span * 2;
				g_102d020 = xr;
				i += 1;
				continue;
			case '<':
				if (d == -1) {
					d = 0;
				}
				DRAW_RUN(1, g_102d020);
				span = d2_MeasureTextWidth((char*) 0x67d52c, *(int*) (slot + 0x28c)) * d;
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
				len = (d2_CurrentFont - d2_DefaultFont) + g_67d3b4 * 2;
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
					d2_SelectFont(d2_DefaultFont + d);
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
			span = d2_MeasureTextWidth(bufs.a, *(int*) (slot + 0x28c));
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
							if (d2_MeasureTextWidth(bufs.a, *(int*) (slot + 0x28c)) +
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
						span = d2_MeasureTextWidth(bufs.a, *(int*) (slot + 0x28c));
						*(int*) (g_772530 * 0x10c + 0x1011ae8) = span;
						i += tmp + textLen - 1;
						g_772530 += 1;
					} else {
						strcpy(bufs.a, bufs.c);
					}
					DRAW_RUN(0, g_102d020);
					g_102d024 += d2_FontHeight;
					*(int*) (slot + 0x4c + (*(int*) (slot + 0x248) + nLine) * 4) = i;
					nLine += 1;
					if (len > 0) {
						strcpy(bufs.a, &bufs.c[len]);
						textLen = (int) strlen(bufs.a);
						span = d2_MeasureTextWidth(bufs.a, *(int*) (slot + 0x28c));
					}
				} else if (span + g_102d020 < g_1040494) {
					d2_ResizeWindow((short) ((short) span + *(short*) (slot + 0xc)),
					    *(short*) (slot + 0x10), a1);
				} else {
					d2_ResizeWindow((short) ((short) g_1040494 - *(short*) (slot + 4)),
					    *(short*) (slot + 0x10), a1);
					DRAW_RUN(0, span + g_102d020);
					g_102d024 += d2_FontHeight;
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
				p = (char*)&((D2_CONTROL_TL*)g_1015ea0)[img];
				while (!*(int*) (p + 0x78)) {
					if (span + g_102d020 <= *(int*) (p + 0x10)) {
						break;
					}
					if (g_102d020 >= *(int*) (p + 0x10) + *(int*) (p + 0x18)) {
						break;
					}
					if (g_102d024 + d2_FontHeight <= *(int*) (p + 0x14)) {
						break;
					}
					if (g_102d024 >= *(int*) (p + 0x14) + *(int*) (p + 0x1c)) {
						break;
					}
					tmp = *(int*) (p + 0x10) + *(int*) (p + 0x18);
					g_102d020 = tmp + 6;
					if (span + g_102d020 > yr) {
						DRAW_RUN(0, g_102d020);
						g_102d024 += d2_FontHeight;
						*(int*) (slot + 0x4c + (*(int*) (slot + 0x248) + nLine) * 4) = i;
						nLine += 1;
						g_102d020 = xr;
					}
				}
				tmp += 1;
			}
			span = d2_FontHeight;
			len = *(int*) (slot + 0x2c);
			if ((g_67d380 - *(int*) (slot + 4)) + span + g_102d020 > maxW) {
				maxW = (g_67d380 - *(int*) (slot + 4)) + span + g_102d020;
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
		if (d2_ScreenHeight < (int) ((d2_FontHeight - 8) + g_102d024)) {
			tmp = *(int*) (slot + 0x27c);
			p = *(char**)&((D2_CONTROL_TL*)g_1015ea0)[tmp].parent;
			if (p) {
				tmp = *(int*) (p + 0x27c);
				len = ((*(int*) (p + 8) - d2_FontHeight) - g_102d024) + 8 + d2_ScreenHeight;
				span = *(int*) (p + 4);
			} else {
				len = ((d2_ScreenHeight - d2_FontHeight) - g_102d024) + *(int*) (slot + 8) - 8;
				span = *(int*) (slot + 4);
			}
			d2_PositionControl(span, len, tmp);
		}
		d2_ResizeWindow(*(short*) (slot + 0xc),
		    (short) ((d2_FontHeight - *(short*) (slot + 8)) + g_102d024), a1);
	}
	g_102d024 += d2_FontHeight;
	if (*(int*) (slot + 0x14) & 0x2000) {
		d2_ResizeWindow((short) maxW, *(short*) (slot + 0x10), a1);
	}
	tmp = g_102d024 - *(int*) (slot + 8);
	if (*(int*) (slot + 0x254) < tmp) {
		*(int*) (slot + 0x254) = tmp;
	}
	d2_SetClipRect(sv68, sv74, sv78, sv70);
	if ((*(char*) (slot + 0x14) & 0x20) && !g_772554) {
		tmp = ((v6c - v38) - 0x10) / *(int*) (slot + 0x254) + v38;
		span = d2_GetResourceData(g_67d390, 5);
		d2_DrawSpriteFromSet(yr + 1, tmp, a0, span);
	}
	if ((*(int*) (slot + 0x3c4) != *(int*) (slot + 0x2c)) && v64) {
		d2_NormalizeWindowButtonWidths(a1);
		*(int*) (slot + 0x3c4) = *(int*) (slot + 0x2c);
	}
}
