// FUNCTION: GOLD 0x0052e700
// SIZE: 386

// SIZE 0x3c4
typedef struct {
	char pad0[0x3a8];
	int margin[4];
	char pad3b8[0x3c4 - 0x3b8];
} Window;

extern Window g_f8f110[];
extern int g_6ed938;
extern unsigned char* g_6f2308;
extern unsigned char* g_6f230c;

void __cdecl fcn_004731c0(int, int, int, int);

void __cdecl fcn_0052e700(int wnd, int page, int icon)
{
	unsigned char* p;

	fcn_004731c0(0x257, 9, 0x520, wnd);
	if (icon != 0) {
		fcn_004731c0(0xb, 9, icon, wnd);
	} else {
		p = g_6f2308;
		if (p == 0) {
			p = g_6f230c;
		}
		if (p == 0) {
			fcn_004731c0(0xb, 9, 0x520, wnd);
		} else {
			fcn_004731c0(0xb, 9, *p + 0x427, wnd);
		}
	}
	p = g_6f2308;
	if (p == 0) {
		p = g_6f230c;
	}
	if (p == 0) {
		fcn_004731c0(0x257, 9, 0x444, wnd);
	} else if (page != 0x73b) {
		fcn_004731c0(0x257, 9, *p + 0x427, wnd);
	} else {
		fcn_004731c0(0x1eb, 9, 0x520, wnd);
		fcn_004731c0(0x1eb, 9, *p + 0x427, wnd);
	}
	if (page != 0x73b) {
		fcn_004731c0(0, 0, page, wnd);
		fcn_004731c0(0, 0x190, page + 1, wnd);
		fcn_004731c0(0, 0x4d, page + 2, wnd);
		fcn_004731c0(0x247, 0x4d, page + 3, wnd);
	} else {
		fcn_004731c0(0, 0, 0x73b, wnd);
		fcn_004731c0(0, 0x43, 0x73d, wnd);
		fcn_004731c0(0x1f7, 0x43, 0x73e, wnd);
		fcn_004731c0(0, 0x1a8, 0x73c, wnd);
	}
	g_f8f110[g_6ed938].margin[0] = 0x18;
	g_f8f110[g_6ed938].margin[1] = 0x18;
	g_f8f110[g_6ed938].margin[2] = 0x18;
	g_f8f110[g_6ed938].margin[3] = 0x18;
}
