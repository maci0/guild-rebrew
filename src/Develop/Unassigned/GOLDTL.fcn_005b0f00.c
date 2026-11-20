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
extern int d2_MouseRightBoundary;
extern int d2_MouseBottomBoundary;
extern int g_6b5c80;
extern int d2_MouseTopBoundary;
extern int g_778d24;
extern int g_778d20;
extern int d2_MouseX;
extern int d2_MouseY;

void __cdecl fcn_004125c0(int x, int y);

/* ADDRESS: GOLDTL 0x005b0f00 */
int __cdecl d2_UpdateWindowDrag(char* w)
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
			g_774a5c = bx;
			bp = *(int*) (w + 0x258);
			g_774a50 = d2_MouseRightBoundary;
			g_774a44 = d2_MouseBottomBoundary;
			g_774a54 = g_6b5c80;
			g_774a48 = d2_MouseTopBoundary;
			g_6b5c80 = x - bx;
			g_774a60 = bp;
			d2_MouseRightBoundary = g_778d24 - bx - 0x200 + x;
			d2_MouseTopBoundary = y - bp;
			d2_MouseBottomBoundary = g_778d20 - bp - 0x168 + y;
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
		d2_MouseBottomBoundary = g_774a44;
		g_6b5c80 = g_774a54;
		d2_MouseRightBoundary = g_774a50;
		g_774a6c = 0;
		g_774a70 = 0;
		d2_MouseTopBoundary = g_774a48;
		g_6772c4 = 1;
		fcn_004125c0(d2_MouseX, d2_MouseY);
		g_774a74 = 0;
	}
	return r;
}
