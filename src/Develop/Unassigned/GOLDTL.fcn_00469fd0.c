extern int g_67d398;
extern char* g_77253c;
extern int g_77250c;

void __cdecl fcn_00472880(int font);
void __cdecl fcn_0047c560(int a, int b, int c);
void __cdecl fcn_0047c9c0(int x, int y, int w, int h, int color, float alpha);
void __cdecl fcn_0046bd20(int x, int y, int w, int h, int surf, char* text, int flags);

/* ADDRESS: GOLDTL 0x00469fd0 */
void __cdecl fcn_00469fd0(char* e)
{
	char* name;
	unsigned char fl;
	int x;
	int y;

	name = e + 0xcc;
	if (*name != 0 && !(*(int*) (e + 0x1d0) & 0x40)) {
		fl = 8;
		if (*(int*) (e + 0x60) != 0) {
			fl = 9;
		}
		if (*(int*) (e + 0x70) != 0) {
			fl |= 0x10;
		}
		if (*(int*) (e + 0x54) != 0) {
			fl |= 4;
		}
		if (*(int*) (e + 0x1d0) & 8) {
			fl |= 0x20;
		}
		x = *(int*) (e + 0x10);
		if (*(int*) (e + 0x1dc) != -1) {
			x += *(int*) (e + 0x1dc);
		}
		y = *(int*) (e + 0x14);
		if (*(int*) (e + 0x1e0) != -1) {
			y += *(int*) (e + 0x1e0);
		} else {
			y -= 0x10;
		}
		fcn_00472880(*(int*) (e + 0x1cc) != 0 ? *(int*) (e + 0x1cc) : g_67d398 + 1);
		if (*(int*) (e + 0x1d0) & 0x20) {
			fcn_0047c560(0, 0, 0);
			fcn_0047c9c0(*(int*) (e + 0x10), *(int*) (e + 0x14), *(int*) (e + 0x1d4), *(int*) (e + 0x1d8), *(int*) (g_77253c + 0x50), 0.5f);
		}
		if (*(int*) (e + 0x1d0) & 4) {
			fcn_0046bd20(*(int*) (e + 0x10) - 0x30, *(int*) (e + 0x14) + *(int*) (e + 0x1c), *(int*) (e + 0x1d4) + 0x60, *(int*) (e + 0x1c), g_77250c, name, fl);
		} else {
			fcn_0046bd20(x - 0x30, y, *(int*) (e + 0x1d4) + 0x60, *(int*) (e + 0x1c), g_77250c, name, fl);
		}
	}
}
