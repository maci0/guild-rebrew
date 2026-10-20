extern int g_14ce8e8;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern short g_14cf900;
extern short g_14cf902;
extern int g_774a74;
extern int g_774a6c;
extern int g_774a70;
extern int g_774a5c;
extern int g_774a60;
extern int g_774a50;
extern int g_774a44;
extern int g_774a54;
extern int g_774a48;
extern int g_6772c4;
extern int g_6772bc;
extern int g_6772c0;
extern int g_6b5c80;
extern int g_6b5c84;
extern int g_778d24;
extern int g_778d20;
extern int g_100f1e8;
extern int g_100f1ec;

void __cdecl fcn_004125c0(int x, int y);

/* ADDRESS: GOLDTL 0x005b0f00 */
int __cdecl fcn_005b0f00(char* w)
{
	int r;

	r = 0;
	if (g_14ce8e8) {
		int y;
		int x;
		int bp;
		int bx;
		int py;
		int px;

		if (g_774a74 == 0) {
			x = g_14ce8c0;
			y = g_14ce8c2;
			g_6772c4 = 0;
			g_774a74 = 1;
			g_774a6c = x;
			g_774a70 = y;
			bx = *(int*) (w + 0x268);
			bp = *(int*) (w + 0x258);
			g_774a5c = bx;
			g_774a60 = bp;
			g_774a50 = g_6772bc;
			g_774a44 = g_6772c0;
			g_774a54 = g_6b5c80;
			g_774a48 = g_6b5c84;
			g_6b5c80 = x - bx;
			g_6772bc = g_778d24 - bx - 0x200 + x;
			g_6b5c84 = y - bp;
			g_6772c0 = g_778d20 - bp - 0x168 + y;
		} else {
			x = g_774a6c;
			y = g_774a70;
			bx = g_774a5c;
			bp = g_774a60;
		}
		px = g_14cf900 - x;
		py = g_14cf902 - y;
		px = (int) (float) px;
		py = (int) (float) py;
		if (*(int*) (w + 0x268) != bx + px || *(int*) (w + 0x258) != bp + py) {
			r = 1;
		}
		*(int*) (w + 0x268) = bx + px;
		*(int*) (w + 0x258) = g_774a60 + py;
	} else if (g_774a74) {
		g_6772c0 = g_774a44;
		g_6b5c80 = g_774a54;
		g_6772bc = g_774a50;
		g_774a6c = 0;
		g_774a70 = 0;
		g_6b5c84 = g_774a48;
		g_6772c4 = 1;
		fcn_004125c0(g_100f1e8, g_100f1ec);
		g_774a74 = 0;
	}
	return r;
}
