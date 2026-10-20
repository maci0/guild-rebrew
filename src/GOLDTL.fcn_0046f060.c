extern char g_1015f40[];
extern int g_10161d0[];
extern char g_1015ea0[];

void __cdecl fcn_0046eda0(int w, int h, int win);

/* ADDRESS: GOLDTL 0x0046f060 */
void __cdecl fcn_0046f060(int win)
{
	char* p;
	char* e;
	int v;
	int n;
	int y;

	if (g_10161d0[win * 0xf3] == 0) {
		return;
	}
	p = (char*) g_1015f40 + win * 0x3cc;
	y = *(int*) (p + 8);
	if (*(unsigned char*) (p + 0x14) & 0x10) {
		v = *(int*) (p + 0x254);
	} else {
		v = win;
	}
	n = *(int*) (p + 0x2c);
	if (n > 0) {
		e = (char*) g_1015ea0 + 0x14;
		do {
			if (y + v < *(int*) (e + 8) + *(int*) e) {
				v = (*(int*) (e + 8) - y) + *(int*) e + 8;
			}
			e += 0x2f4;
			n--;
		} while (n != 0);
	}
	fcn_0046eda0(*(short*) (p + 0xc), (short) v, win);
}
