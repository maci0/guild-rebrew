extern int g_774970;
extern int __cdecl fcn_0046f740(int x, int y, int id, int ctx);
extern int __cdecl fcn_0051af00(char* dst, const char* fmt, ...);
extern int __cdecl fcn_005c9090(char* text, int x, int y, int color, int flags);
extern int __cdecl fcn_004677e0(int x, int y, int w, int a, int b, int c, int d, int ctx);
extern int __cdecl fcn_0050f980(int a, int b);
extern int __cdecl fcn_00472380(int element, int a, int b, int value);
extern int __cdecl fcn_00472640(int element, int a);
extern int __cdecl _ftol(void);

/* Draw the trade-good detail window: create the frame and the four value
 * labels, format the two lines of text into the message buffer, draw the
 * unit icon plus its 0xca-wide gauges, then create the element and kick off
 * its animation. */
/* ADDRESS: GOLDTL 0x005ca740 */
int __cdecl fcn_005ca740(int a0, int a1, int a2, int a3, int* a4, int a5)
{
	int v8;
	int v10;
	int v5;
	int v6;
	int v7;
	char buf[0x100];

	(void) a2;
	v8 = a1 + 0x1c;
	v10 = *(short*) (*(int*) 0x772500 + 0x1ebd8) / 2 + a0;
	a4[1] = fcn_0046f740(a0, v8, 0x5da, *(int*) 0x772514);
	a4[2] = -1;
	if (a4[0] != 0) {
		v5 = *(int*) (a4[0] + 0x18c);
		a4[6] = fcn_0046f740(v10 - *(short*) (*(int*) 0x772500 + 0x50 + v5 * 0x54) / 2 - 3,
		                     a1 + 0x1d, v5, *(int*) 0x772514);
		fcn_0046f740(a0 + 3, a1 + 0x1f, a4[7], *(int*) 0x772514);
		if (a4[8])
			fcn_0046f740(a0 + 3, *(short*) (*(int*) 0x772500 + 0x1ebda) + 9 + a1,
			             a4[8], *(int*) 0x772514);
		if (a4[9])
			fcn_0046f740(*(short*) (*(int*) 0x772500 + 0x1ebd8) - 0x10 + a0,
			             a1 + 0x1f, a4[9], *(int*) 0x772514);
		fcn_0046f740(*(short*) (*(int*) 0x772500 + 0x1ebd8) - 0x10 + a0,
		             *(short*) (*(int*) 0x772500 + 0x1ebda) + 9 + a1, a4[10],
		             *(int*) 0x772514);
		if (*(unsigned char*) (a4[0] + 0xd) && a5)
			fcn_0051af00(buf, (const char*) 0x6ac964,
			             ((*(unsigned char*) (a4[0] + 9) != 0) ? 10 : 0) + 0x114 +
			                 *(unsigned char*) (a4[0] + 0xd),
			             *(unsigned short*) a4[0]);
		else
			fcn_0051af00(buf, (const char*) 0x6ac96c, *(unsigned short*) a4[0]);
		v7 = a3;
		fcn_005c9090(buf, v10, a4[5], 0xca, a3);
		fcn_0051af00(buf, (const char*) 0x6ac95c, *(unsigned short*) a4[0]);
		fcn_005c9090(buf, v10, a4[5] + 0xe, 0xca, v7);
		if (*(unsigned char*) (a4[0] + 2) != 6) {
			v6 = fcn_004677e0(v10 - 0x23, *(short*) (*(int*) 0x772500 + 0x1ebda) + 0x1e + a1,
			                  0x40, 0, 100, 0x75, 0x442, *(int*) 0x772514);
			a4[2] = v6;
			if (*(unsigned char*) (a4[0] + 2) != 7) {
				fcn_0050f980(*(unsigned short*) 0x774970,
				             *(unsigned short*) a4[0]);
				fcn_00472380(a4[2], 0, 100, _ftol());
			} else {
				fcn_00472380(v6, 0, 100, 0);
			}
			fcn_00472640(a4[2], 0);
		}
		if (a4[0xc]) {
			*(int*) (*(int*) 0x1015ea0 + 0x5c + a4[1] * 0x2f4) = 1;
			*(int*) (*(int*) 0x1015ea0 + 0x1d0 + a4[1] * 0x2f4) = 3;
			*(int*) (*(int*) 0x1015ea0 + 0x2f0 + a4[1] * 0x2f4) = a4[0];
		}
		v5 = *(unsigned char*) (a4[0] + 2);
		if (v5 != 5 && v5 != 6 && v5 != 7)
			return 0;
		v7 = *(int*) (a4[0] + 0x54);
		v6 = a0 - 0x20;
	} else {
		v8 = a1 + 0x1d;
		v7 = 0x4fb;
		v6 = v10 - *(short*) (*(int*) 0x772500 + 0x1a2ac) / 2 - 3;
	}
	fcn_0046f740(v6, v8, v7, *(int*) 0x772514);
	return 0;
}
