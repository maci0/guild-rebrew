// FUNCTION: GOLDTL 0x00533dc0
// SIZE: 383

// SIZE 0x3cc
typedef struct {
	char pad0[0x3a8];
	int margin[4];
	char pad3b8[0x3cc - 0x3b8];
} Window;

extern Window g_1015f40[];
extern int g_772514;
extern unsigned char* g_7746c4;
extern unsigned char* g_7746c8;

void __cdecl fcn_0046f740(int, int, int, int);

void __cdecl fcn_00533dc0(int wnd, int page, int icon)
{
	unsigned char* p;

	fcn_0046f740(0x257, 9, 0x520, wnd);
	if (icon != 0) {
		fcn_0046f740(0xb, 9, icon, wnd);
	} else {
		p = g_7746c4;
		if (p == 0) {
			p = g_7746c8;
		}
		if (p == 0) {
			fcn_0046f740(0xb, 9, 0x520, wnd);
		} else {
			fcn_0046f740(0xb, 9, *p + 0x427, wnd);
		}
	}
	p = g_7746c4;
	if (p == 0) {
		p = g_7746c8;
	}
	if (p == 0) {
		fcn_0046f740(0x257, 9, 0x444, wnd);
	} else if (page != 0x73b) {
		fcn_0046f740(0x257, 9, *p + 0x427, wnd);
	} else {
		fcn_0046f740(0x1eb, 9, 0x520, wnd);
		fcn_0046f740(0x1eb, 9, *p + 0x427, wnd);
	}
	if (page != 0x73b) {
		fcn_0046f740(0, 0, page, wnd);
		fcn_0046f740(0, 0x190, page + 1, wnd);
		fcn_0046f740(0, 0x4d, page + 2, wnd);
		fcn_0046f740(0x247, 0x4d, page + 3, wnd);
	} else {
		fcn_0046f740(0, 0, 0x73b, wnd);
		fcn_0046f740(0, 0x43, 0x73d, wnd);
		fcn_0046f740(0x1f7, 0x43, 0x73e, wnd);
		fcn_0046f740(0, 0x1a8, 0x73c, wnd);
	}
	g_1015f40[g_772514].margin[0] = 0x18;
	g_1015f40[g_772514].margin[1] = 0x18;
	g_1015f40[g_772514].margin[2] = 0x18;
	g_1015f40[g_772514].margin[3] = 0x18;
}
