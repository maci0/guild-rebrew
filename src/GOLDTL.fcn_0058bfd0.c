#include "Develop/Units/d2.v1/d2_gui.h"

extern char g_6811b0[];
extern char g_7f4ca0[];
extern unsigned short g_774970;
extern float g_662cf8;

int __cdecl fcn_004727a0(int win, int layer);
int __cdecl fcn_0046f740(int x, int y, int id, int win);
int __cdecl fcn_0046fac0(int x, int y, char* text, int win);
void __cdecl fcn_00472900(int element, int value);
int __cdecl fcn_00519190();
void __cdecl fcn_0051af00(char* buf, char* fmt, ...);
void __cdecl fcn_00533f40(int x, int y, int owner, int other, int arg5,
                           int* id2, int* id1, int* id3);
void __cdecl fcn_00534160(int x0, int y, int len, int t);
void __cdecl fcn_0058b9c0(void* a1, void* a2);
void __cdecl fcn_0058ba20(char* o, char* buf);

/* ADDRESS: GOLDTL 0x0058bfd0 */
void __cdecl fcn_0058bfd0(int* a0)
{
	int i;
	int saved;
	int n;
	int* v1;
	int v9;
	int v10;
	int v11;
	char buf[256];
	char buf2[256];
	int e;
	int j;
	int h;
	int y;
	int* r;

	n = 0;
	v1 = (int*) a0[7];
	i = *(int*) (v1[0] * 4 + 0x6652f8);
	if (i > 0) {
		e = 0;
		r = a0 + 0xc;
		do {
			if (*(int*) ((char*) v1[4] + e) != -1) {
				r[-1] = v1[4] + e;
				n++;
				r[-2] = -1;
				r[0] = *(int*) ((char*) v1[4] + e);
				r += 3;
			}
			e += 0x44;
		} while (--i);
	}
	if (n < 8) {
		r = a0 + n * 3 + 0xc;
		i = 8 - n;
		do {
			r[-1] = 0;
			*r = -1;
			r[-2] = -1;
			r += 3;
		} while (--i);
	}
	saved = *(int*) (a0[2] * 0x3cc + 0x1016198);
	fcn_004727a0(a0[0], 2);
	fcn_00519190(g_6811b0);
	fcn_004727a0(a0[0], 3);
	fcn_00519190(g_6811b0);
	fcn_004727a0(a0[0], 5);
	fcn_00519190(g_6811b0);
	fcn_00533f40(0, 0, a0[4], a0[2], *(int*) (a0[2] * 0x3cc + 0x1015f50),
	             &v9, &v11, &v10);
	fcn_004727a0(a0[0], 2);
	i = 0;
	if (n > 0) {
		r = a0 + 0xb;
		do {
			h = *(int*) (a0[2] * 0x3cc + 0x1015f4c);
			y = (h - *(short*) (g_772500 + 0x2399c)) / 2;
			r[-1] = fcn_0046f740(y,
			                     *(int*) (a0[2] * 0x3cc + 0x1015f50) * i + 2,
			                     0x6c7, a0[2]);
			h = fcn_0046f740(y + 2,
			                 *(int*) (a0[2] * 0x3cc + 0x1015f50) * i + 4,
			                 *(int*) (*r + 0x3c), a0[2]);
			r[-1] = h;
			*(int*) (g_1015ea0 + 0x5c + h * 0x2f4) = 1;
			*(int*) (g_1015ea0 + 0x1d0 + r[-1] * 0x2f4) = 3;
			fcn_0058b9c0((void*) *r, buf);
			fcn_0058ba20((char*) *r, buf2);
			y = *(int*) (a0[2] * 0x3cc + 0x1015f50) * i + 0x38;
			h = fcn_0046fac0(0, y, buf, a0[2]);
			*(int*) (g_1015ea0 + 0x6c + h * 0x2f4) = 1;
			*(int*) (g_1015ea0 + 0x18 + h * 0x2f4) =
			    *(int*) (a0[2] * 0x3cc + 0x1015f4c);
			fcn_00472900(h, 0x54);
			y += 0xd;
			h = fcn_0046fac0(0, y, buf2, a0[2]);
			*(int*) (g_1015ea0 + 0x6c + h * 0x2f4) = 1;
			*(int*) (g_1015ea0 + 0x18 + h * 0x2f4) =
			    *(int*) (a0[2] * 0x3cc + 0x1015f4c);
			fcn_00472900(h, 0x54);
			y += 0x12;
			for (j = 0; j < 5; j++) {
				fcn_0051af00(buf, "%s:", 0x16b7 + j);
				h = fcn_0046fac0(0x28, y, buf, a0[2]);
				*(int*) (g_1015ea0 + 0x18 + h * 0x2f4) = 0x12c;
				fcn_00472900(h, 0x54);
				fcn_00534160(0xa0, y,
				             *(unsigned char*) (*r + 0x24 + j), 0x4df);
				y += 0xd;
			}
			i++;
			r += 3;
		} while (i < n);
	}
	*(int*) (a0[2] * 0x3cc + 0x1016198) = saved;
	fcn_004727a0(a0[0], 5);
	fcn_00519190(g_6811b0);
	fcn_0051af00(buf, "%1N3",
	             *(unsigned short*) (g_7f4ca0 +
	                                 (unsigned int) g_774970 * 0x21c));
	fcn_00519190("$7<$R%s$0<$4>$L%s$A$0>", 0x4101, buf);
	fcn_0051af00(buf, "AD %i", *(unsigned short*) ((char*) v1 + 0xa) + 0x578);
	fcn_00519190("$7<$R%s$0<$4>$L%s$A$0>", 0x4102, buf);
	fcn_0051af00(buf, "%i %%",
	             (int) ((float) *(unsigned char*) ((char*) v1 + 0xc) *
	                    *(float*) 0x662c30 * g_662cf8));
	fcn_00519190("$7<$R%s$0<$4>$L%s$A$0>", 0x4103, buf);
}
