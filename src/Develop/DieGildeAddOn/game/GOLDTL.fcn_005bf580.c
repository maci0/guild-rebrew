#include "client_types.h"

extern unsigned short g_774970;
extern int g_772514;
extern int g_14ce8e0;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14b5e04;
extern int g_14b5e08;
extern int g_14b5e0c;
extern int g_14b5e10;
extern int g_14b5e14;
extern int g_14b5e18;
extern int g_1015ea0;
extern int g_1015f4c;
extern pos14_7f4c00 g_7f4c00;

char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_004c5620(char*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_0046fac0(int, int, int, int);
void __cdecl fcn_00472900(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00472380(int, int, int, int, int);
void __cdecl fcn_00468bb0(int, int, int, int, int);
void __cdecl fcn_00533a60(int, int, int*, int, int, int);
int __cdecl fcn_00471f80(int);
int __cdecl gm_WalkEntityChain(int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00526010(void*, int, int);
void __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c4ef0(char*);
void __cdecl fcn_004c5530(void*);

/* ADDRESS: GOLDTL 0x005bf580 */
int __cdecl fcn_005bf580(char* rec)
{
	char* q;
	char* h;
	int tries;
	int sel[2];
	int ret;
	int row;
	unsigned char pkt[0xf8];
	char buf[0x3fc];
	unsigned char* tbl;
	int slot;
	int row2;
	int v;
	int w1;
	int w2;
	int n;
	int ea;
	float f;
	float f2;

	q = fcn_005463a0(2, 2, g_774970, 0, 0x18);
	tries = 0;
	if (q != 0) {
		for (;;) {
			if (*(int*) (q + 0xc4) == *(int*) (rec + 4)) {
				io_FormatTextBuffer(buf, 0x42c1, *(unsigned short*) rec);
				if (fcn_00526120(buf, 0x101) != 0) {
					*(pos14_7f4c00*) (q + 0x52) = g_7f4c00;
					*(int*) (q + 0x84) = fcn_004c5620(q, -1);
				}
				return 0;
			}
			tries++;
			q = he_fn_Handlung();
			if (q == 0)
				break;
		}
		if (tries > 4) {
			io_FormatTextBuffer(buf, 0x42c0, 5);
			fcn_00526120(buf, 0x104);
			return 0;
		}
	}
	h = (char*) fcn_00470820(0, 0, "locations\\wohnsitz\\spy");
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60((int) h);
	d2_SetForm((int) h, 0);
	fcn_005340f0(g_772514);
	d2_SetForm((int) h, 2);
	row = fcn_0046fac0(0, 3, g_14b5e18, g_772514);
	slot = g_1015ea0 + row * 0x2f4;
	*(int*) (slot + 0x6c) = 1;
	*(int*) (slot + 0x18) = *(int*) (g_1015f4c + g_772514 * 0x3cc);
	fcn_00472900(row, 0x54);
	row2 = fcn_004677e0(0x57, 0x14, 0xc8, 0, 0x64, 0x7b, 0x82, g_772514);
	fcn_00472380(row2, 0, 2, 0, 1);
	fcn_00468bb0(row2, 3, g_14b5e0c, g_14b5e10, g_14b5e14);
	d2_SetForm((int) h, 3);
	fcn_00533a60(g_772514, 0, sel, 2, g_14b5e04, g_14b5e08);
	ret = 0;
	tbl = (unsigned char*) (0x7f4ca0 + g_774970 * 0x21c);
	while (fcn_005373e0((void*) fcn_005bf580, 0x677c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (*(unsigned short*) rec == 0xffff) {
			g_774654 = 1;
		} else {
			v = fcn_00471f80(row2);
			f = (float) v * *(float*) 0x664188 + *(float*) 0x6628a0;
			w1 = gm_WalkEntityChain(*(unsigned short*) tbl);
			f2 = (float) w1 * *(float*) 0x664138;
			w2 = gm_WalkEntityChain(*(unsigned short*) rec);
			n = (int) ((float) w2 * *(float*) 0x664138 + f2);
			n = (int) ((float) n * f);
			d2_SetForm((int) h, 1);
			io_AppendText((int) 0x6811b0);
			io_AppendText(0x42b8, n, *(unsigned short*) rec);
			if (g_100f1dc != -1) {
				if (g_67d370 == sel[0]
					&& fcn_00526010(tbl, n, *(unsigned char*) 0x773d75) != 0) {
					pkt[4] = 0x18;
					*(int*) (pkt + 8) = *(int*) (tbl + 4);
					*(int*) (pkt + 0xc) = -1;
					pkt[0x36] = 2;
					*(int*) (pkt + 0x70) = *(int*) (rec + 4);
					ea = *(int*) (tbl + 0x16c);
					*(int*) (pkt + 0x58) = ea != 0 ? *(int*) (ea + 1) : -1;
					*(int*) (pkt + 0x94) = n;
					*(int*) (pkt + 0x9c) = fcn_00471f80(row2);
					fcn_004c4eb0("spionage");
					fcn_004c5530(pkt);
					fcn_004c4ef0("spionage");
					io_FormatTextBuffer(buf, 0x42bf, *(unsigned short*) rec);
					fcn_00526120(buf, 0x100);
					g_774654 = 1;
					ret = 1;
				} else if (g_67d370 == sel[1]) {
					g_774654 = 1;
				}
			}
		}
	}
	fcn_00471e30((int) h);
	fcn_00532ef0();
	return ret;
}
